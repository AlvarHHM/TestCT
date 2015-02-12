#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "CompressiveTracker.h"

using namespace cv;
using namespace std;

Rect selection;
bool selecting;
bool selected;
Point originPoint;
CompressiveTracker ct;
Mat imgOriginal;
Mat grayImg;

void mouse_callback(int event, int x, int y, int flags, void *data)
{
    switch(event)
    {
        case CV_EVENT_LBUTTONDOWN:
            // User has started their selection, initialise the rectangle.
            selecting = true;
            selection = Rect(0,0,0,0);
            originPoint.x = x;
            originPoint.y = y;
            break;
        case CV_EVENT_LBUTTONUP:
            // User has selected their selection.
            selecting = false;
            selected = true;
            ct.init(grayImg,selection);
            break;
        case CV_EVENT_MOUSEMOVE:
            // Mouse is moving, user is selecting an area.
            if (selecting)
            {
                selection.x = MIN(x, originPoint.x);
                selection.y = MIN(y, originPoint.y);
                selection.width = std::abs(x - originPoint.x);
                selection.height = std::abs(y - originPoint.y);
            }
            break;
        default:
        {
            // Unknown user input, usually result of a right-click.
            break;
        }
    }
}


int main( int argc, char** argv )
{
    VideoCapture cap(0); //capture the video from web cam
    
    if ( !cap.isOpened() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }
        
    namedWindow( "Original", WINDOW_AUTOSIZE );


    setMouseCallback("Original",mouse_callback);


    while (true)
    {
        
        
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video
        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }
        resize(imgOriginal,imgOriginal,Size(720,480));
        cvtColor(imgOriginal, grayImg, CV_RGB2GRAY);

        if(selected){
            ct.processFrame(grayImg,selection);
        }
        

        rectangle(imgOriginal,selection, Scalar(200,0,0),2);

        imshow("Original", imgOriginal); //show the original image
        
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break; 
        }
    }
    
    return 0;
    
}
