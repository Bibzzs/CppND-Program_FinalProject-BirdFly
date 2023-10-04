#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include "Bird.h"
#include "Sky.h"
#include "FlyingObject.h"
#include "LeaderBird.h"

constexpr float MAX_WIDTH = 500;
#define MAX_LENGTH MAX_WIDTH
constexpr float SQUARESIZE = 50;
constexpr float COEFFCARTESIANTOGRAPHIC = MAX_WIDTH/SQUARESIZE;
constexpr float TIMEREFRESH = 10; // ms;
#define TIMESTEP TIMEREFRESH/1000 // s
cv::Point whiteDotPosition(100, 100); // Initial position


// On Mousse event 
void onMouse(int event, int x, int y, int flags, void* userdata) {
    LeaderBird* leadBird(static_cast<LeaderBird*>(userdata));
    if (event == cv::EVENT_MOUSEMOVE) {
        whiteDotPosition = cv::Point(x, y);
        leadBird->update(x / COEFFCARTESIANTOGRAPHIC, y / COEFFCARTESIANTOGRAPHIC);
        
    }
}

// create SKY 
Sky FlyingObject::_sky = Sky(MAX_WIDTH / COEFFCARTESIANTOGRAPHIC, MAX_LENGTH / COEFFCARTESIANTOGRAPHIC); 
struct skyDimension {
    float maxH = MAX_WIDTH / COEFFCARTESIANTOGRAPHIC;
    float maxW = MAX_WIDTH / COEFFCARTESIANTOGRAPHIC;
}; // definir une class ciel 


// create bird net
void createBirdNet(std::vector<std::shared_ptr<Bird>> &birds, int nmbrOfBird)
{
    // how to pass info hrer ??????   
    for (size_t nb = 0; nb < nmbrOfBird; nb++)
    {
        birds.push_back(std::make_shared<Bird>(nb, nb*(MAX_WIDTH / nmbrOfBird)/ COEFFCARTESIANTOGRAPHIC));
    }
}

int main() {
    
    // create Bird Net
    std::vector<std::shared_ptr<Bird>> birds;
    int nmbrOfBird = 50;
    
    createBirdNet(birds, nmbrOfBird);
    LeaderBird leadBird;

    // Create a window
    cv::namedWindow("Mouse Follower");

    // Set the mouse callback function
    cv::setMouseCallback("Mouse Follower", onMouse, &leadBird);
    
    while (true) {
        
        // Create a black background image
        cv::Mat image = cv::Mat::zeros(MAX_LENGTH, MAX_WIDTH, CV_8UC3);

        // Draw a white dot at the current mouse position
        //cv::circle(image, whiteDotPosition, 10, cv::Scalar(255, 255, 255), -1);
        cv::circle(image, cv::Point(leadBird.getPosX() * COEFFCARTESIANTOGRAPHIC, leadBird.getPosY() * COEFFCARTESIANTOGRAPHIC), 10, cv::Scalar(255, 0, 255), -1);
        //cv::circle(image, , 10, cv::Scalar(255, 255, 255), -1);
        
        // Draw bird
        for (auto& v : birds)
        {
            cv::circle(image, cv::Point(v->getBirdXpos() * COEFFCARTESIANTOGRAPHIC, v->getBirdYpos() * COEFFCARTESIANTOGRAPHIC), 5, cv::Scalar(0, 255, 255), -1);
        }
        

        // Add text in the top-left corner
        cv::putText(image, "To finish, press Esc", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(image, "Number of birds = # " + std::to_string(birds[0]->getNumberOfBirds()), cv::Point(10, 60), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 0.5);


        // Simulate Bird
        leadBird.fly((float)TIMESTEP);
        if (leadBird.getUpdate())
        {
            for (auto& v : birds)
            {
                v->fly((float)TIMESTEP,&leadBird);
            }
        }
        else
        {
            for (auto& v : birds)
            {
                v->fly((float)TIMESTEP);
            }
        }
        
       



        // Display the image in the window
        cv::imshow("Mouse Follower", image);

        // Wait for a key event
        int key = cv::waitKey(TIMEREFRESH); // ms
        if (key == 27)  // Exit when the 'Esc' key is pressed
            break;
    }

    // Close the window and release resources
    cv::destroyAllWindows();

    return 0;
}
