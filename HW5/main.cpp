#include"Editor.h"

int main() {
    Editor editor;

    editor.createDocument("myDoc");

    auto myDoc = editor.getDocument("myDoc");
    myDoc->addSquare(2);
}