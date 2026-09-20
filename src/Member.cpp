#include "Member.hpp"
#include "Exceptions.hpp"

Member::Member(const std::string& name, const int ID) : Person { name }, m_ID { ID } {}

int Member::getID() const {
    return m_ID;
}

void Member::borrowBook(std::weak_ptr<Book> book) {
    std::shared_ptr tmpBook = book.lock();
    for (const auto& borrowedBook: borrowedBooks) {
        std::shared_ptr<Book> tmpBorrowedBook = borrowedBook.lock();
        if (tmpBook->getISBN() == tmpBorrowedBook->getISBN()) {
            throw DuplicateBookException("You have already borrowed the book " + tmpBook->getName() + " : by " + tmpBook->getAuthor());
        }
    }

    const int borrowedBooksLimit = 3;
    if (borrowedBooks.size() == borrowedBooksLimit) {
        throw BorrowedBooksLimitReachedException("You have reached the limit of maximum books you can borrow: " + std::to_string(borrowedBooksLimit));
    }

    borrowedBooks.push_back(std::move(book));
}

void Member::returnBook(const std::weak_ptr<Book>& book) {
    std::shared_ptr tmpBook = book.lock();
    for (int i{}; i < borrowedBooks.size(); ++i) {
        std::shared_ptr<Book> tmpBorrowedBook = borrowedBooks[i].lock();
        if (tmpBook->getISBN() == tmpBorrowedBook->getISBN()) {
            borrowedBooks.erase(borrowedBooks.begin() + i);
        }
    }

    throw BookNotFoundException("You haven't borrowed the book " + tmpBook->getName() + " : by " + tmpBook->getAuthor());
}