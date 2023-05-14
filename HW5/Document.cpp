#include"Document.h"

void Document::print(std::ostream& out) {
    out << "Document: \nShapes list:\n";
    for(auto& shape: shapes_) {
        shape->print(out);
    }
}

void Document::addSquare(int side) {
    shapes_.emplace_back(std::make_unique<Square>(side));
}
