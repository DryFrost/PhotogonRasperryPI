#include "camera.h"

using namespace cv;

void *display(void *);

int capDev = 0;

VideoCapture cap(capDev);

void Camera::capture(){
    int localSocket, remoteSocket, port = 4097;

        struct  sockaddr_in localAddr,remoteAddr;

        pthread_t thread_id;

        int addrLen = sizeof(struct sockaddr_in);

        localSocket = socket(AF_INET , SOCK_STREAM , 0);
        if (localSocket == -1){
             perror("socket() call failed!!");
        }

        localAddr.sin_family = AF_INET;
        localAddr.sin_addr.s_addr = INADDR_ANY;
        localAddr.sin_port = htons( port );

        if( bind(localSocket,(struct sockaddr *)&localAddr , sizeof(localAddr)) < 0) {
             perror("Can't bind() socket");
             exit(1);
        }

        //Listening
        listen(localSocket , 3);

        std::cout <<  "Waiting for connections...\n"
                  <<  "Server Port:" << port << std::endl;

        //accept connection from an incoming client
        while(1){


         remoteSocket = accept(localSocket, (struct sockaddr *)&remoteAddr, (socklen_t*)&addrLen);
          //std::cout << remoteSocket<< "32"<< std::endl;
        if (remoteSocket < 0) {
            perror("accept failed!");
            exit(1);
        }
        std::cout << "Connection accepted" << std::endl;
         pthread_create(&thread_id,NULL,display,&remoteSocket);
         std::cout << "Quiting";

        }
}

void *display(void *ptr){
    int socket = *(int *)ptr;
    Mat img;
    int imgSize;
    int bytes = 0;
    Size size(640,480);

    while(1) {
            /* get a frame from camera */
                cap >> img;

                resize(img,img,size);

                imgSize = img.total()*img.elemSize();

                //send processed image
                if ((bytes = send(socket, img.data, imgSize, 0)) < 0){
                     std::cerr << "bytes = " << bytes << std::endl;
                     break;
                }
    }

}
