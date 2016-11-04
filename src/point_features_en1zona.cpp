
//OpenCV 
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//consts
const unsigned int MIN_NUM_FEATURES = 300; //minimum number of point fetaures

int main(int argc, char *argv[]) 
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
    orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
    std::vector<cv::KeyPoint> point_set; //set of point features
    cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor 
	
	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;  
			break; 
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break; 
		default: 
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl; 
			std::cout << "EXIT program." << std::endl; 
			break; 
	}
	
	//advertising to the user 
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) ) 
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image)) 
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }
        		
    //**************** Find ORB point fetaures and descriptors ****************************

	//Definim la máscara que volem utilitzar
	//cv::Mat mask;
	//mask = cv::Mat::zeros(image.size(), image.type());
	//mask = cv::Mat::zeros(image.size(), CV_8U);
        
        //clear previous points
        point_set.clear(); 
	
	//Definim un rectangle que indica la nostra área d'interes
	cv::Rect myROI(10, 10, 100, 100);
	
	//Trossegem la imatge per buscar els punts d'interes només en l'área que ens interesa.
	cv::Mat croppedImage = image(myROI);
	
	//detect and compute(extract) features
        orb_detector->detectAndCompute(croppedImage, cv::noArray(), point_set, descriptor_set);
        
        //draw points on the image
        cv::drawKeypoints(image, point_set, image, 255, cv::DrawMatchesFlags::DEFAULT );      
                
    //********************************************************************
		
        //show image
        cv::imshow("Output Window", image);

		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
    }   
}
