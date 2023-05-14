#pragma once

#include "Square.h"
#include <vector>
#include <memory>

class Document : public IEditable {
public:
    Document() {}

    virtual ~Document() = default;
    
    void print(std::ostream& out) override;

    void saveToFile(const char*) { /*implementation*/ };

    void loadFromFile(const char*) { /*implementation*/ };

    void addSquare(int side);

    bool removeShape(IShape*) { /*implementation*/ return true; };

private:

    std::vector<std::unique_ptr<IShape> > shapes_;
};