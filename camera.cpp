#include "camera.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <raspicam/raspicam_still_cv.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
raspicam::RaspiCam_Still_Cv Camera;

Mat3b getMean(const vector<Mat3b>& images){
    if (images.empty()) return Mat3b();
    Mat m(images[0].rows,images[0].cols,CV_64FC3);
    m.setTo(Scalar(0,0,0,0));
    Mat temp;
    for(int i =0;i<images.size();++i){
        images[i].convertTo(temp,CV_64FC3);
        m+=temp;
    }
    m.convertTo(m,CV_8U,1./images.size());
    return m;
}
void Camera::capture(){
    Mat img;
    int imgSize;
    int bytes = 0;
    Size size(640,480);

    raspicam::RaspiCam_Still_Cv Camera;
    //Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    Camera.set(cv::CAP_PROP_FRAME_WIDTH,2592);
    Camera.set(cv::CAP_PROP_FRAME_HEIGHT,1944);

    //for(int i = 0; i< 2; ++i){
    Camera.open();
    sleep(1);


        Camera.grab();



            /* get a frame from camera */
                Camera.retrieve(img);
                //imwrite("/home/pi/Desktop/test1.jpg",img);

                //resize(img,img,size);

                //imgSize = img.total()*img.elemSiz
                Camera.release();
//}
    //Mat3b meanImage = getMean(images);
    imwrite("image.png",img);
    imwrite("/home/pi/Desktop/image.png",img);
    return;

}

