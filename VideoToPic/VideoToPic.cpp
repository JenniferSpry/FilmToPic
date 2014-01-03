#include <opencv2\opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

VideoCapture videoCapture;
string path = "C:\\test\\m12";
string fileName = "test";
Mat result(1500, 1200, CV_8UC3, Scalar(0,0,0)); 
int width = 100;
int height = 60;
int x = 0;
int y = 0;
vector<int> compression_params;
int imagenumber = 1;

string itos(int i){
	// integer to string helpermethod
	stringstream ss;
	ss << i;
	return ss.str();
}

void save(Mat &result){
	imwrite(fileName+"_"+itos(imagenumber)+".jpg", result, compression_params);
	cout << "Saved: " << fileName+"_"+itos(imagenumber)+".jpg" << endl;
}

int main(){
	cout << "Please enter the path to your film:" << endl;
	cout << "(Like this: C:\\\\Users\\\\Bob\\\\Videos\\\\film.avi)" << endl;
	cin >> path;
	cout << "Enter a name for the image files:" << endl;
	cin >> fileName;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY );
	compression_params.push_back(100);

	//namedWindow("Video");
	Mat now;
	VideoCapture videoCapture;

	cout << "Opening: " << path << endl;
	videoCapture.open(path);

	if(videoCapture.isOpened()) {
		cout << "...creating image..." << endl;
		while(true){
			if(!videoCapture.grab()){
				break;
			}
			int frame = videoCapture.get(CV_CAP_PROP_POS_FRAMES);

			if (frame%60 == 0){
				videoCapture.retrieve(now);
				//resize
				Size newSize(width, height);
				resize(now, now, newSize);

				//insert
				Rect roi(Point(x, y), now.size()); //region of interest
				Mat destinationROI = result(roi);
				now.copyTo(destinationROI);

				x = x + width;
				if( x > result.cols-width){
					x = 0;
					y = y + height;
					if (y > result.rows-height){
						save(result);
						x = 0;
						y = 0;
						imagenumber++;
						result.setTo(Scalar(0,0,0));
						cout << "...creating image..." << endl;
					}
				}
				//imshow("Video", result);
			}
			////End with key
			//int key = waitKey(10);
			//if (key != -1){
			//	break;
			//}
		}
		save(result);
	}
	videoCapture.release();
	cout << "Finished!" << endl;
	cout << "Type x and press enter to exit" << endl;
	cin >> path;
	return 0;
}