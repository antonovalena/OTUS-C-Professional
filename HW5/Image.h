#include<string>
#include<iostream>

class Image {
public:
    Image() {}

    Image(int h, int w): height_(h), width_(w) {}

    Image(int h, int w, std::string name, std::string desc): 
                                                height_(h), 
                                                width_(w),
                                                name_(name),
                                                description_(desc)  {}

    void setSize(int w, int h);

    void setNameAndDescription(std::string name, std::string desc);

    void draw(std::ostream& stream);

    bool parseFromString(std::string imgStr);

private:
    int height_;
    int width_;

    std::string name_;
    std::string description_;
};