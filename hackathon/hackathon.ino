#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
// Include JSON Library https://arduinojson.org
#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "WiFiSSID"
#define STAPSK "WiFiPassword"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
const char *host = "rest.bitcoin.com";

// JSON
// Allocate the JSON document
const size_t capacity = JSON_ARRAY_SIZE(6) + 7 * JSON_OBJECT_SIZE(6) + 870;
DynamicJsonDocument doc(capacity);

// HTTPS Port
const int httpsPort = 443;

// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "DB AB 4F 13 A0 85 59 9D 12 E5 38 9F 19 0D 95 3E BC D0 02 A1";
WiFiClientSecure client;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);
  // WiFi
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 0.5 second for re-trying
    delay(500);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
}

const char* makeRequest(String addr) {
  // Use WiFiClientSecure class to create TLS connection
  Serial.print("Connecting to ");
  Serial.print(host);
  String url = "GET https://rest.bitcoin.com/v2/address/unconfirmed/" + addr + " HTTP/1.1";
  //Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  Serial.println("\nStarting connection to host...");
  if (!client.connect(host, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println(url);
    // client.println("GET https://rest.bitcoin.com/v2/address/unconfirmed/bitcoincash:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq9 HTTP/1.1");
    client.println("Host: rest.bitcoin.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    String content = "";
    char c;
    // if there are incoming bytes available
    // from the server, read them and concatenate
    // them into the content variable:
    while (client.available()) {
      c = client.read();
      content.concat(c);
    }

    deserializeJson(doc, content);
    JsonArray utxos = doc["utxos"];

    JsonObject utxos_0 = utxos[0];
    const char* utxos_0_txid = utxos_0["txid"];
    int utxos_0_vout = utxos_0["vout"];
    float utxos_0_amount = utxos_0["amount"];
    int utxos_0_satoshis = utxos_0["satoshis"];
    int utxos_0_confirmations = utxos_0["confirmations"];
    long utxos_0_ts = utxos_0["ts"];

    JsonObject utxos_1 = utxos[1];
    const char* utxos_1_txid = utxos_1["txid"];
    int utxos_1_vout = utxos_1["vout"];
    float utxos_1_amount = utxos_1["amount"];
    long utxos_1_satoshis = utxos_1["satoshis"];
    int utxos_1_confirmations = utxos_1["confirmations"];
    long utxos_1_ts = utxos_1["ts"];

    JsonObject utxos_2 = utxos[2];
    const char* utxos_2_txid = utxos_2["txid"];
    int utxos_2_vout = utxos_2["vout"];
    float utxos_2_amount = utxos_2["amount"];
    long utxos_2_satoshis = utxos_2["satoshis"];
    int utxos_2_confirmations = utxos_2["confirmations"];
    long utxos_2_ts = utxos_2["ts"];

    JsonObject utxos_3 = utxos[3];
    const char* utxos_3_txid = utxos_3["txid"];
    int utxos_3_vout = utxos_3["vout"];
    float utxos_3_amount = utxos_3["amount"];
    long utxos_3_satoshis = utxos_3["satoshis"];
    int utxos_3_confirmations = utxos_3["confirmations"];
    long utxos_3_ts = utxos_3["ts"];

    JsonObject utxos_4 = utxos[4];
    const char* utxos_4_txid = utxos_4["txid"];
    int utxos_4_vout = utxos_4["vout"];
    float utxos_4_amount = utxos_4["amount"];
    long utxos_4_satoshis = utxos_4["satoshis"];
    int utxos_4_confirmations = utxos_4["confirmations"];
    long utxos_4_ts = utxos_4["ts"];

    JsonObject utxos_5 = utxos[5];
    const char* utxos_5_txid = utxos_5["txid"];
    int utxos_5_vout = utxos_5["vout"];
    float utxos_5_amount = utxos_5["amount"];
    long utxos_5_satoshis = utxos_5["satoshis"];
    int utxos_5_confirmations = utxos_5["confirmations"];
    long utxos_5_ts = utxos_5["ts"];

    const char* legacyAddress = doc["legacyAddress"];
    const char* cashAddress = doc["cashAddress"];
    const char* slpAddress = doc["slpAddress"];
    const char* scriptPubKey = doc["scriptPubKey"];
    // const char* asm = doc["asm"];


    // PROBLEM: Exception (28) https://github.com/esp8266/Arduino/blob/master/doc/exception_causes.rst
    if (utxos >= 1) { // apparently not a solution :(
      Serial.println(utxos_0_txid);
      Serial.println(utxos_1_txid);
      Serial.println(utxos_2_txid);
      // Serial.println(legacyAddress);
      // Serial.println(cashAddress);
      // Serial.println(slpAddress);
      // Serial.println(scriptPubKey);
    }
    client.stop();
    return utxos_0_txid;
  }
}


const char* makeSecondRequest(String addr) {
  // Use WiFiClientSecure class to create TLS connection
  Serial.print("Connecting to ");
  Serial.print(host);
  String url = "GET https://rest.bitcoin.com/v2/address/unconfirmed/" + addr + " HTTP/1.1";
  //Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  Serial.println("\nStarting connection to host...");
  if (!client.connect(host, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println(url);
    client.println("Host: rest.bitcoin.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    String content = "";
    char c;
    // if there are incoming bytes available
    // from the server, read them and concatenate
    // them into the content variable:
    while (client.available()) {
      c = client.read();
      content.concat(c);
    }

    deserializeJson(doc, content);
    JsonArray utxos = doc["utxos"];

    JsonObject utxos_0 = utxos[0];
    const char* utxos_0_txid = utxos_0["txid"];
    int utxos_0_vout = utxos_0["vout"];
    float utxos_0_amount = utxos_0["amount"];
    int utxos_0_satoshis = utxos_0["satoshis"];
    int utxos_0_confirmations = utxos_0["confirmations"];
    long utxos_0_ts = utxos_0["ts"];

    JsonObject utxos_1 = utxos[1];
    const char* utxos_1_txid = utxos_1["txid"];
    int utxos_1_vout = utxos_1["vout"];
    float utxos_1_amount = utxos_1["amount"];
    long utxos_1_satoshis = utxos_1["satoshis"];
    int utxos_1_confirmations = utxos_1["confirmations"];
    long utxos_1_ts = utxos_1["ts"];

    JsonObject utxos_2 = utxos[2];
    const char* utxos_2_txid = utxos_2["txid"];
    int utxos_2_vout = utxos_2["vout"];
    float utxos_2_amount = utxos_2["amount"];
    long utxos_2_satoshis = utxos_2["satoshis"];
    int utxos_2_confirmations = utxos_2["confirmations"];
    long utxos_2_ts = utxos_2["ts"];

    JsonObject utxos_3 = utxos[3];
    const char* utxos_3_txid = utxos_3["txid"];
    int utxos_3_vout = utxos_3["vout"];
    float utxos_3_amount = utxos_3["amount"];
    long utxos_3_satoshis = utxos_3["satoshis"];
    int utxos_3_confirmations = utxos_3["confirmations"];
    long utxos_3_ts = utxos_3["ts"];

    JsonObject utxos_4 = utxos[4];
    const char* utxos_4_txid = utxos_4["txid"];
    int utxos_4_vout = utxos_4["vout"];
    float utxos_4_amount = utxos_4["amount"];
    long utxos_4_satoshis = utxos_4["satoshis"];
    int utxos_4_confirmations = utxos_4["confirmations"];
    long utxos_4_ts = utxos_4["ts"];

    JsonObject utxos_5 = utxos[5];
    const char* utxos_5_txid = utxos_5["txid"];
    int utxos_5_vout = utxos_5["vout"];
    float utxos_5_amount = utxos_5["amount"];
    long utxos_5_satoshis = utxos_5["satoshis"];
    int utxos_5_confirmations = utxos_5["confirmations"];
    long utxos_5_ts = utxos_5["ts"];

    const char* legacyAddress = doc["legacyAddress"];
    const char* cashAddress = doc["cashAddress"];
    const char* slpAddress = doc["slpAddress"];
    const char* scriptPubKey = doc["scriptPubKey"];
    // const char* asm = doc["asm"];


    // PROBLEM: Exception (28) https://github.com/esp8266/Arduino/blob/master/doc/exception_causes.rst
    if (utxos >= 1) { // apparently not a solution :(
      Serial.println(utxos_0_txid);
      Serial.println(utxos_1_txid);
      Serial.println(utxos_2_txid);
      // Serial.println(legacyAddress);
      // Serial.println(cashAddress);
      // Serial.println(slpAddress);
      // Serial.println(scriptPubKey);
    }
    client.stop();
    return utxos_0_txid;
  }
}

// the following if statement could apply to a 
// relay module & a 5V/12V power supply to automate a 
// variety of appliances, from lights to candy machines
// That's fucking right. I'm coming for you Iozeta.
void loop() {
  const char* txid = makeRequest("bitcoincash:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq9");
  delay (10000);
  const char* txid2 = makeSecondRequest("bitcoincash:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq9");
  if (&txid != &txid2) { 
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN)); 
  } 
  delay (50000000);
}
// I chose to opt in to toggle a built-in led because
// simplicity and beauty ;)