#include "QuadTree.h"
//#include <time.h>

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

double calculateAccuracy(Mat& original, Mat& decoded) {
	int n = original.rows * original.cols;
	double mse = 0;
	for (int i = 0; i < original.rows; i++) {
		for (int j = 0; j < original.cols; j++) {
			int diff = (int)original.at<uchar>(i, j) - (int)decoded.at<uchar>(i, j);
			mse += pow(diff, 2);
		}
	}
	double rmse = mse / n;
	double accuracy = (1 - (rmse / pow(255.0,2))) * 100.0;
	return accuracy;
}

void intArrayToImage(int** arr, int rows, int cols, string filename) {
	Mat image(rows, cols, CV_8UC1);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int pixelValue = arr[i][j];
			image.at<uchar>(i, j) = (uchar)pixelValue;
		}
	}
	imwrite(filename, image);
}


int main() {
	srand(time(NULL));
	int option;
	int height = 0;
	int width = 0;
	QuadTree t;
	TwoDLL ll;
	while (true) {
		do {
			cout << "Select Option: \n1. Load Image, Create Tree And Write to File\n2. Read File & Create Tree\n3. Compare Images\nEnter Option: ";
			cin >> option;
		} while (option < 1 || option>3);
		if (option == 1) {
			Mat img = imread("./B2DBy.png");
			if (img.empty())
			{
				cout << "Could not open or find the image" << endl;
				return -1;
			}
			height = img.rows;
			width = img.cols;
			Mat gray_img;
			cvtColor(img, gray_img, COLOR_BGR2GRAY);
			int** img_data = new int* [height];
			for (int i = 0; i < height; i++) {
				img_data[i] = new int[width];
			}
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					img_data[i][j] = static_cast<int>(gray_img.at<uchar>(i, j));
					//cout << img_data[i][j] << "\t"/*;*/
				}
				//cout << endl;
			}
			TwoDLL d;
			d.convertTo2dLL(img_data, height, width);
			t.createTree(d, height, width);
			t.writeToFile();
			for (int i = 0; i < height; i++)
			{
				delete[] img_data[i];
			}
			delete[] img_data;
			cout << "Data Written To File\n";
		}
		else if (option == 2) {
			t.readFile();
		}
		else {
			int** decodedImgArr = t.treeToDMA();
			intArrayToImage(decodedImgArr, 4, 4, "image1.jpg");
			Mat original = imread("./B2DBy.png", IMREAD_GRAYSCALE);
			Mat decoded = imread("./image1.jpg", IMREAD_GRAYSCALE);
			double accuracy = calculateAccuracy(original, decoded);
			cout << "Accuracy: " << accuracy << "%" << endl;
		}
	}
	return 0;
}

