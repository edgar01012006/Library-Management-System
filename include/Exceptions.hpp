#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class LibraryExceptions : public std::runtime_error {
    public:
        LibraryExceptions(const std::string& msg) : std::runtime_error(msg) {}
};  

class DuplicateISBNException : public LibraryExceptions {
    public:
        DuplicateISBNException(const std::string& msg) : LibraryExceptions(msg) {}
};

class ISBNNotFoundException : public LibraryExceptions {
    public:
        ISBNNotFoundException(const std::string& msg) : LibraryExceptions(msg) {}
};

class DuplicateBookException : public LibraryExceptions {
    public:
        DuplicateBookException(const std::string& msg) : LibraryExceptions(msg) {}
};

class BorrowedBooksLimitReachedException : public LibraryExceptions {
    public:
        BorrowedBooksLimitReachedException(const std::string& msg) : LibraryExceptions(msg) {}
};

class BookNotFoundException : public LibraryExceptions {
    public:
        BookNotFoundException(const std::string& msg) : LibraryExceptions(msg) {}
};

class MemberNotFoundException : public LibraryExceptions {
    public:
        MemberNotFoundException(const std::string& msg) : LibraryExceptions(msg) {}
};

#endif