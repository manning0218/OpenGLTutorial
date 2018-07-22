#include "Window.hpp"

float Window::angle_ {0.0f};
std::array<float, 2> Window::position_ {0.0f, 1.0f};
std::array<float, 2> Window::direction_ {0.0f, 5.0f};
std::shared_ptr<Snowman> Window::snowman_ {std::make_shared<Snowman>()};


bool Window::createWindow(const std::string& title) {
    bool returnFlag {false};

    if(colorMode_ != display::NO_COLOR_MODE) {
        glutInitDisplayMode(16);
        glutInitWindowSize(sizeAndLocation_->height_, sizeAndLocation_->width_);
        glutInitWindowPosition(sizeAndLocation_->posX_, sizeAndLocation_->posY_);
        glutCreateWindow(const_cast<char*>(title.c_str()));

        returnFlag = true;
    } else {
        std::cout << __FILE__ << ":" << __LINE__ 
                 << " [Error] Failed to set the mode for the window" 
                 << std::endl;
    }

    return returnFlag;
}

void Window::setSize(int height, int width)
{
    if(!sizeAndLocation_) {
        sizeAndLocation_ = new SizeLocation;
    }

    sizeAndLocation_->height_ = height;
    sizeAndLocation_->width_ = width;
}

void Window::setLocation(int posX, int posY) {
    if(!sizeAndLocation_) {
        sizeAndLocation_ = new SizeLocation;
    }

    sizeAndLocation_->posX_ = posX;
    sizeAndLocation_->posY_ = posY;
}

SizeLocation* Window::getSizeAndLocation() {
    return sizeAndLocation_;
}

void Window::setMode(display::Color colorMode, std::vector<display::Buffer>& bufferModes)
{
    colorMode_ = colorMode;
    switch(colorMode_) {
        case display::RGB: mode_ = GLUT_RGB; // Uses RGBA color mode
                           break;
        case display::INDEX: mode_ = GLUT_INDEX; // Uses INDEX color mode
                             break;
        case display::NO_COLOR_MODE: mode_ = 0;
                                     std::cout << __FILE__ << ":" << __LINE__ 
                                         << " [Error] No color mode selected. Please select either RGB or INDEX"
                                         << std::endl;
                                     break;
        default: mode_ = 0;
                 std::cout << __FILE__ << ":" << __LINE__
                          << " [Error] Invalid color mode selected"
                          << std::endl;
                 break;
    }

    for(auto bufferMode : bufferModes) {
        switch(bufferMode) {
            case display::SINGLE: mode_ |= GLUT_SINGLE; // Uses single buffer
                                  break;
            case display::DOUBLE: mode_ |= GLUT_DOUBLE; // Uses double buffer
                                  break;
            case display::ACCUM: mode_ |= GLUT_ACCUM; // Uses accumulation buffer
                                 break;
            case display::STENCIL: mode_ |= GLUT_STENCIL; // Uses stencil buffer
                                   break;
            case display::DEPTH: mode_ |= GLUT_DEPTH; // Uses depth buffer
                                 break;
            case display::NO_BUFFER: std::cout << __FILE__ << ":" << __LINE__ 
                                              << " [Info] No buffer was selected for the window."
                                              << std::endl;
                                     break;
            default: std::cout << __FILE__ << ":" << __LINE__
                              << " [Error] User did not pass a buffer to the window."
                              << std::endl;
                     break;
        }

    }

}

void Window::run() {
    std::cout << "Adding callbacks..." << std::endl;
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutIdleFunc(render);

    // Adding callbacks for keys
    glutKeyboardFunc(key_->processNormalKeys);
    glutSpecialFunc(key_->processSpecialKeys);


    std::cout << "Entering GLUT event processing cycle..." << std::endl;
    glutMainLoop();
}

void Window::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the transformations and set the camera
    glLoadIdentity();
    gluLookAt(  position_[0],                      1.0f,   position_[1],
                position_[0] + direction_[0],      1.0f,   position_[1] + direction_[1],
                0.0f,   1.0f,   0.0f);  
               
              

    // Sets the rotation
    glRotatef(angle_, 0.0f, 1.0f, 0.0f);

    // Sets color of the ground
    glColor3f(0.9f, 0.9f, 0.9f);

    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 Snowmen
    for(int i = -3; i < 3; i++) {
        for(int j = -3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            snowman_->drawSnowman();
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}

void Window::changeSize(int width, int height) {
    // Prevents division by 0
    if(height == 0) {
        height = 1;
    }

    float ratio = width*1.0/height;

    // Sets projection matrix
    glMatrixMode(GL_PROJECTION);
    
    // Resets matrix
    glLoadIdentity();

    // Sets the viewport to entire wind
    glViewport(0, 0, width, height);

    // Sets perspective
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get back to the ModelView
    glMatrixMode(GL_MODELVIEW);
}

void Window::increaseAngle() {
    angle_ += 0.01f;
}

void Window::decreaseAngle() {
    angle_ -= 0.01f;
}

void Window::moveLeft() {
    direction_[0] = std::sin(angle_);
    direction_[1] = -std::cos(angle_);
}

void Window::moveRight() {
    direction_[0] = std::sin(angle_);
    direction_[1] = -std::cos(angle_);
}

void Window::moveDown() {
    position_[0] -= direction_[0] * 0.1f;
    position_[1] -= direction_[1] * 0.1f;
}

void Window::moveUp() {
    position_[0] += direction_[0] * 0.1f;
    position_[1] += direction_[1] * 0.1f;
}
