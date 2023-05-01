#include"Document.h"
#include<fstream>

void Document::saveToFile(const char* filename) {
    std::ofstream file;
    file.open(filename);
    for (auto& img: images_) {
        img.draw(file);
    }

    file.close();
}

void Document::loadFromFile (const char* filename) {
    std::ifstream file(filename);
    std::string curImgStr;
    while(file) {
        Image curImg;
        std::getline(file, curImgStr);
        if(curImg.parseFromString(curImgStr)) {
            addImage(curImg);
        } 

        std::getline(file, curImgStr);
    }
    file.close();
}

void Document::addImage(Image img) {
    images_.push_back(img);
}
