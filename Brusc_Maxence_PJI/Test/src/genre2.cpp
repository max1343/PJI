/*
 * genre2.cpp
 *
 *  Created on: 2016?3?16?
 *      Author: fan
 */




#include <opencv.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cv;

void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels)
{
	std::ifstream file(filename.c_str(), ifstream::in);//c_str()函数可用可不用，无需返回一个标准C类型的字符串
	char separator =';';
	if (!file) {
		string error_message ="No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file,line))//从文本文件中读取一行字符，未指定限定符默认限定符为“/n”
	{
		stringstream liness(line);//这里采用stringstream主要作用是做字符串的分割
		getline(liness, path, separator);//读入图片文件路径以分好作为限定符
		getline(liness, classlabel);//读入图片标签，默认限定符
		if(!path.empty()&&!classlabel.empty())//如果读取成功，则将图片和对应标签压入对应容器中
		{
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}



int main(int argc,char*argv[])
{
    String csvPath = "/Users/pro/Desktop/PJI/ExGenre/at.txt";
    vector<Mat> images;
    vector<int> labels;
    read_csv(csvPath,images,labels);

    Ptr<FaceRecognizer> modelPCA = createEigenFaceRecognizer();
    modelPCA->train(images,labels);
    modelPCA->save("/Users/pro/Desktop/PJI/ExGenre/PCA_Model.xml");

    Ptr<FaceRecognizer> modelFisher = createFisherFaceRecognizer();
    modelFisher->train(images,labels);
    modelFisher->save("/Users/pro/Desktop/PJI/ExGenre/Fisher_Model.xml");

    Ptr<FaceRecognizer> modelLBP = createLBPHFaceRecognizer();
    modelLBP->train(images,labels);
    modelLBP->save("/Users/pro/Desktop/PJI/ExGenre/LBP_Model.xml");

    //Ptr<FaceRecognizer> modelPCA = createEigenFaceRecognizer();
    //Ptr<FaceRecognizer> modelFisher = createFisherFaceRecognizer();
    //Ptr<FaceRecognizer> modelLBP = createLBPHFaceRecognizer();

    modelPCA->load("/Users/pro/Desktop/PJI/ExGenre/PCA_Model.xml");
    modelFisher->load("/Users/pro/Desktop/PJI/ExGenre/Fisher_Model.xml");
    modelLBP->load("/Users/pro/Desktop/PJI/ExGenre/LBP_Model.xml");

    Mat testImage = imread("/Users/pro/Desktop/PJI/ExGenre/测试样本/男性测试样本/face_480.bmp",0);
    int predictPCA = modelPCA->predict(testImage);
    int predictLBP = modelLBP->predict(testImage);
    int predictFisher = modelFisher->predict(testImage);

    return 0;
}
