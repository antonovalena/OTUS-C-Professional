#include"Image.h"
#include<vector>

class Document {
public:
    Document() {}
    
    void saveToFile(const char* filename);

    void loadFromFile(const char* filename);

    void addImage(Image img);

private:

    std::vector<Image> images_;
};