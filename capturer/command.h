//LiXiao.Yang 
//@Dorabot .Vision Team .
//3.22.2018
//Define the Command and Data header of the autodriver.
#ifndef _AUTODRIVER_COMMAND__
#define _AUTODRIVER_COMMAND__
enum class Command
{
	forward_left,
	forward_right,
	forward,
	backward_right,
	backward_left,
	backward,
	reset,

};
enum class Data {
	color_img,//capturer -> controller
	segmentaion_img, //capturer -> controller
	depth_img, //capturer -> controller
	score//capturer -> controller
};


#endif