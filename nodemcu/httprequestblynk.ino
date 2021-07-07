#include <ESP8266WiFi.h>

const char auth[] = "authkalian";

const char ssid[] = "wificuy";
const char pass[] = "12345";

const char* host = "blynk-cloud.com";
unsigned int port = 8080;

long randNumber;
long randNumber2;
long randNumber3;

WiFiClient client;

// Start the WiFi connection
void connectNetwork()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
}

bool httpRequest(const String& method,
                 const String& request,
                 String&       response)
{
  Serial.print(F("Connecting to "));
  Serial.print(host);
  Serial.print(":");
  Serial.print(port);
  Serial.print("... ");
  if (client.connect(host, port)) {
    Serial.println("OK");
  } else {
    Serial.println("failed");
    return false;
  }

  client.print(method); client.println(F(" HTTP/1.1"));
  client.print(F("Host: ")); client.println(host);
  client.println(F("Connection: close"));
  if (request.length()) {
    client.println(F("Content-Type: application/json"));
    client.print(F("Content-Length: ")); client.println(request.length());
    client.println();
    client.print(request);
  } else {
    client.println();
  }

  //Serial.println("Waiting response");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return false;
    }
  }

  //Serial.println("Reading response");
  int contentLength = -1;
  while (client.available()) {
    String line = client.readStringUntil('\n');
    line.trim();
    line.toLowerCase();
    if (line.startsWith("content-length:")) {
      contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
    } else if (line.length() == 0) {
      break;
    }
  }

  //Serial.println("Reading response body");
  response = "";
  response.reserve(contentLength + 1);
  while (response.length() < contentLength && client.connected()) {
    while (client.available()) {
      char c = client.read();
      response += c;
    }
  }
  client.stop();
  return true;
}

void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();

  randomSeed(analogRead(A0));
  connectNetwork();
}

void loop() {
  String response;
  unsigned long value = millis();
  randNumber = random(30);
  Serial.println(randNumber);
  randNumber2 = random(100);
  Serial.println(randNumber);
  randNumber3 = random(300);

  String data1 = String("[\"") + randNumber + "\"]";
  if (httpRequest(String("PUT /") + auth + "/update/V1", data1, response)) {
    if (response.length() != 0) {
      Serial.print("WARNING: ");
      Serial.println(response);
    }
  }
  String data2 = String("[\"") + randNumber2 + "\"]";
  if (httpRequest(String("PUT /") + auth + "/update/V2", data2, response)) {
    if (response.length() != 0) {
      Serial.print("WARNING: ");
      Serial.println(response);
    }
  }
  String data3 = String("[\"") + randNumber3 + "\"]";
  if (httpRequest(String("PUT /") + auth + "/update/V3", data3, response)) {
    if (response.length() != 0) {
      Serial.print("WARNING: ");
      Serial.println(response);
    }
  }

  // Wait
  //delay(1000);
}