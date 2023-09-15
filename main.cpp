#include <iostream>
#include <string>

using namespace std;

// Enum to represent book genres
enum Genre {
    Fiction,
    NonFiction,
    Mystery,
    ScienceFiction,
    Fantasy
};

// Structure to represent a book
struct Book {
    string title;
    string author;
    Genre genre;
    int yearOfPublication;
};


// Function to add a new book to the library
void AddBook(Book library[], int& numBooks) {
    if (numBooks < 50) {
        cout << "Enter the title of the book: ";
        cin.ignore(); // Consume the newline character left in the buffer
        getline(cin, library[numBooks].title);

        cout << "Enter the author of the book: ";
        getline(cin, library[numBooks].author);

        int genreInput;
        cout << "Enter the genre of the book (0:Fiction, 1:NonFiction, 2:Mystery, 3:ScienceFiction, 4:Fantasy): ";
        cin >> genreInput;
        
        // Validate the genre input
        if (genreInput >= 0 && genreInput <= 4) {
            library[numBooks].genre = static_cast<Genre>(genreInput);
        } else {
            cout << "Invalid genre input. Setting genre to Fiction." << endl;
            library[numBooks].genre = Genre::Fiction;
        }

        cout << "Enter the year of publication: ";
        cin >> library[numBooks].yearOfPublication;

        numBooks++;
        cout << "Book added to the library." << endl;
    } else {
        cout << "Library is full. Cannot add more books." << endl;
    }
}


// Function to list all books in the library
void ListBooks(const Book library[], int numBooks) {
    if (numBooks == 0) {
        cout << "Library is empty. No books to list." << endl;
        return;
    }

    cout << "List of books in the library:" << endl;
    for (int i = 0; i < numBooks; i++) {
        cout << "Title: " << library[i].title << endl;
        cout << "Author: " << library[i].author << endl;
        cout << "Genre: " << library[i].genre << endl;
        cout << "Year of Publication: " << library[i].yearOfPublication << endl;
        cout << "------------------------" << endl;
    }
}


// Function to search books by genre
void SearchBooksByGenre(const Book library[], int numBooks, Genre searchGenre) {
    bool found = false;

    cout << "Books in the selected genre:" << endl;
    for (int i = 0; i < numBooks; i++) {
        if (library[i].genre == searchGenre) {
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year of Publication: " << library[i].yearOfPublication << endl;
            cout << "------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No books found in the selected genre." << endl;
    }
}

// Function to search books by author
void SearchBooksByAuthor(const Book library[], int numBooks, const string& searchAuthor) {
    bool found = false;

    cout << "Books by the selected author:" << endl;
    for (int i = 0; i < numBooks; i++) {
        if (library[i].author == searchAuthor) {
            cout << "Title: " << library[i].title << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "Year of Publication: " << library[i].yearOfPublication << endl;
            cout << "------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No books found by the selected author." << endl;
    }
}

int main() {
    const int MAX_BOOKS = 50;
    Book library[MAX_BOOKS];
    int numBooks = 0;
    string searchAuthor; // Declare searchAuthor outside the switch block

    while (true) {
        cout << "Library Management System Menu:" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. List all books" << endl;
        cout << "3. Search books by genre" << endl;
        cout << "4. Search books by author" << endl;
        cout << "5. Quit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                AddBook(library, numBooks);
                break;
            case 2:
                // Sort the books by publication year
                for (int i = 0; i < numBooks - 1; i++) {
                    for (int j = 0; j < numBooks - i - 1; j++) {
                        if (library[j].yearOfPublication > library[j + 1].yearOfPublication) {
                            // Swap the books
                            Book temp = library[j];
                            library[j] = library[j + 1];
                            library[j + 1] = temp;
                        }
                    }
                }
                ListBooks(library, numBooks);
                break;
            case 3:
                int searchGenre;
                cout << "Enter the genre to search (0:Fiction, 1:NonFiction, 2:Mystery, 3:ScienceFiction, 4:Fantasy): ";
                cin >> searchGenre;
                SearchBooksByGenre(library, numBooks, static_cast<Genre>(searchGenre));
                break;
            case 4:
                cout << "Enter the author's name to search: ";
                cin.ignore(); // Consume the newline character left in the buffer
                getline(cin, searchAuthor);
                SearchBooksByAuthor(library, numBooks, searchAuthor);
                break;
            case 5:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

