#include "Book.hpp"

Book::Book() : m_ISBN { -1 }, m_name {}, m_author {}, m_genre {} {}

Book::Book(int ISBN, const std::string& name, const std::string& author, const std::string& genre)
    : m_ISBN { ISBN }, m_name { name }, m_author { author }, m_genre { genre } {}

int Book::getISBN() const { return m_ISBN; }
std::string Book::getName() const { return m_name; }
std::string Book::getAuthor() const { return m_author; }
std::string Book::getGenre() const { return m_genre; }

std::ostream& operator<<(std::ostream& ostr, const Book& book) {
    ostr << "ISBN: " << book.getISBN()
         << "\nName: " << book.getName()
         << "\nAuthor: " << book.getAuthor()
         << "\nGenre: " << book.getGenre() << "\n";

    return ostr;
}
