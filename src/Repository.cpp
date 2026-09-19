#include "Repository.hpp"
#include "Exceptions.hpp"

void Repository::addBook(int ISBN, const std::string& name, const std::string& author, const std::string& genre) {
    if (m_books.find(ISBN) == m_books.end()) {
        m_books.insert({ ISBN, {ISBN, name, author, genre} });
    } else {
        throw DuplicateISBNException("ISBN with the number " + std::to_string(ISBN) + " already exists");
    }
}

void Repository::removeBook(int ISBN) {
    if (m_books.find(ISBN) != m_books.end()) {
        m_books.erase(ISBN);
    } else {
        throw ISBNNotFoundException("ISBN with the number " + std::to_string(ISBN) + " was not found");
    }
}

const Book& Repository::getBookByISBN(int ISBN) const {
    if (m_books.find(ISBN) != m_books.end()) {
        return m_books.at(ISBN);
    } else {
        throw ISBNNotFoundException("ISBN with the number " + std::to_string(ISBN) + " was not found");
    }
    return {};
}

void Repository::displayBooksCatalog() const {
    for (const auto& [ISBN, book] : m_books) {
        std::cout << book;
    }
}

// void Repository::displayBooksByGenre(const std::string& genre)