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

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "DB AB 4F 13 A0 85 59 9D 12 E5 38 9F 19 0D 95 3E BC D0 02 A1";

void setup()
{
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
    WiFiClientSecure client;
    Serial.print("connecting to ");
    Serial.println(host);

    //Serial.printf("Using fingerprint '%s'\n", fingerprint);
    client.setFingerprint(fingerprint);

    if (!client.connect(host, httpsPort))
    {
        Serial.println("connection failed");
        return;
    }

    String url = "/v2/address/details/bitcoincash:qqxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
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
            break;
        }
    }

    // String line = client.readString();

    // JSON
    // Allocate the JSON document
    const size_t capacity = JSON_ARRAY_SIZE(1000) + JSON_OBJECT_SIZE(16) + 72640;
    DynamicJsonDocument doc(capacity);

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, client);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }

    JsonObject root_0 = doc[0];
    Serial.println("JSON Docss");
    Serial.println(root_0);

    // Get the Name:
    const char *root_0_name = root_0["name"];

    // if (line.startsWith("{\"state\":\"success\""))
    // {
    //     Serial.println("esp8266/Arduino CI successfull!");
    // }
    // else
    // {
    //     Serial.println("esp8266/Arduino CI has failed");
    // }
    Serial.println("Name was");
    Serial.println("==========");
    Serial.println(root_0_name);
    Serial.println("==========");
    Serial.println("closing connection");
}

void loop() {

}
