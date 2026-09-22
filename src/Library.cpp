#include "Library.hpp"
#include "Exceptions.hpp"

int Library::m_IDCounter = 1;

void Library::registerMember(const std::string& name) {
    m_members.insert({m_IDCounter, std::make_shared<Member>(name, m_IDCounter)});
    ++m_IDCounter;
}

void Library::reserveBook(std::weak_ptr<Member> member, const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();

    if (m_borrowedBooksList.find(tmpBook->getISBN()) != m_borrowedBooksList.end()) {
        m_reservations[tmpBook->getISBN()].push(member);
    } else { 
        issueBook(member, book);
    }
}

void Library::issueBook(std::weak_ptr<Member> member, const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();
    std::shared_ptr<Member> tmpMember = member.lock();
    
    m_borrowedBooksList.insert(tmpBook->getISBN());
    tmpMember->borrowBook(book);
}

void Library::returnBook(std::weak_ptr<Member> member, const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();
    std::shared_ptr<Member> tmpMember = member.lock();
    
    m_borrowedBooksList.erase(tmpBook->getISBN());
    tmpMember->returnBook(book);

    updateReservation(book);
}

void Library::updateReservation(const std::weak_ptr<Book>& book) {
    std::shared_ptr<Book> tmpBook = book.lock();

    if (m_reservations.find(tmpBook->getISBN()) != m_reservations.end()) {
        issueBook(m_reservations.at(tmpBook->getISBN()).front(), book);
        m_reservations.at(tmpBook->getISBN()).pop();
    }
}

void Library::displayAllMembers() const {
    if (m_members.empty()) {
        std::cout << "No users found in database\n";
    }

    for (const auto&[ID, member]: m_members) {
        std::cout << *member << "\n";
    }
}

void Library::updateInvalidReservation(const Repository& repository, int ISBN) {
    try { 
        auto book = repository.getBookByISBN(ISBN);
    } catch(const LibraryExceptions& e) {
        std::cout << "Removing invalid book reservations...\n";
        m_reservations.erase(ISBN);
    }
}

void Library::deleteAllMembers() {
    m_members.clear();
    Library::m_IDCounter = 1;
}

std::weak_ptr<Member> Library::getMemberByID(int ID) const {
    if (m_members.find(ID) == m_members.end()) {
        throw MemberNotFoundException("Member with the ID-" + std::to_string(ID) + " not found");
    }
    return m_members.at(ID);
}

void Library::saveMembers(const std::string& fileName) {
    std::ofstream file(fileName);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open the file\n";
        return;
    }

    for (const auto& [ID, member]: m_members) {
        file << member->getName() << "\n";
    }

    file.close();
}

void Library::loadMembers(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to opent he file\n";
        return;
    }

    deleteAllMembers();

    std::string line{};

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        
        std::string name{};

        std::getline(ss, name, ',');

        registerMember(name);
    }

    file.close();
}

void Library::interface(Repository& repository) {
    // pre made for testing
    registerMember("User1");
    registerMember("User2");
    repository.addBook(10, "Book1", "Author1", "Genre1");
    repository.addBook(11, "Book2", "Author2", "Genre2");
    repository.addBook(12, "Book3", "Author3", "Genre3");

    std::cout << "Welcome to the library. Here are the features currently available"; 
    int userInput{};

    do {
        std::cout << "\n0: Quit the program\n"
                  << "1: Register a member\n"
                  << "2: Reserve a book\n"
                  << "3: Return a book\n"
                  << "4: Add a book\n"
                  << "5: Remove a book\n"
                  << "6: Display books catalog\n"
                  << "7: Display all members\n"
                  << "8. Save members data\n"
                  << "9: Load members data\n"
                  << "10: Save books data\n"
                  << "11: Load books data\n"
                  << "12: Delete all members\n"
                  << "13: Delete all books\n"
                  << "Enter the number for the feature you would like to try out\n"; 
        std::cin >> userInput;
        std::cout << "\n";

        switch (userInput) {
            case 0: {
                return;
            }
            case 1: {
                std::string username{};
                std::cout << "Enter your name\n";
                std::cin >> username;
                registerMember(username);
                break;
            }
            case 2: {
                int memberID{};
                std::cout << "Enter Member ID\n";
                std::cin >> memberID;
                int ISBN{};
                std::cout << "Enter the book ISBN\n";
                std::cin >> ISBN;
                try {
                    reserveBook(getMemberByID(memberID), repository.getBookByISBN(ISBN));
                } catch (const LibraryExceptions& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 3: {
                int memberID{};
                std::cout << "Enter Member ID\n";
                std::cin >> memberID;
                int ISBN{};
                std::cout << "Enter the book ISBN\n";
                std::cin >> ISBN;
                try {
                    returnBook(getMemberByID(memberID), repository.getBookByISBN(ISBN));
                } catch (const LibraryExceptions& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 4: {
                int ISBN{};
                std::string name{};
                std::string author{};
                std::string genre{};
                std::cout << "Enter ISBN number\n";
                std::cin >> ISBN;
                std::cout << "Enter the name of the book\n";
                std::cin >> name;
                std::cout << "Enter the author name\n";
                std::cin >> author;
                std::cout << "Enter genre\n";
                std::cin >> genre;
                try {
                    repository.addBook(ISBN, name, author, genre);
                } catch (const LibraryExceptions& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 5: {
                int ISBN{};
                std::cout << "Enter ISBN number\n";
                std::cin >> ISBN;
                try {
                    repository.removeBook(ISBN);
                    updateInvalidReservation(repository, ISBN);
                } catch (const LibraryExceptions& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 6: {
                repository.displayBooksCatalog();
                break;
            }
            case 7: {
                displayAllMembers();
                break;
            }
            case 8: {
                saveMembers("MemberData.txt");
                break;
            }
            case 9: {
                loadMembers("MemberData.txt");
                break;
            }
            case 10: {
                repository.saveBooks("BooksData.txt");
                break;
            }
            case 11: {
                repository.loadBooks("BooksData.txt");
                break;
            }
            case 12: {
                deleteAllMembers();
                break;
            }
            case 13: {
                repository.deleteAllBooks();
                break;
            }
            default:    
                std::cout << userInput << "No feature avaiable with this input " << userInput << "\n";
                break;
        }
    } while (userInput != 0);
}