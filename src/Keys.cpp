#include "Keys.hpp"
#include "Window.hpp"

int Keys::currentKey_;

std::unordered_map<int, int> Keys::keyToGLUTKey_ = {
    {keyboard::F1,          GLUT_KEY_F1},
    {keyboard::F2,          GLUT_KEY_F2},
    {keyboard::F3,          GLUT_KEY_F3},
    {keyboard::F4,          GLUT_KEY_F4},
    {keyboard::F5,          GLUT_KEY_F5},
    {keyboard::F6,          GLUT_KEY_F6},
    {keyboard::F7,          GLUT_KEY_F7},
    {keyboard::F8,          GLUT_KEY_F8},
    {keyboard::F9,          GLUT_KEY_F9},
    {keyboard::F10,         GLUT_KEY_F10},
    {keyboard::F11,         GLUT_KEY_F11},
    {keyboard::F12,         GLUT_KEY_F12},
    {keyboard::LEFT,        GLUT_KEY_LEFT},
    {keyboard::RIGHT,       GLUT_KEY_RIGHT},
    {keyboard::UP,          GLUT_KEY_UP},
    {keyboard::DOWN,        GLUT_KEY_DOWN},
    {keyboard::PAGE_UP,     GLUT_KEY_PAGE_UP},
    {keyboard::PAGE_DOWN,   GLUT_KEY_PAGE_DOWN},
    {keyboard::HOME,        GLUT_KEY_HOME},
    {keyboard::END,         GLUT_KEY_END},
    {keyboard::INSERT,      GLUT_KEY_INSERT}
};

bool Keys::initialize(std::shared_ptr<Window> window) {
    bool returnFlag {false};

    if(window) {
        window->setKey(shared_from_this());
        returnFlag = true;
    } else {
        std::cout << __FILE__ << ":" << __LINE__
                 << " [Error] Failed to initialize window" 
                 << std::endl;
    }

    return returnFlag;
}

void Keys::processNormalKeys(unsigned char key, int x, int y) {
    if(key == 27) {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    }
}

void Keys::processSpecialKeys(int key, int x, int y) {
    if(findKey(static_cast<keyboard::SpecialKey>(key))) {
        switch(key) {
            case GLUT_KEY_UP:
                Window::moveUp();
                break;
            case GLUT_KEY_LEFT:
                Window::decreaseAngle();
                Window::moveLeft();
                break;
            case GLUT_KEY_RIGHT:
                Window::increaseAngle();
                Window::moveRight();
                break;
            case GLUT_KEY_DOWN:
                Window::moveDown();
                break;
            default: 
                std::cout << __FILE__ << ":" << __LINE__ 
                         << " [Info] Current key has no functionality."
                         << " key: " << currentKey_ << std::endl;
                break;
        }
    } else {
        std::cout << __FILE__ << ":" << __LINE__
                 << " [Error] Invalid key selected. key: " << key
                 << std::endl;
    }
}

bool Keys::findKey(keyboard::SpecialKey key) {
    bool returnFlag {false};
    auto glutKeyIter = keyToGLUTKey_.find(key);

    if(glutKeyIter != keyToGLUTKey_.end()) {
        currentKey_ = glutKeyIter->second;
        returnFlag = true;
    } else {
        std::cout << __FILE__ << ":" << __LINE__ 
                 << " [Error] Unable to find key. key: " 
                 << key << std::endl;
    }

    return returnFlag;
}
