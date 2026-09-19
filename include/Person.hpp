#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person {
    private:
        std::string m_name;

    public:
        Person(const std::string& name);

        std::string getName() const;
};

#endif