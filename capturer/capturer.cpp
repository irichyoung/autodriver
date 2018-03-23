#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "capturer.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512

capturer::capturer() {
	WSADATA wsaData;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		std::abort();
	}
	std::cout << "Init success." << std::endl;
}
void capturer::accept_controller(unsigned int port) {
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener == INVALID_SOCKET)
	{
		std::cout << "create listener failed." << WSAGetLastError() << std::endl;
		std::abort();
	}
	sockaddr_in sListen;
	sListen.sin_family = AF_INET;
	sListen.sin_addr.s_addr = htonl(INADDR_ANY);
	sListen.sin_port = htons(port);
	int nSize;
	nSize = sizeof(sockaddr_in);
	if (bind(listener, (sockaddr*)&sListen, nSize) == SOCKET_ERROR)
	{
		closesocket(listener);
		std::cout << "bind failed." << WSAGetLastError() << std::endl;
		std::abort();
	}
	if (listen(listener, 1) == SOCKET_ERROR)
	{
		closesocket(listener);
		std::cout << "listen failed." << WSAGetLastError() << std::endl;
		std::abort();
	}
	std::cout << "Start To Listen." << std::endl;
	sockaddr_in saRemote;
	nSize = sizeof(sockaddr_in);
	conn = accept(listener, (sockaddr*)&saRemote, &nSize);
	if (conn == INVALID_SOCKET)
	{
		std::cout << "accept failed." << WSAGetLastError() << std::endl;
		std::abort();
	}
	std::cout << "Someone connected." << std::endl;
}
void capturer::send_int(int data) {
	if (send(conn, (char*)&data, sizeof(data), 0) == SOCKET_ERROR)
	{
		std::cout << "capturer send int fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
void capturer::send_buff(const char*buff, int size) {
	if (send(conn, buff, size, 0) == SOCKET_ERROR) {
		std::cout << "send buff error." << std::endl;
		std::abort();
	}
}
void capturer::send_data_header(Data cmd) {
	if (send(conn, (char*)&cmd, sizeof(Data), 0) == SOCKET_ERROR)
	{
		std::cout << "send data header fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
void capturer::send_img() {
	send_data_header(Data::color_img);
	std::cout << "Send Color_Img_Header." << std::endl;
	send_int(color.size);
	std::cout << "Send Size." << std::endl;
	send_buff((const char*)color.buff, color.size);
	std::cout << "Send Buffer." << std::endl;
	send_data_header(Data::segmentaion_img);
	std::cout << "Send Segmentaion_Img_Header." << std::endl;
	send_int(segmentaion.size);
	std::cout << "Send Size." << std::endl;
	send_buff((const char*)segmentaion.buff, segmentaion.size);
	std::cout << "Send Buffer." << std::endl;
}
void capturer::send_score(int score) {
	send_data_header(Data::score);
	std::cout << "Send Score Header." << std::endl;
	send_int(score);
	std::cout << "Send Score." << std::endl;
}
void capturer::retrive_command() {
	char cmd[sizeof(Command)];
	if (recv(conn, (char *)cmd, sizeof(Command), 0) <= 0) {
		std::cout << "retrive command failed." << std::endl;
		std::abort();
	}
	switch (*(Command *)cmd) {
	case Command::backward:
		std::cout << "Receive Backward CMD." << std::endl;
		break;
	case Command::forward:
		std::cout << "Receive Forward CMD." << std::endl;
		break;
	case Command::forward_right:
		std::cout << "Receive Forward_Right CMD." << std::endl;
		break;
	case Command::forward_left:
		std::cout << "Receive Forward_Left CMD." << std::endl;
		break;
	}
}
void capturer::capture_img() {
}
