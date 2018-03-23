//LiXiao.Yang 
//@Dorabot .Vision Team .
//3.22.2018
//Define the network of controller.
//This class's work is make decision according to the score and images from capturer.
#ifndef _AUTODRIVER_CONTROLLER__
#define _AUTODRIVER_CONTROLLER__
#include "image.h"
#include "command.h"
#include <iostream>  
#include <winsock2.h>
#include <ws2tcpip.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"Ws2_32.lib") 
class controller {
public:
	controller();
	void connect_capturer(const std::string &ip, unsigned int port);
	void handle_data();
	void make_decision();
private:

	void send_buff(const char*buff, int size);
	void send_command(Command);
	void send_int(int);

	Data receive_data_header();
	int receive_int();
	void receive_img(image *);

	image color;
	image segmentaion;
	int score;
	SOCKET conn = INVALID_SOCKET;
};
#endif