#include"Editor.h"

int main() {
    Editor editor;

    editor.createDocument("myDoc");

    editor.importDocument("myDoc", "../myDoc_import.txt");
    editor.exportDocument("myDoc", "../myDoc_export.txt");
}