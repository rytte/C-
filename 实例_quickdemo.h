#ifndef QUICKDEMO_H
#define QUICKDEMO_H

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class QuickDemo
{
public:
	QuickDemo();

	void imageSplicing(void);
	void colorSpace(void);
	void mat_creation(void);
	void pixel_visit(void);
	void operators_demo(void);
	void tracking_bar(void);
	void color_style(void);
	void bitwise(void);
	void channels(void);
	void inrange(void);
	void pixel_statistic(void);
	void geometry_drawing(void);
	void random_drawing(void);
	void polyline_drawing(void);
	void mouse_drawing(void);
	void norm_demo(void);
	void resize_demo(void);
	void flip_demo(void);
	void rotate_demo(void);
	void video_demo(void);
	void histogram_demo(void);
	void histogram_2d_demo(void);
	void histogram_eq_demo(void);
	void blur_demo(void);
	void gaussian_blur_demo(void);
	void bifilter_demo(void);


private:
	Mat image;
};

#endif // QUICKDEMO_H

