//LiXiao.Yang 
//@Dorabot .Vision Team .
//3.21.2018
//Define the image buffer for transfer.
#ifndef _AUTODRIVER_IMG__
#define _AUTODRIVER_IMG__
#include<iostream>
#include<fstream>
#define IMG_MAX_SIZE 5000000
struct image {
	unsigned int size;
	char *buff;
	image():size(1) {
		//image size should be controled below 5M
		buff = new char[IMG_MAX_SIZE];
	}
	void save_to_file(const std::string filename) {
	}
	void load_from_file(const std::string filename) {
		std::ifstream t;
		int length;
		t.open(filename);
		t.seekg(0, std::ios::end);
		length = t.tellg();
		if (length > IMG_MAX_SIZE)
			std::abort();
		t.seekg(0, std::ios::beg);
		t.read((char *)buff, length);
		t.close();
	}
	void copy_from_mem(unsigned char*begin, unsigned int length) {
		if (length > IMG_MAX_SIZE)
			std::abort();
		size = length;
		for (int i = 0; i < length; i++) {
			buff[i] = begin[i];
		}
	}
};
#endif