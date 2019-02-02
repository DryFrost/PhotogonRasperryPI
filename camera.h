#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <string.h>

class Camera
{
public:
    void capture();
};

#endif // CAMERA_H
