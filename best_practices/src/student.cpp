#include "../student.h"

Student::Student(std::string name, std::string id) : _name(name), _id(id) {}

void Student::print_name() {
    std::cout << "Name: " << _name << std::endl;
}
void Student::print_id() {
    std::cout << "ID: " << _id << std::endl;
}
