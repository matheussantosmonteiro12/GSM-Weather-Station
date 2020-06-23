#include "a7gprs.h"
// SoftwareSerial Serial3(9, 8); // RX, TX



a7gprs::a7gprs(){}

//big (70 char) )string buffer to avoid memory fragmentation
String buff = "0123456789012345678901234567890123456789012345678901234567890123456789";


a7gprs::a7gprs (const char *server){
  this->device_identificator();
  // this->connect();

}

void a7gprs::init(){
  //Serial.begin(19200);
  Serial3.setTimeout(500);
  Serial3.begin(38400);
  //Serial.print("start..........");
  this->device_identificator();
  start_time = millis();
  if(!this->connect()) this->reboot();
}

bool a7gprs::check_uptime(){
	if(millis()-start_time > 300000) reboot();
	return true;
}

void a7gprs::set_server(const char *server){
  this->server = server;
}

bool a7gprs::register_device(){
  char *data = NULL;
  data = this->make_client_data(data);
  bool result = this->POST("/client", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool a7gprs::register_service(int s){
  char *data = NULL;
  data = this->make_service_data(this->service[s], data);
  //Serial.println(data);
  bool result = this->POST("/service", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool a7gprs::register_data(int s, char* value, int sensitive){
  char *data = NULL;
  data = this->make_raw_data(this->service[s], value, sensitive, data);

  bool result = this->POST("/data", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}
bool a7gprs::connect(){
    String imei="111111111111111";
    int a=0, b=0, j=0;
	long time = millis();
	buff.remove(0,70); //Apagando buffer
	Serial3.println("AT+CPOF");
	do{
		this->read_a7gprs();
		if(buff.indexOf("ERROR") != -1 || millis()-time > 20000){
			Serial3.println("AT+CPOF");
			delay(500);
		}
	}while(buff.indexOf("OK") == -1 && check_uptime());
	do{
		delay(8000);
		do{
			Serial3.println("AT+IPR=38400");
			this->read_a7gprs();
			delay(1000);
		}while(buff.indexOf("OK") == -1 && check_uptime());
	
		Serial3.println("AT+CFUN=0");
		do{
			delay(300);
			this->read_a7gprs();
		}while(buff.indexOf("OK") == -1 && check_uptime());
		Serial3.println("AT+CFUN=1");
		do{
			delay(300);
			this->read_a7gprs();
		}while(buff.indexOf("OK") == -1 && check_uptime());
		Serial3.println("AT+CSTT=""timbrasil.br"",""tim"",""tim");
		do{
			delay(300);
			this->read_a7gprs();
		}while(buff.indexOf("OK") == -1 && check_uptime());
		Serial3.println("AT+CIICR");
		do{
			delay(300);
			this->read_a7gprs();
			if(buff.indexOf("ERROR") != -1){
				return false;
			}
		}while(buff.indexOf("OK") == -1 && check_uptime());
		Serial3.println("AT+CIFSR");
		do{
			delay(300);
			this->read_a7gprs();
			if(buff.indexOf("ERROR") != -1)
				return false;;
		}while(buff.indexOf("OK") == -1 && check_uptime());
	}while(buff.indexOf("ERROR") != -1 && check_uptime());
    // Serial.println(imei);
    Serial3.println("AT+EGMR=2,7");
	delay(300);
	this->read_a7gprs();
	b=buff.indexOf("EGMR:");
	if(b!=-1){
		imei=buff.substring(b+5,b+15+5);
	}else {
		return false;
	}
    // Serial.println(imei);
    this->set_mac(imei);
	return true;
}

void a7gprs::read_a7gprs(){
	buff.remove(0,70); //Apagando buffer
	while (Serial3.available() && check_uptime()) {
		buff += Serial3.readString();
		Serial.println("->>"+buff); //For Debug Porpouses
	}
}

bool a7gprs::POST(const char* endpoint, char* post_data){
    int tamanho;
    String controle;
    tamanho=strlen(post_data);
	Serial3.println("AT+CIPSTART=""TCP"",""uiot-gateway.herokuapp.com"",""80");
	do{
		delay(200);
		this->read_a7gprs();
		if(buff.indexOf("ERROR") != -1)Serial3.println("AT+CIPSTART=""TCP"",""uiot-gateway.herokuapp.com"",""80");
	}while(buff.indexOf("OK") == -1 && check_uptime());
	buff.remove(0,70); //Apagando buffer
	Serial3.println("AT+CIPSTATUS");
	do{
		this->read_a7gprs();
	}while(buff.indexOf("OK") == -1 && check_uptime());
	if(buff.indexOf("CONNECT") == -1){
		Serial3.println("AT+CIPCLOSE");
		this->read_a7gprs();
		//Serial.println("Fail at connect");
		return false;
	}
	
    Serial3.println("AT+CIPSEND");
	delay(300);
    this->read_a7gprs();
    Serial3.print("POST ");
	delay(300);
    this->read_a7gprs();
    Serial3.print(endpoint);
	delay(300);
    this->read_a7gprs();
    Serial3.println(" HTTP/1.1");
	delay(300);
    this->read_a7gprs();
    Serial3.println("Connection: close");
	delay(300);
    this->read_a7gprs();
    Serial3.println("Host: uiot-gateway.herokuapp.com");
	delay(300);
    this->read_a7gprs();
    Serial3.println("Content-Type: application/json");
	delay(300);
    this->read_a7gprs();
    Serial3.print("Content-Length: ");
	delay(300);
    this->read_a7gprs();
    Serial3.println(strlen(post_data));
	delay(300);
    this->read_a7gprs();
    Serial3.println("");
    this->read_a7gprs();

    if(tamanho>126){
    this->string1(post_data,0,63);
	delay(300);
    this->read_a7gprs();
    this->string1(post_data,63,126);
	delay(300);
    this->read_a7gprs();
    this->string1(post_data,126,tamanho);
	delay(300);
    this->read_a7gprs();
  }else{
    this->string1(post_data,0,63);
	delay(300);
    this->read_a7gprs();
    this->string1(post_data,63,tamanho);
	delay(300);
    this->read_a7gprs();
  }
    Serial3.println("");
    this->read_a7gprs();

	buff.remove(0,70); //Apagando buffer
    Serial3.println(char(26));
	delay(5000);
	  this->read_a7gprs();
	if(buff.indexOf("200") == -1){
		Serial3.println("AT+CIPCLOSE");
		this->read_a7gprs();
		// Serial.println("answer not 200");
		return false;
	}
	
    Serial3.println("AT+CIPCLOSE");
	delay (500);
	this->read_a7gprs();


  return true;
}

 void a7gprs::string1(char* post,int comeco,int tamanho){
   for(int i=comeco;i<tamanho;i++){
     Serial3.print(post[i]);
   }
   }

// String a7gprsgprs::GPS() {
//  int j=0,i=16;
//  char x0[11],y0[11];
//  String aa;
// //  Serial.println("AT");
// // this->connect();
// Serial.println("AT");
// this->read_a7gprs();//Print GSM Status an the Serial Output;
// //  Serial.println("AT+SAPBR=1,1");
// Serial.println("AT+SAPBR=1,1");
// this->read_a7gprs();
// //  Serial.println("AT+CIPGSMLOC=1,1");
// Serial.println("AT+CIPGSMLOC=1,1");  // Definimos o número do destinatário em formato internacional
// delay(700);
// this->read_a7gprs();
// delay(4000);
// aa = Serial.readString();
// // delay(5000);
// Serial.println(aa);
//
//   return aa;
// }

void a7gprs::reboot(){
	digitalWrite(7, HIGH);
}