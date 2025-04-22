#include <iostream>
#include <cstring>  // For strcpy and strlen

using namespace std;
class Book {
private:
    char* title;
    char* author;
    int pageCount;
    bool formatType;  // true = hardcover, false = paperback
    float* chapterPages;
    int numChapters;

public:
    // Default Constructor
    Book() {
        title = new char[1];
        title[0] = '\0';
        author = new char[1];
        author[0] = '\0';

        pageCount = 0;
        formatType = false;
        numChapters = 0;
        chapterPages = nullptr;
    }

    // Parameterized Constructor
    Book(const char* t, const char* a, int pCount, bool format, int chapters)
        : pageCount(pCount), formatType(format), numChapters(chapters) {
        title = new char[strlen(t) + 1];
        strcpy(title, t);

        author = new char[strlen(a) + 1];
        strcpy(author, a);

        if (numChapters > 0) {
            chapterPages = new float[numChapters];

            // Distribute pages uniformly
            float avgPages = (numChapters > 0) ? static_cast<float>(pageCount) / numChapters : 0;
            for (int i = 0; i < numChapters; i++) {
                chapterPages[i] = avgPages;
            }
        } else {
            chapterPages = nullptr;
        }
    }

    // Copy Constructor (Deep Copy)
    Book(const Book& other)
        : pageCount(other.pageCount), formatType(other.formatType), numChapters(other.numChapters) {
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);

        author = new char[strlen(other.author) + 1];
        strcpy(author, other.author);

        if (numChapters > 0) {
            chapterPages = new float[numChapters];
            for (int i = 0; i < numChapters; i++) {
                chapterPages[i] = other.chapterPages[i];
            }
        } else {
            chapterPages = nullptr;
        }
    }

    // Destructor
    ~Book() {
        delete[] title;
        delete[] author;
        delete[] chapterPages;
    }

    // Display Book Information
    void display() const {
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Page Count: " << pageCount << "\n";
        cout << "Format: " << (formatType ? "Hardcover" : "Paperback") << "\n";
        cout << "Number of Chapters: " << numChapters << "\n";
        if (numChapters > 0) {
            cout << "Chapter Pages: ";
            for (int i = 0; i < numChapters; i++) {
                cout << chapterPages[i] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    // Using Default Constructor
    Book book1;
    book1.display();
    
    cout << "\n";

    // Using Parameterized Constructor
    Book book2("Batatyachi chal", "P.L.Deshpande", 500, true, 10);
    book2.display();
    
    cout << "\n";

    // Using Copy Constructor
    Book book3(book2);
    book3.display();

    return 0;
}
