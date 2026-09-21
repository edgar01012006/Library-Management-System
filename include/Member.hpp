#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "Person.hpp"
#include <vector>
#include "Book.hpp"
#include <memory>
#include <utility>
#include <iostream>

class Member : public Person {
    private:
        int m_ID;
        std::vector<std::weak_ptr<Book>> m_borrowedBooks;

    public:
        Member(const std::string& name, const int ID);

        int getID() const;
        const std::vector<std::weak_ptr<Book>>& getBorrowedBooks() const;

        void borrowBook(std::weak_ptr<Book> book);
        void returnBook(const std::weak_ptr<Book>& book);

        void updatebBorrowedBooks();

        friend std::ostream& operator<<(std::ostream& ostr, Member& member);
};

#endif