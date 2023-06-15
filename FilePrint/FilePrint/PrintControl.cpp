// pch.cpp: 与预编译标头对应的源文件

#include "PrintControl.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
PrintControl::PrintControl(const char* filepath, int number = 1)
{
    this->filePath = filepath;
    this->number = number;
}

PrintControl::~PrintControl()
{
}
void PrintControl::SetPath(const char* filepath) {
    this->filePath = filePath;
}
void PrintControl::setNumber(int number) {
    this->number = number;
}
void PrintControl::print_once() {
    char printer_name[256];
    DWORD size = sizeof(printer_name);
    GetDefaultPrinterA(printer_name, &size);
    ShellExecuteA(
        NULL,
        "print",
        this->filePath,
        NULL,
        NULL,
        SW_HIDE
    );
}

void PrintControl::print_file() {
    for (int i = 0; i < this->number; i++) {
        char printer_name[256];
        DWORD size = sizeof(printer_name);
        GetDefaultPrinterA(printer_name, &size);
        ShellExecuteA(
            NULL,
            "print",
            this->filePath,
            NULL,
            NULL,
            SW_HIDE
        );
    }
}