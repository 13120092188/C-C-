#include <fstream>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void write_pixel_to_txt(std::string const &name, ofstream &stream)
{
	IplImage* image;
	CvScalar s;

	/*for (int i = 1; i <= 52; i++) {
		string str = to_string(i) + ".png";*/
		image = cvLoadImage(name.c_str());
		for (int row = 0; row < image->height; row += 1) {
			for (int col = 0; col < image->width; col += 1) {
				s = cvGet2D(image, row, col);
				int mu = (s.val[0] + s.val[1] + s.val[2]) / 3;//照片每个像素点RGB三通道的均值  
				if (mu < 55)
					stream << "88";
				else if (mu < 105)
					stream << "++";
				else if (mu < 130)
					stream << "--";
				else if (mu < 160)
					stream << "..";
				else
					stream << "  ";
			}
			stream << endl;
		}
	//}
}

int main()
{
	ofstream stream("莉哥.txt");
	write_pixel_to_txt("48.png", stream);

	system("pause");
	return 0;
}