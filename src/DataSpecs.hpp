#ifndef DATA_SPECS_HPP
#define DATA_SPECS_HPP

namespace display {
    enum Color : unsigned int{
        NO_COLOR_MODE = 0,
        RGB,
        INDEX
    };

    enum Buffer : unsigned int {
        NO_BUFFER = 0,
        SINGLE,
        DOUBLE,
        ACCUM,
        STENCIL,
        DEPTH
    };

}

namespace keyboard {
    enum SpecialKey : int {
        F1 = 0x0001,
        F2 = 0x0002, 
        F3 = 0x0003,
        F4 = 0x0004,
        F5 = 0x0005,
        F6 = 0x0006,
        F7 = 0x0007, 
        F8 = 0x0008,
        F9 = 0x0009,
        F10 = 0x000A,
        F11 = 0x000B, 
        F12 = 0x000C,
        LEFT = 0x0064, 
        RIGHT = 0x0065,
        UP = 0x0066,
        DOWN = 0x0067,
        PAGE_UP = 0x0068,
        PAGE_DOWN = 0x0069,
        HOME = 0x006A,
        END = 0x006B,
        INSERT = 0x006C
    };
}

#endif 
