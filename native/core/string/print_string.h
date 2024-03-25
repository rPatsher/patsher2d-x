// PrintString.h
#ifndef PRINT_STRING_H
#define PRINT_STRING_H

#include <thread>
#include <cstring>
#include <iostream>
#include <vector>

extern void print_error_line(const char* error);
extern void print_line(const char* line);
extern void print_line_rich(const char* line); // Declaration of the new rich printing function

class PrintString {
public:
    PrintString();
    ~PrintString();

    void print(const char* str);
    void print_handler_list();
    void print_line_rich(const char* line); // Member function to handle rich printing

private:
    std::thread printingThread;
    char* textToPrint;
    bool isPrinting;

    static std::vector<std::string> handlerList;
    static void register_handler(const std::string& handlerName);
    void printingFunction();
};

#endif // PRINT_STRING_H