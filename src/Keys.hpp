#ifndef KEYS_HPP
#define KEYS_HPP

#include <memory>
#include <unordered_map>
#include <stdlib.h>

#include <GL/glut.h>

#include "DataSpecs.hpp"

class Window;

class Keys : public std::enable_shared_from_this<Keys> {
    public:
        Keys() = default;
        ~Keys() = default;

        Keys(Keys &&) = delete;
        Keys(Keys const &) = delete;
        Keys &operator=(Keys &&) = delete;
        Keys &operator=(Keys const &) = delete;

        bool initialize(std::shared_ptr<Window> window);

        static void processNormalKeys(unsigned char key, int x, int y);
        static void processSpecialKeys(int key, int x, int y);

    protected:
        static bool findKey(keyboard::SpecialKey key);

    private:
        static int currentKey_;
        static std::unordered_map<int, int> keyToGLUTKey_;

        std::shared_ptr<Window> window_;
};

#endif
