#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <map>
#include <queue>
#include "Member.hpp"

class Library {
    private:
        std::map<int, std::queue<Member>> m_reservations;
};

#endif