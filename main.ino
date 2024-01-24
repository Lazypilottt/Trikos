//4 motors, 2 servos.
//motor enabling pins: D5(14) and D6(12)
//Servo pins: D1 AND D2

#define ENA  14          //Enable/speed motors Right        GPIO14(D5)
#define ENB   12         //Enable/speed motors Left         GPIO12(D6)


#define IN_1  15          //L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          //L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           //L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           //L298N in4 motors Left            GPIO0(D3)

//servo motors
#define IN_5 5 // GPIO005;D1
#define IN_6 4 // GPIO04;D2


#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>
Servo s1;
String command;             
int speedCar = 800;         
int speed_Coeff = 3;
cont char* ssid = "Timkos1";
ESP8266WebServer server(80);

void setup(){
  pinMode(ENA,OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(IN_5, OUTPUT);
  pinMode(IN_6, OUTPUT);

  Serial.begin(9200); //baud rate


  //wifi configuration

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAdress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
// Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}


void Ahead(){ 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
      
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
}


void Reverse(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}

void Right(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
}

void Left(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}

void stop(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
}


void rampdown(){
    s1.write(180);
}

void rampup(){
   s1.write(0);
}


void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") Ahead();
      else if (command == "B") Back();
      else if (command == "L") Left();
      else if (command == "R") Right();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
      else if (command == "U") rampup();
      else if (command == "D") rampdown();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
