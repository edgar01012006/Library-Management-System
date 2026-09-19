#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "Person.hpp"

class Member : public Person {
    private:
        int m_ID;

    public:
        Member(const std::string& name, const int ID);

        int getID() const;
};

#endif