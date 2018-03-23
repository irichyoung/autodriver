#include "controller.h"
int main() {
	controller ctr;
	ctr.connect_capturer("10.0.9.224", 18381);
	//ctr.connect_capturer("127.0.0.1", 18381);
	for (;;) {
		//retrive data and make decision.
		ctr.handle_data();
	}
}