#include <iostream>
#include <memory>

struct Student {
    std::string name;
    std::string id;
    ~Student() { std::cout << "Student::~Student" << std::endl; }
};

class SmartPtr {
    Student* _student {nullptr};

    explicit SmartPtr(Student* student) : _student(student) {
    }

public:
    static SmartPtr make_smartptr() {
        std::cout << "allocating new student" << std::endl;
        return SmartPtr(new Student());
    }

    SmartPtr(SmartPtr&& other) {
        _student = other._student;
        other._student = nullptr;
    }

    ~SmartPtr() {
        if (_student) std::cout << "Student deleted" << std::endl;
        delete _student;
    }

    Student* get() { return _student; }
    Student* operator->() { return _student; }
    bool operator==(const Student* student) const { return _student == student; }
};

int main() {
    auto print = [](auto& desc, auto& s) {
        std::cout << desc << s->name << " (" << s->id << ")" << std::endl;
    };
    {
        // using regular pointers
        auto s = new Student();
        s->id = "W111222";
        s->name = "john";
        print("OLD PTR: ", s);
        // don't forget
        delete s;
    }
    std::cout << "--------------------" << std::endl;
    {
        auto sp1 = SmartPtr::make_smartptr();
        sp1->id = "W222333";
        sp1->name = "jane";
        print("ORIGINAL: ", sp1);

        // borrow a reference to the data
        auto student = sp1.get();
        print("REFERENCED: ", student);

        // give ownership to another variable
        auto sp2 = std::move(sp1);
        print("MOVED: ", sp2);

        // sp1 no longer has access to the moved data
    }
    std::cout << "--------------------" << std::endl;
    {
        // STL version
        auto up1 = std::make_unique<Student>();
        up1->id = "W333444";
        up1->name = "jill";
        print("UNIQUE: ", up1);

        // reference the data
        auto student = up1.get();
        print("REFERENCED: ", student);

        // move the ownership
        auto up2 = std::move(up1);
        print("MOVED: ", up2);
 // up1 no longer has access to the data
    }
    return 0;
}
