//LiXiao.Yang 
//@Dorabot .Vision Team .
//3.21.2018
//Define the network of capturer.
//This class's work is capture screen in certain rate and send it to the AI controller.
#ifndef _AUTODRIVER_CAPTURER__
#define _AUTODRIVER_CAPTURER__
#include "image.h"
#include "command.h"
#include <winsock2.h>
#include <ws2tcpip.h>
class capturer {
public:
	capturer();
	void accept_controller(unsigned int port);
	void send_img();
	void send_score(int);
	void retrive_command();
	void capture_img();
private:
	void send_buff(const char*buff, int size);
	void send_data_header(Data);
	void send_int(int);
	image color;
	image segmentaion;
	SOCKET listener = INVALID_SOCKET;
	SOCKET conn = INVALID_SOCKET;
};
#endif