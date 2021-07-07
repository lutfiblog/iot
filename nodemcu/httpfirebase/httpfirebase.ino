#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
long randNumber;
long randNumber2;
long randNumber3;


void setup() {
  Serial.begin(115200);                         
  WiFi.begin("lutfiyaa", "aku12345");
  
  randomSeed(analogRead(A0));
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.println("Waiting for connection");
  }
}

void loop() {
  randNumber = random(30);
  Serial.println(randNumber);
  randNumber2 = random(100);
  Serial.println(randNumber);
  randNumber3 = random(300);

  if (WiFi.status() == WL_CONNECTED) { 

    StaticJsonBuffer<300> JSONbuffer;   
    JsonObject& JSONencoder = JSONbuffer.createObject();
//buat json object { "sensor1" : randNumber, "sensor2" : randNumber2, "sensor3" : randNumber3, } 
    JSONencoder["sensor1"] = randNumber;
    JSONencoder["sensor2"] = randNumber2;
    JSONencoder["sensor3"] = randNumber3;
    //tambah child array 
//buat json object { "sensor1" : randNumber, "sensor2" : randNumber2, "sensor3" : randNumber3, "value" : ["values":20,21,23]} 
    //    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
    //    values.add(20); //Add value to array
    //    values.add(21); //Add value to array
    //    values.add(23); //Add value to array
    //
    //    JsonArray& timestamps = JSONencoder.createNestedArray("timestamps"); //JSON array
    //    timestamps.add("10:10"); //Add value to array
    //    timestamps.add("10:20"); //Add value to array
    //    timestamps.add("10:30"); //Add value to array

    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
    WiFiClientSecure client;
    HTTPClient http;  
    client.setInsecure();
    http.begin(client, "https://lutfiiot-default-rtdb.firebaseio.com");  
    http.setURL("/.json");
    http.addHeader("Content-Type", "application/json");  //filejson header

    int httpCode = http.POST(JSONmessageBuffer);  
    String payload = http.getString();                                       
    Serial.println(httpCode);   
    Serial.println(payload);    

    http.end();  

  } else {

    Serial.println("Error in WiFi connection");

  }

  delay(5000);  

}
