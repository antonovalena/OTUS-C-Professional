#pragma once

#include "Editable.h"

class IShape : public IEditable {
public:
    virtual ~IShape() = default;

    void setArea(int vol) { area_ = vol; }

    int getArea() { return area_; }

private:
    int area_ = 0;
};