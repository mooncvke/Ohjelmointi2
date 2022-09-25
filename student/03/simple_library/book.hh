#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <iostream>
#include <string>

using namespace std;


class Book
{
    public:
        Book(string const &author, string const &book_name);
        void print();
        void loan(Date const &today);
        void renew();
        void give_back();


    private:
        string author_;
        string book_name_;
        bool available_;
        Date loan_date_;
        Date due_date_;

};

#endif // BOOK_HH
