#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include <unordered_map>
#include "Book.hpp"

class Repository {
    private:
        std::unordered_map<int, Book> m_books;

    public:
        void addBook(int ISBN, const std::string& name, const std::string& author, const std::string& genre);
        void removeBook(int ISBN);

        const Book& getBookByISBN(int ISBN) const;
        void displayBooksCatalog() const;
        // void displayBooksByGenre(const std::string& genre)
};

#endif