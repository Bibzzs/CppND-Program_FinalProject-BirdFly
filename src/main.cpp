#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <algorithm>
#include "Bird.h"
#include "Sky.h"
#include "FlyingObject.h"
#include "LeaderBird.h"

constexpr double MAX_WIDTH = 500;
constexpr double MAX_LENGTH = MAX_WIDTH;
constexpr double SQUARESIZE = 50;
constexpr double COEFFCARTESIANTOGRAPHIC = MAX_WIDTH/SQUARESIZE;
constexpr int TIMEREFRESH = 10; // ms;
constexpr double TIMESTEP = (double)TIMEREFRESH / (double)1000; // s
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
    double maxH = MAX_WIDTH / COEFFCARTESIANTOGRAPHIC;
    double maxW = MAX_WIDTH / COEFFCARTESIANTOGRAPHIC;
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
    cv::namedWindow("Bird attack");

    // Set the mouse callback function
    cv::setMouseCallback("Bird attack", onMouse, &leadBird);

    // init time counter
    std::chrono::time_point<std::chrono::system_clock> lastTLUpdate;
    lastTLUpdate = std::chrono::system_clock::now();

    double cycleDuration = 4000;
    
    for (auto& v : birds)
    {
        
        threads.emplace_back(std::thread(&Bird::fly, v, (double)TIMESTEP, &leadBird));
        
    }
    
    int localLifePoint = 100;
    while (true) {
        
        // Create a  background image
        cv::Mat image;
        if (leadBird.getLifePoint() < localLifePoint)
        {
            image = cv::Mat::ones((int)MAX_LENGTH, (int)MAX_WIDTH, CV_8UC3)*255;
            localLifePoint = leadBird.getLifePoint();
        }
        else
        {
            image = cv::Mat::zeros((int)MAX_LENGTH, (int)MAX_WIDTH, CV_8UC3);
        }
        
        

        // Draw a white dot at the current mouse position
        cv::circle(image, cv::Point((int)(leadBird.getPosX() * COEFFCARTESIANTOGRAPHIC), (int)(leadBird.getPosY() * COEFFCARTESIANTOGRAPHIC)), 10, cv::Scalar(255, 0, 255), -1);
         
        // Draw birds
        for (auto& v : birds)
        {
            cv::circle(image, cv::Point((int)(v->getPosX() * COEFFCARTESIANTOGRAPHIC), (int)(v->getPosY() * COEFFCARTESIANTOGRAPHIC)), 5, cv::Scalar(0, 255, 255), -1);
        }

        // Add text in the top-left corner
        cv::putText(image, "To finish, press Esc", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(image, "Number of birds # " + std::to_string(leadBird.getNumberOfBirds()), cv::Point(10, 60), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1);
        cv::putText(image, "LifePoints = # " + std::to_string(leadBird.getLifePoint()), cv::Point(int(MAX_LENGTH / 2), 60), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1);
        // Simulate LeaderBird
        leadBird.fly(TIMESTEP);
        
        if (key == 27)  // Exit when the 'Esc' key is pressed
        {
            leadBird.end(); // allow to end the bird thread 
            break;
        }
        if (leadBird.getLifePoint() == 0)  // Exit when the 'Esc' key is pressed
        {
            cv::putText(image, "GAME OVER ...", cv::Point(10, (int)(MAX_LENGTH / 2)), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
            cv::putText(image, "score : " + std::to_string(leadBird.getNumberOfBirds()), cv::Point(10, (int)(MAX_LENGTH / 1.5)), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
            leadBird.end(); // allow to end the bird thread 
            if (key == 27)  // Exit when the 'Esc' key is pressed
            {
                leadBird.end(); // allow to end the bird thread 
                break;
            }
        }

        // Display the image in the window
        cv::imshow("Bird attack", image);

        // Wait for a key event
        key = cv::waitKey(TIMEREFRESH); // ms

        // update number of bird
        long timeSinceLastTLUpdate = (long)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastTLUpdate).count());
        if (timeSinceLastTLUpdate > cycleDuration && leadBird.getLifePoint() > 0)
        {
            birds.push_back(std::make_shared<Bird>(int(leadBird.getPosX())));
            threads.emplace_back(std::thread(&Bird::fly, birds.back(), (double)TIMESTEP, &leadBird));
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
