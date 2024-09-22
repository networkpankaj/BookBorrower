#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Book {
  string title;
  string author;

   string displayTitle() const {
        return "\"" + title + "\"";
    }

    bool operator<(const Book& other) const {
        if (author != other.author)
            return author < other.author;
        return title < other.title;
    }
};

int main() {
   vector<Book> library;
   vector<Book> returnedBooks;
    string line;

    while (getline(cin, line) && line != "END") {
       istringstream iss(line);
       string title, by, author;
       getline(iss, title, '\"');
      getline(iss, title, '\"');
        iss >> by; 
       getline(iss, author);
        library.push_back({title, author});
    }

    std::sort(library.begin(), library.end());

    while (getline(cin, line) && line != "END") {
        istringstream iss(line);
       string command, title;
        iss >> command;

        if (command == "BORROW") {
            iss.ignore(); 
           getline(iss, title, '\"');
           getline(iss, title, '\"'); 
        } else if (command == "RETURN") {
            iss.ignore();
           getline(iss, title, '\"');
           getline(iss, title, '\"'); 
           
            auto it = find_if(library.begin(), library.end(), [&](const Book& book) {
                return book.title == title;
            });
            if (it != library.end()) {
                returnedBooks.push_back(*it); 
            }
        } else if (command == "SHELVE") {
          
          sort(returnedBooks.begin(), returnedBooks.end());

           
            for (const auto& returned : returnedBooks) {
                auto it = lower_bound(library.begin(), library.end(), returned);
                if (it == library.begin()) {
                    cout << "Put " << returned.displayTitle() << " first" << endl;
                } else {
                  cout << "Put " << returned.displayTitle() << " after " << (*(it - 1)).displayTitle() << endl;
                }
            }
           cout << "END" << endl;

           
            returnedBooks.clear();
        }
    }

    return 0;
}
