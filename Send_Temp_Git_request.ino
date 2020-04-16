
#include <dht.h>

dht DHT;

#define DHT8 8
#define DHT2 2
#define DHT4 4
#define DHT7 7




#include <SPI.h>
#include <Ethernet.h>
//-------------------------------------------------------------------------------
byte mac[] = { 0xDC , 0xD3 , 0xA2 , 0xD3 , 0x5B , 0xC7 }; //Setting MAC Address
char server[] = "api.pushingbox.com"; //pushingbox API server
IPAddress ip(192,168,1,39); //Arduino IP address. Only used when DHCP is turned off.
EthernetClient client; //define 'client' as object
String data; //GET query with data

float s1t;
float s1h;
float s2t;
float s2h;
float s3t;
float s3h;
float s4t;
float s4h;
String temps;

boolean koneksi = false;
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac, ip);
  }
  delay(1000);
}
//------------------------------------------------------------------------------
void loop(){

  readData();
    temps = String(s1t) + "," + String(s1h) + "," + String(s2t) + "," + String(s2h) + "," + String(s3t) + "," + String(s3h) + "," + String(s4t) + "," + String(s4h) ;
    Serial.println(temps);
    delay(20000);
    
    readData();
    temps += "," + String(s1t) + "," + String(s1h) + "," + String(s2t) + "," + String(s2h) + "," + String(s3t) + "," + String(s3h) + "," + String(s4t) + "," + String(s4h) ;
    Serial.println(temps);
    delay(20000);

    readData();
    temps += "," + String(s1t) + "," + String(s1h) + "," + String(s2t) + "," + String(s2h) + "," + String(s3t) + "," + String(s3h) + "," + String(s4t) + "," + String(s4h) ;
    Serial.println(temps);
    delay(20000);
    
    readData();
    temps += "," + String(s1t) + "," + String(s1h) + "," + String(s2t) + "," + String(s2h) + "," + String(s3t) + "," + String(s3h) + "," + String(s4t) + "," + String(s4h) ;
    Serial.println(temps);    
    delay(20000);

    readData();
    temps += "," + String(s1t) + "," + String(s1h) + "," + String(s2t) + "," + String(s2h) + "," + String(s3t) + "," + String(s3h) + "," + String(s4t) + "," + String(s4h) ;
    Serial.println(temps);
    delay(20000);

    readData();
    temps += "," + String(s1t) + "," + String(s1h) + "," + String(s2t) + "," + String(s2h) + "," + String(s3t) + "," + String(s3h) + "," + String(s4t) + "," + String(s4h) ;
    Serial.println(temps);

  
   kemasData(); //packing GET query with data
   Serial.println("connecting...");
   if (client.connect(server, 80)) {
     sendData();  
     koneksi = true; //connected = true
   }
   else{
     Serial.println("connection failed");
   }
  // loop
  while(koneksi){
    if (client.available()) {
    char c = client.read(); //save http header to c
    Serial.print(c); //print http header to serial monitor
    }
    if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
          Serial.print("Temperature Sent :");
          Serial.println(temps); //print sent value to serial monitor
          Serial.println(data);
    client.stop(); 
          koneksi = false; 
          data = ""; //data reset
    }
  }
  delay(17000); // interval
}

void readData(){
    int chk1 = DHT.read11(DHT8); //sensor-3
    s1t = DHT.temperature;
    s1h = DHT.humidity;
    if (s1t==-999 || s1h==-999 ) {
    s1t = 0;
    s1h = 0;
    }
    int chk2 = DHT.read11(DHT2); //sensor-2
    s2t = DHT.temperature;
    s2h = DHT.humidity;
    if (s2t==-999 || s2h==-999 ) {
    s2t = 0;
    s2h = 0;
    }
    int chk3 = DHT.read11(DHT4); //sensor-3
    s3t = DHT.temperature;
    s3h = DHT.humidity;
    if (s3t==-999 || s3h==-999 ) {
    s3t = 0;
    s3h = 0;
    }
    int chk4 = DHT.read11(DHT7); //sensor-4
    s4t = DHT.temperature;
    s4h = DHT.humidity;
    if (s4t==-999 || s4h==-999 ) {
    s4t = 0;
    s4h = 0;
    }

}
void kemasData(){
  data+="";
  data+="GET /pushingbox?devid=vA4EFADAE01C91EE&tempData="; //GET request query to pushingbox API
  data+=temps;
  data+=" HTTP/1.1";
}
void sendData(){
  Serial.println("connected");
  client.println(data);
  client.println("Host: api.pushingbox.com");
  client.println("Connection: close");
  client.println();
}
