#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MQTT_MAX_PACKET_SIZE 256
#include <stdio.h>
#include <string.h>
#define MSG_BUFFER_SIZE  (50)

AsyncWebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* APssid = "NodeMCU";
const char* APpassword = "123456789";
char AP_IP[32];
String server_ip = "";
const char* ssid = "Dialog 4G 204";
const char* password = "B3b95FC1";
const char* mqtt_server = "test.mosquitto.org";

const char* PARAM_INPUT_1 = "Country";
String inputMessage = "";
String arry[21];
char msg[MSG_BUFFER_SIZE];

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  }

  td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;}

  tr:nth-child(even) {background-color: #dddddd;}
 
  </style>
  </head>
  
  <body>
  <h2>Local Covid 19 Status</h2>
  <table width = 500>
      <tr>
          <th>Topic</th>
          <th>Count</th>
      </tr>
      <tr>
          <td>New cases</td>
          <td>%Data1%</td>
      </tr>
      <tr>
          <td>Total cases</td>
          <td>%Data2%</td>
      </tr>
      <tr>
          <td>In hospitals</td>
          <td>%Data3%</td>
      </tr>
      <tr>
          <td>Total deaths</td>
          <td>%Data4%</td>
      </tr>
      <tr>
          <td>New deaths</td>
          <td>%Data5%</td>
      </tr>
      <tr>
          <td>Total recovered</td>
          <td>%Data6%</td>
      </tr>
      <tr>
          <td>Active cases</td>
          <td>%Data7%</td>
      </tr>
      <tr>
          <td>Total PCR tests</td>
          <td>%Data8%</td>
      </tr>
      <tr>
          <td>Daily PCR Tests</td>
          <td>%Data10%</td>
      </tr>
  </table>


  
  <h2>Gobal Covid 19 Status</h2>
  <table width = 500>
      <tr>
          <th>Topic</th>
          <th>Count</th>
      </tr>
      <tr>
          <td>New cases</td>
          <td>%Data11%</td>
      </tr>
      <tr>
          <td>Total cases</td>
          <td>%Data12%</td>
      </tr>
      <tr>
          <td>New deaths</td>
          <td>%Data13%</td>
      </tr>
      <tr>
          <td>Total deaths</td>
          <td>%Data14%</td>
      </tr>
      <tr>
          <td>New recovered</td>
          <td>%Data15%</td>
      </tr>
      <tr>
          <td>Total Recovered</td>
          <td>%Data16%</td>
      </tr>
  </table>
  <h2></h2>
  </body>
  
  <body>
  <form action="/get">
  Country: <input type="text" name="Country">
  <input type="submit" value="Submit">
  </form>
  
  <h2>%Data21% Covid 19 Status</h2>
  <table width = 500>
      <tr>
          <th>Topic</th>
          <th>Count</th>
      </tr>
      <tr>
          <td>Total cases</td>
          <td><span id="D17">%%Data17%%</span></td>
      </tr>
      <tr>
          <td>Total deaths</td>
          <td><span id="D18">%%Data18%%</span></td>
      </tr>
      <tr>
          <td>Total Recovered</td>
          <td><span id="D19">%%Data19%%</span></td>
      </tr>
      <tr>
          <td>Active cases</td>
          <td><span id="D20">%%Data20%%</span></td>
      </tr>
   </table> 
</body>


<script>
setInterval(function ( ){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200) {document.getElementById("D17").innerHTML = this.responseText;}};
  xhttp.open("GET", "/D17", true);
  xhttp.send();
  },2000 );

setInterval(function ( ){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200) {document.getElementById("D18").innerHTML = this.responseText;}};
  xhttp.open("GET", "/D18", true);
  xhttp.send();
  },2000 );

setInterval(function ( ){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200) {document.getElementById("D19").innerHTML = this.responseText;}};
  xhttp.open("GET", "/D19", true);
  xhttp.send();
  },2000 );

setInterval(function ( ){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200) {document.getElementById("D20").innerHTML = this.responseText;}};
  xhttp.open("GET", "/D20", true);
  xhttp.send();
  },2000 );

