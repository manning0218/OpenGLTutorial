#include <vector>
#include <string_view>
#include <utility>
#include <memory>

#include <GL/glut.h>

#include "Window.hpp"

std::pair<display::Color, std::vector<display::Buffer>> getModeSettings(int argc, char** argv) {
    display::Color colorMode;
    
    std::string_view currentArg {argv[1]};
    if(currentArg.compare("RGB") == 0) {
        colorMode = display::RGB;
    } else if(currentArg.compare("INDEX") == 0) {
        colorMode = display::INDEX;
    } else {
        colorMode = display::NO_COLOR_MODE;
        std::cout << __FILE__ << ":" << __LINE__ 
                 << " [Error] Invalid color mode selected."
                 << std::endl;
    }

    std::vector<display::Buffer> bufferModes;
    for(int index = 2; index < argc; index++) {
        currentArg = argv[index];
        if(currentArg.compare("SINGLE") == 0) {
            bufferModes.push_back(display::SINGLE);
        } else if(currentArg.compare("DOUBLE") == 0) {
            bufferModes.push_back(display::DOUBLE);
        } else if(currentArg.compare("ACCUM") == 0) { 
            bufferModes.push_back(display::ACCUM);
        } else if(currentArg.compare("STENCIL") == 0) {
            bufferModes.push_back(display::STENCIL);
        } else if(currentArg.compare("DEPTH") == 0) {
            bufferModes.push_back(display::DEPTH);
        } else {
            std::cout << __FILE__ << ":" << __LINE__
                     << " [Error] Invalid buffer mode selected. bufferMode: " 
                     << argv[index] << std::endl;
        }
    }

    return std::make_pair(colorMode, std::move(bufferModes));
}

int main(int argc, char** argv) {
    std::shared_ptr<Window> window {std::make_shared<Window>()};
    std::shared_ptr<Keys> key {std::make_shared<Keys>()};

    window->initialize(&argc, argv);

    if(argc >=2) {
        auto windowMode = getModeSettings(argc, argv);

        window->setMode(windowMode.first, windowMode.second);
        window->setSize(320, 320);
        window->setLocation(100, 100);
        if(window->createWindow("Window Class")) {
            key->initialize(window);
            window->run();
        } else {
            auto sizeAndLocation = window->getSizeAndLocation();
            std::cout << __FILE__ << ":" << __LINE__ 
                     << " [Error] Failed to create window. addr: " << &window
                     << " width: " << sizeAndLocation->width_ << " height: " 
                     << sizeAndLocation->height_ << " pos: (" << sizeAndLocation->posX_
                     << ", " << sizeAndLocation->posY_ << ")" << std::endl;
        }
    } else {
        std::cout << __FILE__ << ":" << __LINE__
                 << " [Error] Not enough arguments:\n"
                 << " To run ./openGLTest [COLOR_BUFFER] [DISPLAY_BUFFER]..."
                 << std::endl;
    }

    return 0;
}
