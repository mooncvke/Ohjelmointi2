#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <iostream>

using namespace std;


class Book
{
    public:
        Book(string author, string book_name);
        void print();
        void loan(Date const &today);
        void renew();
        void give_back();

    private:
        string author_;
        string book_name_;
};

#endif // BOOK_HH
