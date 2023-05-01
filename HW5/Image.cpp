#include"Image.h"
#include<iostream>

void Image::setSize(int w, int h) {
    height_ = h;
    width_ = w;
}

void Image::setNameAndDescription(std::string name, std::string desc) {
    name_ = name;
    description_ = desc;
}

void Image::draw(std::ostream& stream){
    stream << "{Img: \"" << name_ << "\" size: " <<
     width_ << "x" << height_ <<
     " description: " << description_ << "}" << std::endl;
}

bool Image::parseFromString(std::string imgStr) {
    size_t foundPos = imgStr.find("Img: \"");
    if (foundPos == std::string::npos) {
        std::cerr << "img not found" << std::endl;
        return false;
    }

    for (size_t i = foundPos+6; imgStr[i] != '"'; ++i) {
        name_.push_back(imgStr[i]);
    }

    foundPos = imgStr.find("size: ");
    if (foundPos == std::string::npos) {
        std::cerr << "size not found" << std::endl;
        return false;
    }
    
    std::string w;
    size_t ind;
    for(ind = foundPos+5; imgStr[ind] != 'x'; ++ind) {
        w.push_back(imgStr[ind]);
    }
    std::string h;
    for(ind = ind+1; imgStr[ind] != ' '; ++ind) {
        h.push_back(imgStr[ind]);
    }
    setSize(std::atoi(w.c_str()), std::atoi(h.c_str()));

    foundPos = imgStr.find("description: ");
    if (foundPos == std::string::npos) {
        std::cerr << "desc not found" << std::endl;
        return false;
    }
    for(size_t i = foundPos+13; imgStr[i] != '}'; ++i) {
        description_.push_back(imgStr[i]);
    }

    return true;
}