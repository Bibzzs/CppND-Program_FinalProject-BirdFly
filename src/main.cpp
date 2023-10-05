#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <algorithm>
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
        birds.push_back(std::make_shared<Bird>( nb*(MAX_WIDTH / nmbrOfBird)/ COEFFCARTESIANTOGRAPHIC));
    }
}

int main() {
    int key = 0;

    // create Bird Net
    int nmbrOfBird = 10;
    std::vector<std::shared_ptr<Bird>> birds;
    
    std::vector<std::thread> threads;
    createBirdNet(birds, nmbrOfBird);

    LeaderBird leadBird;

    // Create a window
    cv::namedWindow("Mouse Follower");

    // Set the mouse callback function
    cv::setMouseCallback("Mouse Follower", onMouse, &leadBird);

    // init time counter
    std::chrono::time_point<std::chrono::system_clock> lastTLUpdate;
    lastTLUpdate = std::chrono::system_clock::now();

    double cycleDuration = 4000;
    
    for (auto& v : birds)
    {
        
        threads.emplace_back(std::thread(&Bird::fly, v, (float)TIMESTEP, &leadBird));
        
    }
    
    
    while (true) {
        
        // Create a black background image
        cv::Mat image = cv::Mat::zeros(MAX_LENGTH, MAX_WIDTH, CV_8UC3);

        // Draw a white dot at the current mouse position
        cv::circle(image, cv::Point(leadBird.getPosX() * COEFFCARTESIANTOGRAPHIC, leadBird.getPosY() * COEFFCARTESIANTOGRAPHIC), 10, cv::Scalar(255, 0, 255), -1);
         
        // Draw birds
        for (auto& v : birds)
        {
            cv::circle(image, cv::Point(v->getPosX() * COEFFCARTESIANTOGRAPHIC, v->getPosY() * COEFFCARTESIANTOGRAPHIC), 5, cv::Scalar(0, 255, 255), -1);
        }

        // Add text in the top-left corner
        cv::putText(image, "To finish, press Esc", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(image, "Number of birds # " + std::to_string(leadBird.getNumberOfBirds()), cv::Point(10, 60), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 0.5);
        cv::putText(image, "LifePoints = # " + std::to_string(leadBird.getLifePoint()), cv::Point(MAX_LENGTH / 2, 60), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 0.5);
        // Simulate LeaderBird
        leadBird.fly((float)TIMESTEP);
        
        if (key == 27)  // Exit when the 'Esc' key is pressed
        {
            leadBird.end(); // allow to end the bird thread 
            break;
        }
        if (leadBird.getLifePoint() == 0)  // Exit when the 'Esc' key is pressed
        {
            cv::putText(image, "GAME OVER ...", cv::Point(10, MAX_LENGTH / 2), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
            cv::putText(image, "score : " + std::to_string(leadBird.getNumberOfBirds()), cv::Point(10, MAX_LENGTH / 1.5), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
            leadBird.end(); // allow to end the bird thread 
            if (key == 27)  // Exit when the 'Esc' key is pressed
            {
                leadBird.end(); // allow to end the bird thread 
                break;
            }
        }

        // Display the image in the window
        cv::imshow("Mouse Follower", image);

        // Wait for a key event
        key = cv::waitKey(TIMEREFRESH); // ms

        // update number of bird
        long timeSinceLastTLUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastTLUpdate).count();
        if (timeSinceLastTLUpdate > cycleDuration && leadBird.getLifePoint() > 0)
        {
            birds.push_back(std::make_shared<Bird>(0));
            threads.emplace_back(std::thread(&Bird::fly, birds.back(), (float)TIMESTEP, &leadBird));
            lastTLUpdate = std::chrono::system_clock::now();
            cycleDuration = std::max(cycleDuration / 1.05,100.0);
        }
    }

    // Close the window and release resources
    cv::destroyAllWindows();

    // set up thread barrier before this ending th eprogramm
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) 
        {
            t.join();
        });
    
    return 0;
}
