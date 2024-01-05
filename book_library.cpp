#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Book structure to hold book information
struct Book {
    string title;
    string author;
    string ISBN;
    bool available;
    string studentName;
    double price;
};

// Library class to manage books
class Library {
private:
    vector<Book> catalog;

public:
    // Function to add a new book to the catalog
    void addBook() {
        Book newBook;
        cout << "Enter book title: ";
        getline(cin >> ws, newBook.title);
        cout << "Enter book author: ";
        getline(cin >> ws, newBook.author);
        cout << "Enter book ISBN: ";
        cin >> newBook.ISBN;
        cout << "Enter book price: ";
        cin >> newBook.price;
        newBook.available = true; // Book initially available
        newBook.studentName = ""; // No student assigned initially
        catalog.push_back(newBook);
        cout << "Book added to the catalog." << endl;
    }

    // Function to remove a book from the catalog
    void removeBook() {
        string searchISBN;
        cout << "Enter the ISBN of the book you want to remove: ";
        cin >> searchISBN;

        auto iter = find_if(catalog.begin(), catalog.end(), [searchISBN](const Book& b) {
            return b.ISBN == searchISBN;
        });

        if (iter != catalog.end()) {
            iter->available = true; // Book is removed, so it's available again
            iter->studentName = ""; // Clear student name
            catalog.erase(iter);
            cout << "Book removed from the catalog." << endl;
        } else {
            cout << "Book with ISBN " << searchISBN << " not found." << endl;
        }
    }

    // Function to check book availability by title or ISBN
    void checkBookAvailability() {
        string searchInput;
        cout << "Enter the title or ISBN of the book: ";
        cin >> searchInput;

        auto iter = find_if(catalog.begin(), catalog.end(), [searchInput](const Book& b) {
            return (b.title == searchInput || b.ISBN == searchInput);
        });

        if (iter != catalog.end()) {
            if (iter->available) {
                cout << "The book '" << iter->title << "' is available." << endl;
            } else {
                cout << "The book '" << iter->title << "' is not available. It is currently borrowed by " << iter->studentName << "." << endl;
            }
        } else {
            cout << "Book with title or ISBN '" << searchInput << "' not found." << endl;
        }
    }

    // Function to display the catalog
    void displayCatalog() {
        cout << "Catalog:" << endl;
        for (const auto& book : catalog) {
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "ISBN: " << book.ISBN << endl;
            cout << "Price: " << book.price << endl;
            cout << "Availability: " << (book.available ? "Available" : "Not Available") << endl;
            if (!book.available) {
                cout << "Borrowed by: " << book.studentName << endl;
            }
            cout << "-------------------------------------------" << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a Book\n";
        cout << "2. Remove a Book\n";
        cout << "3. Check Book Availability\n";
        cout << "4. Display Catalog\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore(); // Clear input buffer
                library.addBook();
                break;
            case 2:
                library.removeBook();
                break;
            case 3:
                library.checkBookAvailability();
                break;
            case 4:
                library.displayCatalog();
                break;
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}
