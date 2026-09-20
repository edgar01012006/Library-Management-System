#include "Library.hpp"

int Library::m_IDCounter = 1;

void Library::registerMember(const std::string& name) {
    m_members.insert({m_IDCounter, std::make_shared<Member>(name, m_IDCounter)});
}

void Library::reserveBook(std::weak_ptr<Member>& member, const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();

    if (m_borrowedBooksList.find(tmpBook->getISBN()) != m_borrowedBooksList.end()) {
        m_reservations[tmpBook->getISBN()].push(member);
    } else { 
        issueBook(member, book);
    }
}

void Library::issueBook(std::weak_ptr<Member>& member, const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();
    std::shared_ptr<Member> tmpMember = member.lock();
    
    m_borrowedBooksList.insert(tmpBook->getISBN());
    tmpMember->borrowBook(book);
}

void Library::returnBook(std::weak_ptr<Member>& member, const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();
    std::shared_ptr<Member> tmpMember = member.lock();
    
    m_borrowedBooksList.erase(tmpBook->getISBN());
    tmpMember->returnBook(book);

    updateReservation(book);
}

void Library::updateReservation(const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();

    if (m_reservations.find(tmpBook->getISBN()) != m_reservations.end()) {
        issueBook(m_reservations.at(tmpBook->getISBN()).front(), book);
        m_reservations.at(tmpBook->getISBN()).pop();
    }
}

void Library::displayAllMembers() const {
    
}

void Library::interface() {
    std::cout << "Welcome to the library. Here are the features currently available\n" 
              << "1: Register a member\n"
              << "2: Reserve a book\n"
              << "3: Return a book\n"
              << "4: Add a book\n"
              << "5: Remove a book\n"
              << "6: Display books catalog\n"
              << "Enter the number for the feature you would like to try out\n"; 

    int userInput{};
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::string username;
            std::cout << "Enter your name\n";
            std::cin >> username;
            registerMember(username);
    }
}