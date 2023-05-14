#pragma once

#include <ostream>

class IEditable {
public:
    virtual ~IEditable() = default;
    virtual void print(std::ostream& out) = 0;
};