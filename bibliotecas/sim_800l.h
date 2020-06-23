#ifndef USIM800L_H
#define USIM800L_H

#include<IPAddress.h>

#ifndef HTTP_PORT
#define HTTP_PORT  8000
#endif



#include <SoftwareSerial.h>

#include "BaseProtocol.h"
class sim_800l : public BaseProtocol{
    public:
        sim_800l();
        sim_800l(const char*);
        void init();
        void set_server(const char*);
        bool register_device();
        bool register_service(int);
        bool register_data(int, char*, int);
        bool POST(const char*, char*);
        void read_sim800();
        String GPS();
        // void conect();
        void connect();
    private:
        const char* server;


};

#endif
