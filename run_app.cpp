#include <iostream>
#include <cstdlib>
#include <limits>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear the screen
}

void displayMenu() {
    clearScreen();

    // ANSI escape sequences for font colors
    std::string red = "\033[1;31m";
    std::string green = "\033[1;32m";
    std::string cyan = "\033[1;36m";
    std::string reset = "\033[0m";

    // ANSI escape sequences for borders
    std::string horizontalLine = "\033[1;34m-----------------------------------\033[0m";
    std::string verticalLine = "\033[1;34m|\033[0m";

    std::cout << horizontalLine << std::endl;
    std::cout << verticalLine << " " << cyan << "Computer Vision Evaluation      " << reset << verticalLine << std::endl;
    std::cout << horizontalLine << std::endl;
    std::cout << verticalLine << " " << red << "1" << reset << " :  Object Detection          " << green << "✔" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "2" << reset << " :  Semantic Segmentation     " << green << "✔" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "3" << reset << " :  Pose Estimation           " << green << "✔" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "4" << reset << " :  Optic Flow Map            " << green << "✔" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "5" << reset << " :  Stereo Disparity (Video)  " << green << "✔" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "6" << reset << " :  Stereo Disparity (Camera) " << red << "✘" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "7" << reset << " :  Depth Map Generation      " << red << "✘" << reset << verticalLine << std::endl;
    std::cout << verticalLine << " " << red << "8" << reset << " :  Exit                       " << verticalLine << std::endl;
    std::cout << horizontalLine << std::endl;
}


int getInput() {
    int option;
    std::cin >> option;

    // Check if the input is valid
    if (std::cin.fail()) {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input

        return -1; // Return a value that can be recognized as invalid input
    }

    return option;
}

int main() {
    while (true) {
        displayMenu();

        int option;
        std::cout << "Enter the option number: ";
        option = getInput();

        switch (option) {
            case 1:
                   // Object Detection
                std::system("cd /opt/edgeai-gst-apps/apps_python && ./app_edgeai.py ../configs/object_detection.yaml");                // Add the command for Semantic Segmentation
                break;
            case 2:
                // Semantic Segmentation
                std::system("cd /opt/edgeai-gst-apps/apps_python && ./app_edgeai.py ../configs/semantic_segmentation.yaml");                // Add the command for Semantic Segmentation
                break;
            case 3:
                // Pose Estimation
                std::system("cd /opt/edgeai-gst-apps-6d-pose/apps_python && ./app_edgeai.py ../configs/object_6d_pose_estimation.yaml");
                break;
            case 4:
                // Optic Flow Map
                std::system("gst-launch-1.0 v4l2src io-mode=2 device=/dev/video2 ! jpegdec ! tiovxdlcolorconvert ! video/x-raw, format=NV12 ! tiovxpyramid ! application/x-pyramid-tiovx, format=GRAY8 ! tee name=split ! queue ! tiovxdof name=dof ! tiovxdofviz ! kmssink sync=false split. ! tiovxdelay delay-size=1 ! dof.delayed_sink");
                break;
            case 5:
                // Stereo Disparity Video File
                std::system("gst-launch-1.0 filesrc location=/opt/edgeai-test-data/videos/left-1280x720.avi ! avidemux ! h264parse ! v4l2h264dec ! video/x-raw, format=NV12 ! queue ! sde.left_sink filesrc location=/opt/edgeai-test-data/videos/right-1280x720.avi ! avidemux ! h264parse ! v4l2h264dec ! video/x-raw, format=NV12 ! queue ! sde.right_sink tiovxsde name=sde ! tiovxsdeviz ! kmssink sync=false");
                break;
            case 6:
                // Stereo Disparity Camera
                std::system("gst-launch-1.0 v4l2src device=/dev/video2 ! image/jpeg, width=640, height=480, framerate=30/1 ! jpegdec ! video/x-raw ! queue ! sde.left_sink v4l2src device=/dev/video4 ! image/jpeg, width=640, height=480, framerate=30/1 ! jpegdec ! video/x-raw ! queue ! sde.right_sink tiovxsde name=sde ! tiovxsdeviz ! kmssink sync=false");
                break;
            case 7:
                // Depth Map Generation
                std::system("clear");
                std::cout << "Depth Map Generation Not Yet Implemented." << std::endl;
                // Add the command for Depth Map Generation
                break;
            case 8:
                // Exit
                std::cout << "Exiting the program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}
