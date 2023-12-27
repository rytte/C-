#include <opencv2/opencv.hpp>
#include <iostream>
#include <quickdemo.h>

using namespace std;
using namespace cv;


int main()
{

	QuickDemo qd;
	//qd.imageSplicing();
	//qd.colorSpace();
	//qd.mat_creation();
	//qd.pixel_visit();
	//qd.operators_demo();
	//qd.tracking_bar();
	//qd.color_style();
	//qd.bitwise();
	//qd.channels();
	//qd.inrange();
	//qd.pixel_statistic();
	//qd.geometry_drawing();
	//qd.random_drawing();
	//qd.polyline_drawing();
	//qd.mouse_drawing();
	//qd.norm_demo();
	//qd.resize_demo();
	//qd.rotate_demo();
	//qd.video_demo();
	//qd.histogram_demo();
	//qd.histogram_2d_demo();
	//qd.histogram_eq_demo();
	//qd.blur_demo();
	//qd.gaussian_blur_demo();
	qd.bifilter_demo();


	waitKey(0);
	destroyAllWindows();
	return 0;
}
