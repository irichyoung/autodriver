#include "capturer.h"
#include <thread>
#include <Windows.h>
int main(){
	capturer cap;
	cap.accept_controller(18381);
	//create a thread to capture.
	for (;;) {
		Sleep(2000);
		cap.capture_img();
		cap.send_img();
		cap.send_score(100);
		cap.retrive_command();
	};
}
