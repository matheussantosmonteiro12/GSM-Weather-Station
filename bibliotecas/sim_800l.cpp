#include "sim_800l.h"
//SoftwareSerial Serial(0, 1); // RX, TX


sim_800l::sim_800l(){}


sim_800l::sim_800l (const char *server){
  this->device_identificator();
  // this->connect();

}

void sim_800l::init(){
  Serial.begin(9600);
  //delay(100000);
  this->device_identificator();
  // this->connect();
}


void sim_800l::set_server(const char *server){
  this->server = server;
}

bool sim_800l::register_device(){
  char *data = NULL;
  data = this->make_client_data(data);
  bool result = this->POST("/client", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool sim_800l::register_service(int s){
  char *data = NULL;
  data = this->make_service_data(this->service[s], data);
  bool result = this->POST("/service", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool sim_800l::register_data(int s, char* value, int sensitive){
  char *data = NULL;
  data = this->make_raw_data(this->service[s], value, sensitive, data);

  bool result = this->POST("/data", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}
void sim_800l::connect(){
    String apn = "timbrasil.br";                       //APN
    String apn_u = "tim";                     //APN-Username
    String apn_p = "tim";                     //APN-Password
    //Serial.println("AT");
    Serial.println("AT");
    this->read_sim800();//Print GSM Status an the Serial Output;
    //Serial.println("AT+SAPBR=3,1,Contype,GPRS");
    Serial.println("AT+SAPBR=3,1,Contype,GPRS");
    this->read_sim800();
    //Serial.println("AT+SAPBR=3,1,APN," + apn);
    Serial.println("AT+SAPBR=3,1,APN," + apn);
    this->read_sim800();
    //Serial.println("AT+SAPBR=3,1,USER," + apn_u);
    Serial.println("AT+SAPBR=3,1,USER," + apn_u); //Comment out, if you need username
    this->read_sim800();
    //Serial.println("AT+SAPBR=3,1,PWD," + apn_p);
    Serial.println("AT+SAPBR=3,1,PWD," + apn_p); //Comment out, if you need password
    this->read_sim800();
    //Serial.println("AT+SAPBR =1,1");
    Serial.println("AT+SAPBR =1,1");
    this->read_sim800();
    //Serial.println("AT+SAPBR=2,1");
    Serial.println("AT+SAPBR=2,1");
    this->read_sim800();
}

void sim_800l::read_sim800(){
  Serial.readString();
}

bool sim_800l::POST(const char* endpoint, char* post_data){
//  Serial.println(post_data);
  Serial.println("AT+HTTPINIT");
  this->read_sim800();
  //Serial.println("AT+HTTPPARA=CID,1");
  Serial.println("AT+HTTPPARA=CID,1");
  this->read_sim800();
  //Serial.print("AT+HTTPPARA=URL,http://uiot-gateway.herokuapp.com");
  //Serial.println(endpoint);
  Serial.print("AT+HTTPPARA=URL,http://uiot-gateway.herokuapp.com");
  Serial.println(endpoint);
  this->read_sim800();
  //delay(1000);
  //Serial.println("AT+HTTPPARA=CONTENT");
  Serial.println("AT+HTTPPARA=CONTENT,application/json");
  this->read_sim800();
  //delay(1000);
  //Serial.print("AT+HTTPDATA=");
//  Serial.println(strlen(post_data));
  Serial.print("AT+HTTPDATA=");
  Serial.print(strlen(post_data));
  Serial.println(",10000");
  this->read_sim800();
  Serial.println(post_data);
  this->read_sim800();
  //Serial.println("AT+HTTPACTION=1");
  Serial.println("AT+HTTPACTION=1");
  this->read_sim800();
  //Serial.println("AT+HTTPREAD");
  Serial.println("AT+HTTPREAD");
  this->read_sim800();
  //Serial.println("AT+HTTPTERM");
  Serial.println("AT+HTTPTERM");
  this->read_sim800();
  return true;
}

String sim_800l::GPS() {
 int j=0,i=16;
 char x0[11],y0[11];
 String aa;
//  Serial.println("AT");
// this->connect();
Serial.println("AT");
this->read_sim800();//Print GSM Status an the Serial Output;
//  Serial.println("AT+SAPBR=1,1");
Serial.println("AT+SAPBR=1,1");
this->read_sim800();
//  Serial.println("AT+CIPGSMLOC=1,1");
Serial.println("AT+CIPGSMLOC=1,1");  // Definimos o número do destinatário em formato internacional
delay(700);
this->read_sim800();
delay(4000);
aa = Serial.readString();
// delay(5000);
Serial.println(aa);

  return aa;
}
