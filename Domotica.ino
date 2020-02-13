#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/*************
 * Datos Red *
**************/
const char* ssid = "TeleCentro-39b0";                  // Your wifi Name       
const char* password = "FWMMHDNMJDZ5";

/*************
 * Pines     *
*************/
int temp=A0;
int l1=12; //D6
int l2=13; //D7
int cer=15; //D8
int vtna=14;//D5



void setup() {
  Pines();
 Serial.begin(115200);
 WIFI();

  Serial.println("");
  Serial.print("Id= ");
  Serial.println(ESP.getChipId());
}


void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String LdrValueSend, postData;
  int ldrvalue=analogRead(temp);  //Read Analog value of LDR
  LdrValueSend = String(ldrvalue);   //String to interger conversion
 
  //Post Data
  //postData = "ldrvalue=" + LdrValueSend;

  postData = "Temperatura=" + (String)analogRead(temp)+ "&Led1= " + (String)digitalRead(l1)  + "&Led2= " + (String)digitalRead(l2)+"&Switch= " + (String)digitalRead(vtna)+ "Id= " +ESP.getChipId();
  

  
  http.begin("http://wi151875.ferozo.com/InsertDB.asp");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  //Serial.println("LDR Value=" + ldrvalue);
  Serial.print("httpCode:");
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("payload: ");
  Serial.println(payload);    //Print request response payload
  Serial.println("LDR Value=" + LdrValueSend);
  
  http.end();  //Close connection

  

  delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);
}




////////////////////////////////////////////////
//////////////////FUNCIONES/////////////////////
////////////////////////////////////////////////

void WIFI(){
  WiFi.begin(ssid, password);   
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conecta a ");
  Serial.print(ssid);
  Serial.println("");
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
  }

void Pines(){
 pinMode (temp, INPUT);
 pinMode (l1, OUTPUT);
 pinMode (l2, OUTPUT);
 pinMode (cer, OUTPUT);
 pinMode (vtna, INPUT);
  }
