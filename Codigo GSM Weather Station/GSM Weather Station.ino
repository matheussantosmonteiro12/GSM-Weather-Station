//pin2=temperatura e umidade
//pin3=luz 
//pin4=Chuva
#include <LiquidCrystal.h>
#include <a7gprs.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2 
const int sensor_ldr = 3;

a7gprs device;
int service1,service2,service3,service4,service5;
float* lat_long;
String s="1";
float pino_d = 4; 
DHT dht(DHTPIN, DHTTYPE);


void setup() { 
  Serial.setTimeout(200);
  Serial.begin(38400);
   pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  device.set_server("uiot-gateway.herokuapp.com");
    service1 = device.create_service(0, "getTemperatura", "ºC", 1, "weather_box");
    service2 = device.create_service(1, "getHumidity", "%", 1, "weather_box");
    service3 = device.create_service(2, "getLuz", "%", 1, "weather_box");
    service4 = device.create_service(3, "getrain", "%", 1, "weather_box");
    service5 = device.create_service(4, "getCO", "ppm", 1, "weather_box");
    lat_long = (float*)malloc(2*sizeof(float));
    
    device.init();
    dht.begin();
    pinMode(pino_d, INPUT);
}

void loop() {
  bool r;
//  digitalWrite(7, LOW);
  do{
    s=read_Temperature();
    r=device.send_data(service1,s.c_str(),0);
    if(!r) {
      device.connect();
    }
  }while(!r);
  do{
    s=read_Humidity();
    r=device.send_data(service2,s.c_str(),0);
    if(!r) {
      device.connect();
    }
  }while(!r);
  do{
    s=read_light();
    r=device.send_data(service3,s.c_str(),0);
    if(!r) {
      device.connect();
    }
  }while(!r);
  do{
    s=read_rain();
    r=device.send_data(service4,s.c_str(),0);
    if(!r) {
      device.connect();
    }
  }while(!r);
  do{
    s=read_CO();
    r=device.send_data(service5,s.c_str(),0);
    if(!r) {
      device.connect();
    }
  }while(!r);
  digitalWrite(7, HIGH);
  delay(1000);
}



//--------------------------------------------------------------------------------------------------------------------------------------------------
String read_Temperature(){
    String temperatura = "";
    float t = dht.readTemperature();
    if (isnan(t)) {
//    Serial.println("Failed to read from DHT sensor!");
    return temperatura;
    }
    temperatura = String(t);
    //Serial.println(floatToString(temperatura, t, 2));
    return temperatura;
  }
//------------------------------------------------------------------------------------------------------------------------------------------------
String read_Humidity(){
  String Humidity = "";
  float h = dht.readHumidity();
  if (isnan(h)) {
//    Serial.println("Failed to read from DHT sensor!");
    return Humidity;
    }
    Humidity=String(h);
    //Serial.println(floatToString(Humidity, h, 2));
    return Humidity;
  }
 //---------------------------------------------------------------------------------------------------------------------------------------------------------
//Sensor de luz
String read_light(){
  float leitura=analogRead(sensor_ldr);  
  return String((1023 - leitura)*0.1);
}
  //--------------------------------------------------------------------------------------------------------------------------------------------------
//sensor de chuva e neve 
  
String read_rain(){
  float leitura = analogRead(pino_d);
  float porcentagem ;
  porcentagem = (1000 - leitura)*0.1;
  if(porcentagem <= 0){
    return "0";
  }else{
    return String(porcentagem);
  }
}

//--------------------------------------------------------------------
//sensor de co em ppm, Mq7 pin A0

String read_CO(){
  float RS_gas = 0;
  float ratio = 0;
  float sensorValue = 0;
  float sensor_volt = 0;
  float R0 = 7200.0;
  sensorValue = analogRead(A0);
  sensor_volt = sensorValue/1024*5.0;
  RS_gas = (5.0-sensor_volt)/sensor_volt;
  ratio = RS_gas/R0; //Replace R0 with the value found using the sketch above
  return String(pow((1538.46 * ratio),-1.709));
} 
