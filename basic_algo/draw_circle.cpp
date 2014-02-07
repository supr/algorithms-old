#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/* Question:
Write a program to draw a circle. Don't use any trig functions.

Solution:
"draw an eighth of a circle".

see: http://moishelettvin.blogspot.com/2005/12/programming-interviews-sort-of-exposed.html

Install Opencv to compile this program
*/

void set_pixel(Mat &src, int x, int y, int val) {
	src.at<unsigned char>(y, x) = val;
}

void draw_circle1(Mat &src, int x, int y, int r, int value) {
	for (int x_inc = 0; x_inc <= r; x_inc++) {
		int y_inc = static_cast<int>((sqrt(static_cast<double>(pow(r, 2) - pow(x_inc, 2)))));

		set_pixel(src, x + x_inc, y - y_inc, value);
		set_pixel(src, x + x_inc, y + y_inc, value);
		set_pixel(src, x - x_inc, y + y_inc, value);
		set_pixel(src, x - x_inc, y - y_inc, value);
	}
}

void draw_circle2(Mat &src, int x, int y, int r, int value) {
	for (int y_inc = 0; y_inc <= r; y_inc++) {
		int x_inc = static_cast<int>((sqrt(static_cast<double>(pow(r, 2) - pow(y_inc, 2)))));

		set_pixel(src, x + x_inc, y - y_inc, value);
		set_pixel(src, x + x_inc, y + y_inc, value);
		set_pixel(src, x - x_inc, y + y_inc, value);
		set_pixel(src, x - x_inc, y - y_inc, value);

		set_pixel(src, x + y_inc, y - x_inc, value);
		set_pixel(src, x + y_inc, y + x_inc, value);
		set_pixel(src, x - y_inc, y + x_inc, value);
		set_pixel(src, x - y_inc, y - x_inc, value);
	}
}

void draw_circle3(Mat &src, int x, int y, int r, int value) {
	float x_inc = 0;
	float r2 = r * r;
	float y_inc = r;

	while (y_inc >= x_inc){
		y_inc = sqrt(r2 - (x_inc * x_inc)) + 0.5;

		set_pixel(src, x + x_inc, y + y_inc, value);
		set_pixel(src, x + x_inc, y - y_inc, value);
		set_pixel(src, x - x_inc, y + y_inc, value);
		set_pixel(src, x - x_inc, y - y_inc, value);
		set_pixel(src, x + y_inc, y + x_inc, value);
		set_pixel(src, x + y_inc, y - x_inc, value);
		set_pixel(src, x - y_inc, y + x_inc, value);
		set_pixel(src, x - y_inc, y - x_inc, value);

		x_inc++;
	}
}

int main(int argc, char** argv)
{
	Mat image = Mat::zeros(600, 600, CV_8UC1);
	draw_circle3(image, 300, 300, 200, 255);

	namedWindow("Display window", WINDOW_AUTOSIZE);    // Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	bool write_success = cv::imwrite("circle.jpg", image);

	waitKey(0);                                        // Wait for a keystroke in the window

	return 0;
}