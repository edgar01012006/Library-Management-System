#include "Member.hpp"
#include "Exceptions.hpp"

Member::Member(const std::string& name, const int ID) : Person { name }, m_ID { ID } {}

int Member::getID() const {
    return m_ID;
}

const std::vector<std::weak_ptr<Book>>& Member::getBorrowedBooks() const {
    return m_borrowedBooks;
}

void Member::borrowBook(std::weak_ptr<Book> book) {
    std::shared_ptr tmpBook = book.lock();
    for (const auto& borrowedBook: m_borrowedBooks) {
        std::shared_ptr<Book> tmpBorrowedBook = borrowedBook.lock();
        if (tmpBook->getISBN() == tmpBorrowedBook->getISBN()) {
            throw DuplicateBookException("You have already borrowed the book " + tmpBook->getName() + " : by " + tmpBook->getAuthor());
        }
    }

    const int borrowedBooksLimit = 3;
    if (m_borrowedBooks.size() == borrowedBooksLimit) {
        throw BorrowedBooksLimitReachedException("You have reached the limit of maximum books you can borrow: " + std::to_string(borrowedBooksLimit));
    }

    m_borrowedBooks.push_back(std::move(book));
}

void Member::returnBook(const std::weak_ptr<Book>& book) {
    std::shared_ptr tmpBook = book.lock();
    for (size_t i{}; i < m_borrowedBooks.size(); ++i) {
        std::shared_ptr<Book> tmpBorrowedBook = m_borrowedBooks[i].lock();
        if (tmpBook->getISBN() == tmpBorrowedBook->getISBN()) {
            m_borrowedBooks.erase(m_borrowedBooks.begin() + i);
            return;
        }
    }

    throw BookNotFoundException("You haven't borrowed the book " + tmpBook->getName() + " : by " + tmpBook->getAuthor());
}

void Member::updatebBorrowedBooks() {
    for (size_t i{}; i < m_borrowedBooks.size();) {
        if (m_borrowedBooks[i].expired()) {
            std::cout << "Removing invalid book from borrowed books list...\n";
            m_borrowedBooks.erase(m_borrowedBooks.begin() + i);
        } else {
            ++i;
        }
    }
}

std::ostream& operator<<(std::ostream& ostr, Member& member) {
    member.updatebBorrowedBooks();

    ostr << "Name: " << member.getName()
         << "\nID: " << member.getID()
         << "\nborrowed Books List (ISBNs): ";

    if (member.getBorrowedBooks().empty()) {
        std::cout << "No borrowed books";
    } else {
        for (const auto& book: member.getBorrowedBooks()) {
        std::shared_ptr tmpBook = book.lock();
        ostr << tmpBook->getISBN() << " ";
        }
    }
    std::cout << "\n";   

    return ostr;
}