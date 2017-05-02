/*
 * video.cpp
 *
 *  Created on: 2016?3?7?
 *      Author: fan
 */




#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void detectAndDisplay(Mat frame);

int main()
{
	//打开视频文件：其实就是建立一个VideoCapture结构
	VideoCapture capture("/Users/pro/Desktop/PJI/video/test.mp4");
	//检测是否正常打开:成功打开时，isOpened返回ture
	if(!capture.isOpened())
		cout<<"fail to open!"<<endl;
	//获取整个帧数
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout<<"整个视频共"<<totalFrameNumber<<"帧"<<endl;

	//设置开始帧()
	long frameToStart = 300;
	capture.set( CV_CAP_PROP_POS_FRAMES,frameToStart);
	cout<<"从第"<<frameToStart<<"帧开始读"<<endl;

	//设置结束帧
	int frameToStop = 400;

	if(frameToStop < frameToStart)
	{
		cout<<"结束帧小于开始帧，程序错误，即将退出！"<<endl;
		return -1;
	}
	else
	{
		cout<<"结束帧为：第"<<frameToStop<<"帧"<<endl;
	}

	//获取帧率
	double rate = capture.get(CV_CAP_PROP_FPS);
	cout<<"帧率为:"<<rate<<endl;

	//定义一个用来控制读取视频循环结束的变量
	bool stop = false;
	//承载每一帧的图像
	Mat frame;
	//显示每一帧的窗口
	namedWindow("Extracted frame");
	//两帧间的间隔时间:
	int delay = 1000/rate;

	//利用while循环读取帧
	//currentFrame是在循环体中控制读取到指定的帧后循环结束的变量
	long currentFrame = frameToStart;

	//滤波器的核
	int kernel_size = 3;
	Mat kernel = Mat::ones(kernel_size,kernel_size,CV_32F)/(float)(kernel_size*kernel_size);

	while(!stop)
	{
		//读取下一帧
		if(!capture.read(frame))
		{
			cout<<"读取视频失败"<<endl;
			return -1;
		}

		//这里加滤波程序
		imshow("Extracted frame",frame);
		filter2D(frame,frame,-1,kernel);

		imshow("after filter",frame);
		cout<<"正在读取第"<<currentFrame<<"帧"<<endl;
		//waitKey(int delay=0)当delay ≤ 0时会永远等待；当delay>0时会等待delay毫秒
		//当时间结束前没有按键按下时，返回值为-1；否则返回按键

		int c = waitKey(delay);
		//按下ESC或者到达指定的结束帧后退出读取视频
		if((char) c == 27 || currentFrame > frameToStop)
		{
			stop = true;
		}
		//按下按键后会停留在当前帧，等待下一次按键
		if( c >= 0)
		{
			waitKey(0);
		}
		currentFrame++;

	}
	//关闭视频文件
	capture.release();
	waitKey(0);
	return 0;
}

void detectAndDisplay(Mat frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat img2;
    Mat crop;
    Mat res;
    Mat gray;
    string text;
    stringstream sstm;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Set Region of Interest
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

        crop = frame(roi_b);
        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
        cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        // Form a filename
        filename = "";
        stringstream ssfn;
        ssfn << filenumber << ".png";
        filename = ssfn.str();
        filenumber++;

        imwrite(filename, gray);

        Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
    }

    // Show image
    sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename<<endl;
    sstm << faces.size() << "personnes";
    text = sstm.str();

    putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0, 0, 255), 1, CV_AA);
   // imshow("original", frame);
    cv::resize(frame,img2,Size(1000,1000),0,0,CV_INTER_LINEAR);
    imshow("original", img2);
    if (!crop.empty())
    {
        imshow("detected", crop);
    }
    else
        destroyWindow("detected");
}
