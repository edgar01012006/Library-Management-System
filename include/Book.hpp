#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

class Book {
    private:
        int m_ISBN;
        std::string m_name;
        std::string m_author;
        std::string m_genre;

    public:
        Book();
        Book(int ISBN, const std::string& name, const std::string& author, const std::string& genre);
        
        int getISBN() const;
        std::string getName() const;
        std::string getAuthor() const;
        std::string getGenre() const;

        friend std::ostream& operator<<(std::ostream& ostr, const Book& book);
        // friend bool operator==(const int ISBN, const std::string& name);
        // friend bool operator==(const std::string& name, const int ISBN);
};

#endif