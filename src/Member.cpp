#include "Member.hpp"

Member::Member(const std::string& name, const int ID) : Person { name }, m_ID { ID } {}

int Member::getID() const {
    return m_ID;
}