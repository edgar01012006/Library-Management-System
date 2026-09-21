#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>
#include <iostream>
#include "Member.hpp"
#include "Book.hpp"
#include "Repository.hpp"

class Library {
    private:
        static int m_IDCounter;
        std::unordered_map<int, std::shared_ptr<Member>> m_members;
        std::unordered_map<int, std::queue<std::weak_ptr<Member>>> m_reservations;
        std::unordered_set<int> m_borrowedBooksList;

    public:
        void registerMember(const std::string& name);

        void reserveBook(std::weak_ptr<Member> member, const std::weak_ptr<Book>& book);
        void issueBook(std::weak_ptr<Member> member, const std::weak_ptr<Book>& book);
        void returnBook(std::weak_ptr<Member> member, const std::weak_ptr<Book>& book);
        void updateReservation(const std::weak_ptr<Book>& book);

        void displayAllMembers() const;

        void updateInvalidReservation(const Repository& repository, int ISBN);
        
        std::weak_ptr<Member> getMemberByID(int ID) const;

        void interface(Repository& repository);
};

#endif