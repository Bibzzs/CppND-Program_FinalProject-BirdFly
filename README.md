# CPPND: CAPSTONE 

<img src="data/BirdFlyVideo.gif"/>

This is the final project of the course [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213): Capstone. 

This project is a home made little game : Bird Attack. 

The goal of this game is to escape from birds as long as you can. You start with 100 life point. 
More you survive, more bird will be added. 
When your life point is down to 0, then the game is over and your score appears. 

Hope you enjoy it !  :wink:

## Programm architecture

The main thread start by instanciated sky + leader bir + bird net. 

FlyingObject is the base class of bird and leaderbird.

The main thread launch oen thread by bird. 
Then a while loop is called to loop and produce the graphic output. 
Bird object are reading info from leaderbird to try to catch it. 

Finally once the game is over, all the thred are joined and the program exits. 

<img src="data/archi.png"/>

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./BirdAttack`.



## Project Tasks
### README (All Rubric Points REQUIRED)
| Conformity | Specification | STATUS |
| :--- | :---: | :---: |
| A README with instructions is included with the project | The README is included with the project and has instructions for building/running the project. If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions. You can submit your writeup as markdown or pdf. | :white_check_mark: |
| The README indicates which project is chosen. | The README describes the project you have built. The README also indicates the file and class structure, along with the expected behavior or output of the program. | :white_check_mark: |
| The README includes information about each rubric point addressed.|The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.| :white_check_mark: |

### Compiling and Testing (All Rubric Points REQUIRED)
| Conformity | Specification | STATUS |
| :--- | :---: | :---: |
| The submission must compile and run. |The project code must compile and run without errors. We strongly recommend using `cmake` and `make`, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform.| :white_check_mark:|

### Loops, Functions, I/O
| Conformity | Specification | STATUS | PATH |
| :--- | :---: | :---: | :--- |
| The project demonstrates an understanding of C++ functions and control structures. |A variety of control structures are used in the project. The project code is clearly organized into functions. | :white_check_mark:| Bird.h, FlyingObject.h, LeaderBird.h ... |
| The project reads data from a file and process the data, or the program writes data to a file. |The project reads data from an external file or writes data to a file as part of the necessary operation of the program. | N/A | N/A |
| The project accepts user input and processes the input. |The project accepts input from a user as part of the necessary operation of the program. | :white_check_mark:| main.cpp |

### Object Oriented Programming
| Conformity | Specification | STATUS | PATH |
| :--- | :---: | :---: | :--- |
|The project uses Object Oriented Programming techniques.|The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.|:white_check_mark:| Bird.h, FlyingObject.h, LeaderBird.h, Sly.h |
|Classes use appropriate access specifiers for class members.|All class data members are explicitly specified as public, protected, or private.|:white_check_mark:| Bird.h, FlyingObject.h, LeaderBird.h, Sly.h |
| Class constructors utilize member initialization lists. | All class members that are set to argument values are initialized through member initialization lists.|:white_check_mark:| Bird.h, FlyingObject.h, LeaderBird.h, Sly.h |
| Classes abstract implementation details from their interfaces. | All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.|:white_check_mark:| Bird.h, FlyingObject.h, LeaderBird.h, Sly.h |
|Classes encapsulate behavior. |Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.|:white_check_mark:| Bird.h, FlyingObject.h, LeaderBird.h, Sly.h |
| Classes follow an appropriate inheritance hierarchy. | Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.| :white_check_mark:|FlyingObject.h ==> Bird.h or LeaderBird.h |
|Overloaded functions allow the same function to operate on different parameters. | One function is overloaded with different signatures for the same function name.|:white_check_mark:| Bird.h |
| Derived class functions override virtual base class functions. |One member function in an inherited class overrides a virtual base class member function.|:white_check_mark:| FlyingObject.h ==> Bird.h or LeaderBird.h |
| Templates generalize functions in the project.| One function is declared with a template that allows it to accept a generic parameter.|:white_check_mark:| Bird.cpp `randomInRange()` |

### Memory Management
| Conformity | Specification | STATUS | PATH |
| :--- | :---: | :---: | :--- |
| The project makes use of references in function declarations. |At least two variables are defined as references, or two functions use pass-by-reference in the project code.| :white_check_mark:| `Bird::fly() or Bird::targetReached()` |
|The project uses destructors appropriately.|At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.| N/A |
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.| The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.| :white_check_mark:| ... |
| The project follows the Rule of 5.|For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.| N/A | no copy in the project |
|The project uses move semantics to move data, instead of copying it, where possible.| For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.|:white_check_mark:| `createBirdNet()` ? |
| The project uses smart pointers instead of raw pointers. | The project uses at least one smart pointer: `unique_ptr`, `shared_ptr`, or `weak_ptr`. The project does not use raw pointers. | :white_check_mark:| main.cpp |

### Concurrency
| Conformity | Specification | STATUS | PATH |
| :--- | :---: | :---: |  :--- |
| The project uses multithreading. | The project uses multiple threads in the execution. |:white_check_mark:| main.cpp call one thread per bird created |
| A promise and future is used in the project. | A promise and future is used to pass data from a worker thread to a parent thread in the project code. | N/A | thread does loop infinilty and does not promise data... |
| A mutex or lock is used in the project. |A mutex or lock (e.g. `std::lock_guard` or `std::unique_lock`) is used to protect data that is shared across multiple threads in the project code. | :white_check_mark:| `LeaderBird::fly`  & `Bird::fly` & `Bird::targetReached` use mutex to securise the reading and writing of position and speed |
| A condition variable is used in the project. | A `std::condition_variable` is used in the project code to synchronize thread execution. | N/A | no |


