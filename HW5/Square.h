#pragma once

#include "Shape.h"

class Square : public IShape {
public:
    Square(int side = 1) : side_(side) { 
        setArea(side * side);
    }

    ~Square() override = default;

    void print(std::ostream& out) override {
        out << "Square: side=" << side_ << " area=" << getArea() << std::endl;
    }

private:
    int side_;
};