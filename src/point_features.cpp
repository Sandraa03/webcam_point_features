
//OpenCV 
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//consts
const unsigned int MIN_NUM_FEATURES = 30; //minimum number of point fetaures

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
    
    // Obtenim la mida de la imatge
    int image_width = camera.get(CV_CAP_PROP_FRAME_WIDTH);
    int image_height = camera.get(CV_CAP_PROP_FRAME_HEIGHT);
    
    //Definim les parts en que volem trossejar la imatge d'ample i d'alt
    const int width_parts = 5;
    const int height_parts = 3;
    
    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
      {
	//Read image and check it. Blocking call up to a new image arrives from camera.
	if(!camera.read(image)) 
	  {
	    std::cout << "No image" << std::endl;
	    cv::waitKey();
	  }
	
	// Creem un loop per mirar tota la imatge
	for(int i = 0; i < width_parts; i++)
	  {
	    for(int j = 0; j < height_parts; j++)
	      {
		//Definim la mascara que volem utilitzar
		cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
		
		//Definim la nostra area d'interes
		cv::Mat myROI(mask, cv::Rect(0+(i*(image_width/width_parts)),0+(j*(image_height/height_parts)),image_width/width_parts,image_height/height_parts));
		//Les imatges poden ser "multi-channel", per això, hem d'accedir a un element concret de la imatge
		myROI = cv::Scalar(255,255,255);
						        		
		//**************** Find ORB point fetaures and descriptors ****************************
		
		//clear previous points
		point_set.clear(); 
		
		//detect and compute(extract) features
		orb_detector->detectAndCompute(image, mask, point_set, descriptor_set);
		
		//draw points on the image
		cv::drawKeypoints( image, point_set, image, 255, cv::DrawMatchesFlags::DEFAULT );     
	      }
	  } 
	
	//********************************************************************
	
        //show image
        cv::imshow("Output Window", image);
	
	//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
      }   
}
