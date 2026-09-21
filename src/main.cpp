#include "Book.hpp"
#include "Exceptions.hpp"
#include "Library.hpp"
#include "Member.hpp"
#include "Person.hpp"
#include "Repository.hpp"

int main() {
    Repository repository;
    Library library;
    library.interface(repository);
}