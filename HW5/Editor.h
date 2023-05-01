#include"Document.h"
#include<map>
#include<memory>

class Editor{
public:
    Editor() {}

    void createDocument(const char* docName) {
        if (documents_.find(docName) != documents_.end()) {
            return;
        }

        documents_[docName] = std::make_unique<Document>();
    }

    void exportDocument(const char* docName, const char* filename) {
        auto doc = documents_.find(docName);
        if (doc == documents_.end()) {
            return;
        }

        doc->second->saveToFile(filename);
    }

    void importDocument(const char* docName, const char* fileame) {
        if(!documents_.count(docName)) {
            createDocument(docName);
        }

        auto doc = documents_.find(docName);
        doc->second->loadFromFile(fileame);
    }


private:
    std::map<std::string, std::unique_ptr<Document> > documents_;
};