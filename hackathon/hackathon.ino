#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
// Include JSON Library https://arduinojson.org
#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "wifi"
#define STAPSK "password"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
const char *host = "rest.bitcoin.com";

// HTTPS Port
const int httpsPort = 443;

// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "DB AB 4F 13 A0 85 59 9D 12 E5 38 9F 19 0D 95 3E BC D0 02 A1";
WiFiClientSecure client;

void makeRequest() {
    String url = "/v2/address/unconfirmed/bitcoincash:qr94atyg94rcuh76gxhk6wl89m4plcx9p5tn5wqjp9";
    Serial.print("requesting URL: ");
    Serial.println(url);
   

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: BuildFailureDetectorESP8266\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("request sent");

    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
        {
            Serial.println("headers received");
            while (client.available()) {
              char c = 0;
              client.readBytes(&c, 1);
              Serial.print(c);
              }
            break;
        }
    }


    // JSON
    // Allocate the JSON document
    const size_t capacity = JSON_ARRAY_SIZE(1) + 2*JSON_OBJECT_SIZE(6) + 510;
    DynamicJsonDocument doc(capacity);

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, client);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }

    // Get the Name:
    JsonObject utxos_0 = doc["utxos"][0];
    const char* utxos_0_txid = utxos_0["txid"];
    int utxos_0_vout = utxos_0["vout"];
    float utxos_0_amount = utxos_0["amount"];
    long utxos_0_satoshis = utxos_0["satoshis"];
    int utxos_0_confirmations = utxos_0["confirmations"];
    long utxos_0_ts = utxos_0["ts"];
    const char* legacyAddress = doc["legacyAddress"];
    const char* cashAddress = doc["cashAddress"];
    const char* slpAddress = doc["slpAddress"];
    const char* scriptPubKey = doc["scriptPubKey"];

    Serial.println(utxos_0_txid);
    Serial.println(legacyAddress);
    Serial.println(cashAddress);
    Serial.println(slpAddress);
    Serial.println(scriptPubKey);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // initialize onboard LED
    // Wifi
    Serial.begin(115200);
    Serial.println();
    Serial.print("connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Use WiFiClientSecure class to create TLS connection
    Serial.print("connecting to ");
    Serial.println(host);

    //Serial.printf("Using fingerprint '%s'\n", fingerprint);
    client.setFingerprint(fingerprint);

    if (!client.connect(host, httpsPort))
    {
        Serial.println("connection failed");
        return;
    }

    makeRequest();
}

void loop() {

}