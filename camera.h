#ifndef CAMERA_H
#define CAMERA_H

//#include "opencv4/opencv2/opencv.hpp"
#include <raspicam/raspicam_still_cv.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>
#include <opencv2/opencv.hpp>
class Camera
{
public:
    void capture();
};

#endif // CAMERA_H
