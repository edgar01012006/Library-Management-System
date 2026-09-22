#include "Repository.hpp"
#include "Exceptions.hpp"

void Repository::addBook(int ISBN, const std::string& name, const std::string& author, const std::string& genre) {
    if (m_books.find(ISBN) == m_books.end()) {
        m_books.insert({ ISBN, std::make_shared<Book>(ISBN, name, author, genre) });
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

std::weak_ptr<Book> Repository::getBookByISBN(int ISBN) const {
    if (m_books.find(ISBN) != m_books.end()) {
        return m_books.at(ISBN);
    } else {
        throw ISBNNotFoundException("ISBN with the number " + std::to_string(ISBN) + " was not found");
    }
    return {};
}

void Repository::displayBooksCatalog() const {
    if (m_books.empty()) {
        std::cout << "No books found in database\n";
    }
    
    for (const auto& [ISBN, book] : m_books) {
        std::cout << *book << "\n";
    }
}

void Repository::deleteAllBooks() {
    m_books.clear();
}

void Repository::saveBooks(const std::string& fileName) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file\n";
        return;
    }

    for (const auto&[ISBN, Book]: m_books) {
        file << Book->getISBN() << ","
             << Book->getName() << ","
             << Book->getAuthor() << ","
             << Book->getGenre() << "\n";
    }

    file.close();
}

void Repository::loadBooks(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file\n";
        return;
    }

    std::string line{};

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string ISBN{};
        std::string name;
        std::string author;
        std::string genre;

        std::getline(ss, ISBN, ',');
        std::getline(ss, name, ',');
        std::getline(ss, author, ',');
        std::getline(ss, genre, ',');

        addBook(std::stoi(ISBN), name, author, genre);
    }

    file.close();
}