</script>
</html>)rawliteral";
  

//................................................................GIVE Data For WEBSEVER.....................................................................................
String processor(const String& var){
  
  if(var == "Data1"){return arry[0];}
  if(var == "Data2"){return arry[1];}
  if(var == "Data3"){return arry[2];}
  if(var == "Data4"){return arry[3];}
  if(var == "Data5"){return arry[4];}
  if(var == "Data6"){return arry[5];}
  if(var == "Data7"){return arry[6];}
  if(var == "Data8"){return arry[7];}
  if(var == "Data9"){return arry[8];}
  if(var == "Data10"){return arry[9];}
  if(var == "Data11"){return arry[10];}
  if(var == "Data12"){return arry[11];}
  if(var == "Data13"){return arry[12];}
  if(var == "Data14"){return arry[13];}
  if(var == "Data15"){return arry[14];}
  if(var == "Data16"){return arry[15];}
  if(var == "Data17"){return arry[16];}
  if(var == "Data18"){return arry[17];}
  if(var == "Data19"){return arry[18];}
  if(var == "Data20"){return arry[19];}
  if(var == "Data21"){return inputMessage;}
  return String();
  }

//................................................................GET DATA FROM WEBSEVER.....................................................................................
void getdata(){

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    client.publish("Refresh","hello");
    request->send_P(200, "text/html", index_html, processor);
    });
    
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);     
      int len = inputMessage.length() + 1;
      char messagearry[len];
      inputMessage.toCharArray(messagearry, len);
      const char* publishmessage = messagearry;     
      if (client.connect(clientId.c_str())) {
        Serial.println("connected");
        client.publish("Refresh",publishmessage);
        client.loop();} 
      else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        delay(5000);}}
    else {
      inputMessage = "No message sent";
      inputParam = "none";}
    request->send_P(200, "text/html", index_html, processor); 
      
    Serial.println(inputMessage);
    });
      
    server.on("/D17", HTTP_GET, [](AsyncWebServerRequest *request){request->send_P(200, "text/plain", String(arry[16]).c_str());});
    server.on("/D18", HTTP_GET, [](AsyncWebServerRequest *request){request->send_P(200, "text/plain", String(arry[17]).c_str());});  
    server.on("/D19", HTTP_GET, [](AsyncWebServerRequest *request){request->send_P(200, "text/plain", String(arry[18]).c_str());});  
    server.on("/D20", HTTP_GET, [](AsyncWebServerRequest *request){request->send_P(200, "text/plain", String(arry[19]).c_str());});    
      
   }
    
    /*
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  */





//................................................................CONNECT WIFI AP..........................................................................................
void setup_wifi(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  }

void setup_AP() {
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(APssid, APpassword);
  Serial.print("IP address of the AP: ");
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");
  sprintf(AP_IP, "%d.%d.%d.%d", myIP[0], myIP[1], myIP[2], myIP[3]);
  server_ip = String(AP_IP);
}


//................................................................CONNECT WIFI AP..........................................................................................
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("HTTP server 0");
  if (!strcmp(topic, "Covid19")) {
    payload[length] = '\0';
    char* str = (char*)payload;
    char * pch;
    pch = strtok (str, ",");
    int count = 0;
    while (pch != NULL)
    {
      printf ("%s\n", pch);
      pch = strtok (NULL, ",");
      arry[count] = pch;
      count = count + 1;
    }}}


    //Serial.println(count);


  




//................................................................Reconect..........................................................................................
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("Refresh", "hello");
      client.subscribe("Covid19");
      client.loop();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }}}    
void notFound(AsyncWebServerRequest *request) {request->send(404, "text/plain", "Not found");}



void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_AP();
  getdata();
  server.onNotFound(notFound);
  server.begin();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  client.publish("Refresh","hello");
  request->send_P(200, "text/html", index_html, processor);
  });
  }


void loop() {
  client.setCallback(callback);
  client.loop();
  delay(5000);
  if (!client.connected()) {reconnect();}
}
