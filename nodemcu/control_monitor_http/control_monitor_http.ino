#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
WiFiClient client;

String host = "localhost";
const char auth[] = "";
char ssid[] = "lutfiyaa";
char password[] = "aku12345";

unsigned long timePrevious = 0;
const long interval = 1000;
//control
//#define led D2
//monitoring
#define potPin A0
int pot = 0;
long randNumber;
long randNumber2;
long randNumber3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  randomSeed(analogRead(potPin));
  Serial.println("Connecting....");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.print("Connected to wifi ahay, your IP is...");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - timePrevious >= interval) {
    timePrevious = millis();

    //cek wifi status & get data from page
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin("http://" + host + "/iot/last_oke/json.php"); //endpoint
      int httpCode = http.GET();
      //cek returning code
      if (httpCode > 0) {
        //get payload message
        //String payload = http.getString();
        //PARSING
        const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 100;
        DynamicJsonDocument doc(capacity);

        String json = http.getString();
        deserializeJson(doc, json);

        const char* id = doc["id"]; //array pertama
        const char* nilai = doc["nilai"];
        const char* id2 = doc["id2"]; //array pertama
        const char* nilai2 = doc["nilai2"];
        const char* id3 = doc["id3"]; //array pertama
        const char* nilai3 = doc["nilai3"];

        //to serial monitor
        Serial.print("id : ");
        Serial.println(id);
        Serial.print("nilai : ");
        Serial.println(nilai);

        //to serial monitor
        Serial.print("id : ");
        Serial.println(id2);
        Serial.print("nilai : ");
        Serial.println(nilai2);

        //to serial monitor
        Serial.print("id : ");
        Serial.println(id3);
        Serial.print("nilai : ");
        Serial.println(nilai3);

        if (doc["nilai"] == "1") {
          Serial.println("NYALA DONG");
          digitalWrite(LED_BUILTIN, LOW);
        } else {
          Serial.println("Yah MATI");
          digitalWrite(LED_BUILTIN, HIGH);
        }

        if (doc["nilai2"] == "1") {
          Serial.println("NYALA DONG");
          // digitalWrite(LED_BUILTIN, LOW);
        } else {
          Serial.println("Yah MATI");
          //digitalWrite(LED_BUILTIN, HIGH);
        }

        if (doc["nilai3"] == "1") {
          Serial.println("NYALA DONG");
          //digitalWrite(LED_BUILTIN, LOW);
        } else {
          Serial.println("Yah MATI");
          //digitalWrite(LED_BUILTIN, HIGH);
        }
      } //if(httpCode...............

      //pot = analogRead(potPin);
      randNumber = random(30);
      Serial.println(randNumber);
      randNumber2 = random(100);
      Serial.println(randNumber);
      randNumber3 = random(300);
      Serial.println(randNumber);
      if (client.connect(host, 80)) { //(host, port)
        client.print("GET/iot/last_oke/terimaDataSensor.php?");
        client.print("sensor=");
        client.print(randNumber);

        //        // parameter 2 dan selanjutnya
        client.print("&");
        client.print("sensor2=");
        client.print(randNumber2);

        client.print("&");
        client.print("sensor3=");
        client.print(randNumber3);

        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(host);
        client.println("Connection: close");
        client.println();

      } else {
        Serial.println("data gak kekirim cuy, sedih deh");
      }
      http.end();
    }
  }
}
