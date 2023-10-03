#include<WiFi.h>
#include<ESPAsyncWebSrv.h>
#include<WebSocketsServer.h>
#include<ESP32Servo.h>
#include<stdlib.h>
#include<ArduinoJson.h>
#include<NewPing.h>
#include<Ticker.h>

int LED1 = 15;
int LED2 = 4;
int TRIG = 18;
int ECHO = 5;

Ticker timer;
NewPing sonar(TRIG,ECHO);
AsyncWebServer server(80);
WebSocketsServer socket(81);
Servo myServo;

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<body>
    <script>
        var connection = new WebSocket("ws://" + location.hostname + ":81")
        var led_1_stat = 0;
        var led_2_stat = 0;
        var x = 0;
        const led1_on = () => {
            led_1_stat = 1;
            send_json();
        }
        const led1_off = () => {
            led_1_stat = 0;
            send_json();
        }
        const led2_on = () => {
            led_2_stat = 1;
            send_json();
        }
        const led2_off = () => {
            led_2_stat = 0;
            send_json();
        }
        const handleServo = () => {
            x = document.getElementById("servo").value;
            send_json();
        }

        const send_json = () => {
            var data = '{' + "LED1:" + led_1_stat + "," + "LED2:" + led_2_stat + "," + "SERVO:" + x + '}';
            connection.send(data);
        }
        connection.onmessage = (event) => {
            var full_data = event.data;
            var {SONAR} = JSON.parse(full_data);
            document.getElementById('sensor_meter').value = SONAR;
            document.getElementById('sensor_data').innerHTML = SONAR;
        }
    </script>
    <center>
        <h1>Control Your LED remotely</h1>
        <h3>LED 1</h3>
        <button type="button" onclick="led1_on()">ON</button>
        <button type="button" onclick="led1_off()">OFF</button>
        <h3>LED 2</h3>
        <button type="button" onclick="led2_on()">ON</button>
        <button type="button" onclick="led2_off()">OFF</button>
        <h3>SERVO MOTOR</h3>
        <input type="range" name="servo" value="0" min="0" max="180" onchange="handleServo()" id="servo" />
        <h3>Distance between SONAR and Object</h3>
    </center>
    <div style="text-align: center;">
        <meter id="sensor_meter" value="40" min="0" max="150"></meter>
        <span id="sensor_data">80 </span>cm
    </div>
</body>

</html>
)=====";

void notFound(AsyncWebServerRequest *request){
  String message = "Page Not Found";
  request->send(404,"text/plain", message);
}

void WebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  switch(type){
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected\n",num);
      break;
    case WStype_CONNECTED:{
      IPAddress ip = socket.remoteIP(num);
      Serial.printf("[%u] Connected on IP: %d.%d.%d.%d url: %s\n",num,ip[0],ip[1],ip[2],ip[3],payload);
      socket.sendTXT(num,"Connected");
    }
      break;
    case WStype_TEXT:{
      Serial.printf("[%u] get text: %s\n",num,payload);
      String message = String((char*)(payload));
      Serial.println(message);
      DynamicJsonDocument docs(200);
      DeserializationError error = deserializeJson(docs,message);
      if(error){
        Serial.println("Error occurred...");
        return;
      }

      int led1_status = docs["LED1"];
      int led2_status = docs["LED2"];
      int servo = docs["SERVO"];

      digitalWrite(LED1,led1_status);
      digitalWrite(LED2,led2_status);
      myServo.write(servo);
    }
      break;
  }
}

void send_data(){
  unsigned int distance = sonar.ping_cm();
  String JSON_DATA = "{\"SONAR\" : ";
  JSON_DATA += distance;
  JSON_DATA += "}";
  socket.broadcastTXT(JSON_DATA);
}

void setup() {
  // put your setup code here, to run once:
  myServo.attach(14);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  Serial.begin(115200);
  Serial.println("Configuring Access Point...");
  WiFi.softAP("ESP32","");
  Serial.println("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/",[](AsyncWebServerRequest *request){
    request -> send_P(200,"text/html",webpage);
  });
  server.onNotFound(notFound);
  server.begin();
  socket.begin();
  socket.onEvent(WebSocketEvent);
  timer.attach(0.5,send_data);
}

void loop() {
  socket.loop();
}
