#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"controller.h"
#include <thread>
#include <stdlib.h>
controller::controller(){
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) != 0)
	{
		std::cout << "create ws32 failed." << std::endl;
		std::abort();
	}
}
void controller::connect_capturer(const std::string &ip, unsigned int port) {
	conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn == INVALID_SOCKET)
	{
		std::cout << "create socket failed." << std::endl;
		std::abort();
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	saServer.sin_port = htons(port);
	if (connect(conn, (sockaddr*)&saServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		std::cout << "connect fail." << WSAGetLastError() << std::endl;
		closesocket(conn);
		std::abort();
	}
	std::cout << "connect success." << std::endl;
}
void controller::send_int(int data) {
	if (send(conn, (char*)&data, sizeof(data), 0) == SOCKET_ERROR)
	{
		std::cout << "send int fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
void controller::send_buff(const char*buff, int size) {
	if (send(conn, buff, size, 0) == SOCKET_ERROR) {
		std::cout << "send buff error." << std::endl;
		std::abort();
	}
}
void controller::send_command(Command cmd) {
	if (send(conn, (char*)&cmd, sizeof(Command), 0) == SOCKET_ERROR)
	{
		std::cout << "send int fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
Data controller::receive_data_header() {
	char buff[sizeof(Data)];
	if (recv(conn, buff, sizeof(Data), 0) <= 0) {
		std::cout << "recv data failed." << std::endl;
		std::abort();
	}
	Data data = *(Data*)buff;
	return data;
}
int  controller::receive_int() {
	char buff[sizeof(int)];
	if (recv(conn, buff, sizeof(int), 0) <= 0) {
		std::cout << "recv int failed." << std::endl;
		std::abort();
	}
	//std::cout << "Received int."<< *(int*)buff << std::endl;
	return *(int*)buff;
}
void controller::receive_img(image *img) {
	img->size = receive_int();
	std::cout << "Receive Img Size." << img->size<<std::endl;
	int len = 0;
	while (len < img->size) {
		int r = recv(conn, &img->buff[len], img->size - len, 0);
		//int r = recv(conn, test, img->size - len, 0);
		if (r <= 0) {
			std::cout << "Receive img failed." << WSAGetLastError()<< std::endl;
			std::abort();
		}
		len += r;
	}
	std::cout << "Receive Img Buffer." << img->size << std::endl;
}
void controller::handle_data() {
	bool Bcimg = false, Bsimg = false, Bscore = false;
	for (;;) {
		if (Bcimg && Bsimg && Bscore) {
			make_decision();
			Bcimg = false;
			Bsimg = false;
			Bscore = false;
		}
		switch (receive_data_header()) {
		case Data::color_img:
			std::cout << "Receive Color_Img_Header." << std::endl;
			receive_img(&color);
			Bcimg = true;
			break;
		case Data::segmentaion_img:
			std::cout << "Receive Segmentation_Img_Header." << std::endl;
			receive_img(&segmentaion);
			Bsimg = true;
			break;
		case Data::score:
			std::cout << "Receive Score_Img_Header." << std::endl;
			score = receive_int();
			std::cout << "Receive Score." <<score<< std::endl;
			Bscore = true;
			break;
		}
	}
}
void controller::make_decision() {
	switch(rand() % 4){
		case 0:
			std::cout << "Decision_Forward." << std::endl;
			send_command(Command::forward);
			break;
		case 1:
			std::cout << "Decision_Backward." << std::endl;
			send_command(Command::backward);
			break;
		case 2:
			std::cout << "Decision_Forward_Left." << std::endl;
			send_command(Command::forward_left);
			break;
		case 3:
			std::cout << "Decision_Forward_Right." << std::endl;
			send_command(Command::forward_right);
			break;
	}
}