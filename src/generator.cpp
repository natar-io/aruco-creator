#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <cxxopts.hpp>

using namespace cv;

int markerId = -1;
int markerSize = 50;
int margin = 1;


static int parseCommandLine(cxxopts::Options options, int argc, char** argv)
{
    auto result = options.parse(argc, argv);
    if (result.count("h")) {
        std::cout << options.help({"", "Group"});
        return EXIT_FAILURE;
    }

    if (result.count("i")) {
        markerId = result["i"].as<int>();
    }
    else {
        std::cerr << "Error: -i option required." << std::endl;
        return EXIT_FAILURE;
    }

    if (result.count("m")) {
        margin = result["m"].as<int>();
    }

    if (result.count("s")) {
        markerSize = result["s"].as<int>();
    }
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    cxxopts::Options options("aruco-detection-server", "Aruco markers detection server.");
    options.add_options()
            ("i, id", "Marker ID", cxxopts::value<int>())
            ("s, size", "Marker size", cxxopts::value<int>())
            ("m, margin", "N margin bits", cxxopts::value<int>())
            ("h, help", "Print this help message.");

    if (parseCommandLine(options, argc, argv)) {
        return EXIT_FAILURE;
    }

    std::string name = std::to_string(markerId)+ ".png";

    Mat marker;
    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(aruco::DICT_ARUCO_ORIGINAL);
    aruco::generateImageMarker(dictionary, markerId, markerSize, marker, margin);
    imwrite(name, marker);
    std::cerr << "Succesfully generated " << markerId << ".png." << std::endl;
}
