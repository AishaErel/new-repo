

#include <iostream>
#include <string> // std::string
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono> 
#include <thread>

using namespace std;
using namespace std::chrono;

//Step by Step Explanation
// 1- Read in book information details from a file.
// 2-Use a struct classes to read in books, the classmust have a constructor.
// 3-Create a function that sorts the vector according to ISBN number, this function must take the vector by reference.
// 4-Open a new file of book details 
// 5-Find at which index they should be added using their ISBN number, using a linear or binary search.
// 6-Output the index along with the number of iterations required for each algorithm to find that index.


struct Book {
    Book(const int n, const string& l, const string& t)
{ 

     number = n;
     language = l;
     type = t;
    }
    int number;
    string language;
    string type;
};

bool analyze(const Book& lhs, const Book& rhs) {
    return lhs.number < rhs.number;

}
int linearSearch( const vector< Book >& newbooks, const int number, int &count)
{
    count = 0;
    for (unsigned int i = 0; i < newbooks.size(); i++){
        if ( number == newbooks[i].number) {
            count++;
            return i;
        }
    }
    count = newbooks.size();
    return -1;
}
int binarySearch( const vector< Book >& newbooks, const int number, int &count)
{
    unsigned int low = 0;
    unsigned int high = newbooks.size()-1;
    unsigned int middle;
    bool found = false;
    count = 0;

    while (low <= high) {

        middle = ( low + high) / 2;
         if (newbooks.at(middle).number > number) {
            high = middle - 1;
        }
        else if ( newbooks.at(middle).number < number) {
            low = middle + 1;
        }
        else if ( newbooks.at(middle).number == number) {
            count++;
            return middle;
        }
        count++;
    }
    return -1;
}


int main(int argc, char **argv)  { // command line arguments stands for argument count and argument vector
    
    std::vector<Book> newbooks;
    std::ifstream fileOfNew("newbooks.dat");
    std::string line; 
    int number;
    while (std::getline(fileOfNew, line)) { // read in the data
       std::stringstream data(line);
       std::string language;
       std::string type;
       data >> number >> language >> type;
       newbooks.push_back(Book(number, language, type));
            
 } 
    std::vector<Book> request;    // the list of newbooks and list of requested books are in two vector containers 
    std::ifstream fileOfReq("request.dat");
    int number2;
    while (std::getline(fileOfReq, line)) { // read in the data
       std::stringstream data(line);
       std::string language;
       std::string type;
       data >> number2 >> language >> type;
       request.push_back(Book(number2, language, type));
            
 } 

   std::sort(newbooks.begin(), newbooks.end(), analyze);
   ofstream output ("foundBook2.dat");
    int num_found = 0;
   int isbn =0;
   for (int i=0; i< request.size() ; i++) {
    isbn = request[i].number;

     char method;
    int count = 0;
    int result = 0;
    string start;
    string end;

  
    std::cout << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary: " << endl;
    cin >> method;
    if (method == 'b') { 
        count =0;

        std::chrono::high_resolution_clock::time_point start;
        start = std::chrono::high_resolution_clock::now();
        
        result = binarySearch(newbooks, isbn, count);
        if (result != -1) {
            num_found++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
        std::cout << "CPU time: " << elapsed_us << " microseconds";

    } else if (method == 'l') { 
        count =0;

        std::chrono::high_resolution_clock::time_point start;
        start = std::chrono::high_resolution_clock::now();
        
        result = binarySearch(newbooks, isbn, count);
        if (result != -1) {
            num_found++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
        std::cout << "CPU time: " << elapsed_us << " microseconds";

    } else if (method == 'r') { 
       count =0;

        std::chrono::high_resolution_clock::time_point start;
        start = std::chrono::high_resolution_clock::now();
        
        result = binarySearch(newbooks, isbn, count);
        if (result != -1) {
            num_found++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
        std::cout << "CPU time: " << elapsed_us << " microseconds";

    }
     else {
        std::cout << "Incorrect choice of method" << endl;
    }
   output << num_found<< endl;
   return 0;
}
}

