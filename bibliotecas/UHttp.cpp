#include "UHttp.h"

UHttp::UHttp(){}


UHttp::UHttp(const char *server){
  this->device_identificator();

  this->server = server;
  Ethernet.begin(this->mac_byte);

  Serial.print ("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print (Ethernet.localIP ()[thisByte], DEC);
    Serial.print (".");
  }
  Serial.println("");
}

void UHttp::init(){
  this->device_identificator();
  Ethernet.begin(this->mac_byte);

  Serial.print ("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print (Ethernet.localIP ()[thisByte], DEC);
    Serial.print (".");
  }
  Serial.println("");
}


void UHttp::set_server(const char *server){
  this->server = server;
}

bool UHttp::register_device(){
  char *data = NULL;
  data = this->make_client_data(data);
  bool result = this->POST("/client", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool UHttp::register_service(int s){
  char *data = NULL;
  data = this->make_service_data(this->service[s], data);
  bool result = this->POST("/service", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool UHttp::register_data(int s, char* value, int sensitive){
  char *data = NULL;
  data = this->make_raw_data(this->service[s], value, sensitive, data);

  bool result = this->POST("/data", data);
  for(int i = 0; i < strlen(data); i++)
  data[i] = '\0';
  free(data);
  data = NULL;
  return result;
}

bool UHttp::POST(const char* endpoint, char* post_data){
  if(this->eth_client.connect(this->server,HTTP_PORT)){
    this->eth_client.print("POST ");
    this->eth_client.print(endpoint);
    this->eth_client.println(" HTTP/1.1");

    this->eth_client.println("Host: 192.168.0.109");
    this->eth_client.println("Connection: close");
    this->eth_client.println("Content-Type: application/json");
    this->eth_client.print("Content-Length: ");
    this->eth_client.println(strlen(post_data));
    this->eth_client.println();
    this->eth_client.println(post_data);
    Serial.println(post_data);
    delay(110);
    String response = "";
    while(!this->eth_client.available());
    while(this->eth_client.available()){
      response = (this->eth_client.readStringUntil('\r'));
      }
    Serial.println(response);

    this->eth_client.flush();
    this->eth_client.stop();
    delay(500);

    if(response.indexOf("200") == -1){
      return false;
    }

    return true;
  }
  else{
    Serial.print("Connection to server '");
    Serial.print(this->server);
    Serial.println("' failed");
    return false;
  }
}
