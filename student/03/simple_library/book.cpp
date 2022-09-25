#include "book.hh"

Book::Book(string const &author, string const &book_name):
    author_(author),
    book_name_(book_name),
    available_(true),
    loan_date_(Date()),
    due_date_(Date())
{

}

void Book::print()
{
    cout << author_ << " : " << book_name_ << endl;
    if (available_ ) {
        cout << " - available" << endl;
    } else {
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        due_date_.print();

    }
}

void Book::loan(Date const &today)
{
    if (!available_) {
        cout << "Already loaned: cannot be loaned" << endl;
    } else {
        available_ = false;
        loan_date_ = today;
        due_date_ = today;
        due_date_.advance(28);
    }

}
void Book::renew()
{
    if (available_) {
        cout << "Not loaned: cannot be renewed" << endl;
    } else {
        due_date_.advance(28);
    }

}

void Book::give_back()
{
    if (available_ ) {
        cout << "Not loaned: cannot be given back" << endl;
    } else {
        available_ = true;
    }

}


