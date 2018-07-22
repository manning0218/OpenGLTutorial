#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <memory>
#include <vector>

#include <stdlib.h>

// OpenGL Library
#include <GL/glut.h>

#include "DataSpecs.hpp"
#include "Keys.hpp"

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

        static void setColor(float red, float green, float blue);

    private:
        SizeLocation* sizeAndLocation_ {nullptr};
        unsigned int mode_ {0};
        display::Color colorMode_ {display::NO_COLOR_MODE};

        static float angle_;
        static float red_, green_, blue_;

        std::shared_ptr<Keys> key_;
};

#endif
