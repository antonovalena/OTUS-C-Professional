#pragma once

#include "Document.h"
#include <map>
#include <memory>

class Editor{
public:
    Editor() {}

    void createDocument(const char* docName) {
        if (documents_.find(docName) != documents_.end()) {
            return;
        }

        documents_[docName] = std::make_unique<Document>();
    }

    Document* getDocument(const char* docName) {
        if (documents_.find(docName) == documents_.end()) {
            return nullptr;
        }
        return documents_[docName].get();
    } 

    void exportDocument(const char* /*docName*/, const char* /*filename*/) {}

    void importDocument(const char* /*docName*/, const char* /*fileame*/) {}


private:
    std::map<std::string, std::unique_ptr<Document> > documents_;
};