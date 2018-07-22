#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <cmath>

#include <stdlib.h>

// OpenGL Library
#include <GL/glut.h>

#include "DataSpecs.hpp"
#include "Keys.hpp"
#include "Snowman.hpp"

struct SizeLocation {
    SizeLocation() = default;
    ~SizeLocation() = default;

    SizeLocation(SizeLocation const & rhs) {
        this->height_ = rhs.height_;
        this->width_ = rhs.width_;
        this->posX_ = rhs.posX_;
        this->posY_ = rhs.posY_;
    }
    SizeLocation &operator=(SizeLocation const & rhs) {
        this->height_ = rhs.height_;
        this->width_ = rhs.width_;
        this->posX_ = rhs.posX_;
        this->posY_ = rhs.posY_;

        return *this;
    }

    SizeLocation(SizeLocation &&) = delete;
    SizeLocation &operator=(SizeLocation &&) = delete;

    int height_, width_ = 300;
    int posX_, posY_ = 100;
};

typedef display::Color Color;
typedef display::Buffer Buffer;

class Window {
    public:
        Window() = default;
        ~Window() = default;

        Window(Window &&) = delete;
        Window(Window const &) = delete;
        Window &operator=(Window &&) = delete;
        Window &operator=(Window const &) = delete;

        void initialize(int* argc, char** argv) { glutInit(argc, argv); }
        bool createWindow(const std::string& title);

        // Size and Location Methods
        void setSize(int height, int width);
        void setLocation(int posX, int posY);
        SizeLocation* getSizeAndLocation();

        // Sets the mode for the window
        void setMode(display::Color colorMode, std::vector<display::Buffer>& bufferModes);

        // Adds key to window
        void setKey(std::shared_ptr<Keys> key) { key_ = key; }
        std::shared_ptr<Keys> getKey() { return key_; }

        void run();

        static void render();
        static void changeSize(int width, int height);

        // Increases angle of camera
        static void increaseAngle();

        // Decreeases angle of camera
        static void decreaseAngle();

        // Updates the direction and position of the camera
        static void moveLeft();
        static void moveRight();
        static void moveUp();
        static void moveDown();

    private:
        SizeLocation* sizeAndLocation_ {nullptr};
        unsigned int mode_ {0};
        display::Color colorMode_ {display::NO_COLOR_MODE};

        static float angle_;
        static std::array<float, 2> direction_;
        static std::array<float, 2> position_;

        static std::shared_ptr<Snowman> snowman_;

        std::shared_ptr<Keys> key_;
};

#endif
