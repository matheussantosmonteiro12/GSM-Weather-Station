#ifndef Ua7gprs_H
#define Ua7gprs_H

#include<IPAddress.h>

#ifndef HTTP_PORT
#define HTTP_PORT  8000
#endif



#include <SoftwareSerial.h>

#include "BaseProtocol.h"
class a7gprs : public BaseProtocol{
    public:
        a7gprs();
        a7gprs(const char*);
        void init();
        void set_server(const char*);
        bool register_device();
        bool register_service(int);
        bool register_data(int, char*, int);
        bool POST(const char*, char*);
        void read_a7gprs();
        //String GPS();
        // void conect();
        bool connect();
        void reboot();
        void string1(char*,int,int);
		bool a7gprs::check_uptime();
        void(* Soft_reset) (void) = 0;
    private:
        const char* server;
		double start_time;


};

#endif
