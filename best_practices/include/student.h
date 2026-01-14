#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <ostream>
#include <string>

class Student {
    std::string _name;
    std::string _id;

public:
    Student() = default;
    Student(std::string name, std::string id);

    void print_name();
    void print_id();
};

#endif