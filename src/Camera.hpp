#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>
#include <array>

#include <GL/glut.h>

class Camera {
    public:
        Camera() = default;
        ~Camera() = default;

        Camera(Camera &&) = delete;
        Camera(Camera const &) = delete;
        Camera &operator(Camera &&) = delete;
        Camera &operator(Camera const &) = delete;

    private:
        float angle_; // Angle of rotation in the y-axis.
        std::array<float, 2> direction_; // Vector defining our line of site
        std::array<float, 2> xzPostion_; // Camera position in xz-plane 
};

#endif
