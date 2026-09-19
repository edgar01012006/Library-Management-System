#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class LibraryExceptions : std::runtime_error {
    public:
        LibraryExceptions(const std::string& msg) : std::runtime_error(msg) {}
};  

class DuplicateISBNException : LibraryExceptions {
    public:
        DuplicateISBNException(const std::string& msg) : LibraryExceptions(msg) {}
};

class ISBNNotFoundException : LibraryExceptions {
    public:
        ISBNNotFoundException(const std::string& msg) : LibraryExceptions(msg) {}
};

#endif