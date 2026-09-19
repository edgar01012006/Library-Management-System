#include "Person.hpp"

Person::Person(const std::string& name) : m_name { name } {}

std::string Person::getName() const {
    return m_name;
}