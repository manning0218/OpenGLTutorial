#ifndef SNOWMAN_HPP
#define SNOWMAN_HPP

#include <memory>
#include <iostream>

#include <GL/glut.h>

struct Snowman {
    Snowman() = default;
    ~Snowman() = default;

    Snowman(Snowman &&) = delete;
    Snowman(Snowman const &) = delete;
    Snowman &operator=(Snowman &&) = delete;
    Snowman &operator=(Snowman const &) = delete;

    void drawSnowman();

    void drawBody();
    void drawHead();
    void drawEyes();
    void drawNose();
};

#endif
