/* COMP.CS.110 Project 3: Book contents
 * Description:
 * Program gets book's table of contents from a file and user can find out info
 * about the book with different commands. This header book.hh file contains
 * definitions for class Book and it's functions, few constants to improve
 * readability in other modules and structure for a chapter that is used on class
 * Book.
 *
 * Functions defined in public part executes commands given by user. Functions
 * in private part are used to help execute commands. Functions in private part
 * get in their parameters a vector of strings which are parameters user gave for
 * particular command.
 *
 * Program author
 * Name: Tuuli Silvennoinen
 * Student number: 150185558
 * UserID: kftusi
 * E-Mail: tuuli.silvennoinen@tuni.fi
*/

#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>


// Named constants to improve readability in other modules
const std::string EMPTY = "";
const int NO_LENGTH = -1;

// Command parameters have been collected into a vector. In this way each
// method implementing a command has the same parameters (amount and type).
// If a command has no parameters, the vector is empty.
using Params = const std::vector<std::string>&;

// Struct for a book chapter
struct Chapter
{
    std::string id_ = EMPTY;
    std::string fullName_ = EMPTY;
    int length_ = 0;
    Chapter* parentChapter_ = nullptr;
    std::vector<Chapter*> subchapters_;
    bool open_ = true;
};

using IdSet = std::set<std::string>;

// Book class, a datastucture for Chapter structs
class Book
{
public:
    // Constructor
    Book();

    // Destructor
    ~Book();

    // Adds a new Chapter to the datastructure.
    void addNewChapter(const std::string& id, const std::string& fullName,
                       int length);

    // Adds a new chapter-subchapter relation.
    void addRelation(const std::string& subchapter,
                     const std::string& parentChapter);

    // Prints all stored chapters: ID, full name and length
    void printIds(Params params) const;

    // Prints the contents page of the book. Chapters are printed in the order,
    // they are in the book, subchapters are indented appropriately.
    // Either '-' or '+' is printed before each chapter, '-' for open chapters
    // and '+' for closed one. If a chapter is open, its subchapters are
    // also listed.
    void printContents(Params params) const;

    // Closes the given chapter and its subchapters.
    void close(Params params) const;

    // Opens the given chapter.
    void open(Params params) const;

    // Opens all chapters.
    void openAll(Params params) const;

    // Prints the amount and names of parent chapters in given distance from
    // the given chapter. Parent chapters are printed in alphabethical order.
    void printParentsN(Params params) const;

    // Prints the amount and names of subchapters in given distance from
    // the given chapter. Subchapters are printed in alphabethical order.
    void printSubchaptersN(Params params) const;

    // Prints the sibling chapters of the given chapter, i.e. the chapters
    // sharing the parent chapter with the given one.
    void printSiblingChapters(Params params) const;

    // Prints the total length of the given chapter, i.e. the sum of lengths
    // of the given chapter and its subchapters.
    void printTotalLength(Params params) const;

    // Prints the longest chapter in the hierarchy of the given chapter.
    void printLongestInHierarchy(Params params) const;

    // Prints the shortest chapter in the hierarchy of the given chapter.
    void printShortestInHierarchy(Params params) const;

    // Prints the direct parent chapter of the given chapter.
    // Students will not implement this method.
    void printParent(Params params) const;

    // Prints the direct subchapters of the given chapter.
    // Students will not implement this method.
    void printSubchapters(Params params) const;

private:
    // datastructure to save chapters
    using Data = std::vector< Chapter* >;
    Data database_;

    // Returns a pointer for chapter ID. Parameters are chapter ID as string and boolean
    // value which determines if error message is printed if chapter doesn't exist.
    Chapter* findChapter(const std::string& id, bool printError = true ) const;

    // Checks if chapter exists, parameter is chapter ID. Function
    // returns true if chapter can be found from datastructure
    bool chapterExists(const std::string &id) const;

    // Prints all chapters as table of contents. Used in printContents-function.
    // Parameters are chapter pointer, index that counts chapters to print correct
    // number in front of chapter and indent that prints correct amount of
    // spaces in front of chapter name
    void printChaptersRecursive(Chapter *ch, int index, const std::string indent) const;

    // Goes through chapters and opens or closes them by changing value of open
    // variable. Used with close- and openAll-functions. Parameters are vector
    // of chapter pointers and boolean value which determines if chapter is
    // opened or closed.
    void goThroughRecursive(std::vector<Chapter*> chapters, bool open) const;

    // Goes through chapters and counts their total length. Used with
    // printTotalLength-function. Parameters are vector of chapter pointers
    // and length of chapters. Function returns total length of chapters.
    int countThroughRecursive(std::vector<Chapter*> chapters, int length) const;

    // Get parent chapters of chapter. Parameters are chapter pointer and number
    // of how many levels of parents are wanted. Function returns vector of parent's IDs.
    std::vector<std::string> getParents ( Chapter* chapter, int num ) const;

    // Print chapters. Used with printParentsN-, printSubChaptersN- and
    // printSiblingChapters-functions. Parameters are vector of chapters to be printed
    // and id of chapter to which printed chapters are related to.
    void printChapters(std::vector< std::string > &chapters, std::string &chapterId,
                       std::string param ) const;

    // Get longest/shortest chapter. Used in printLongestInHierarchy- and
    // printShortestInHierarchy-functions. Parameters are vector of chapter pointers,
    // pair of result( longest/shortest chapter at that point )
    // that contains length and ID of the chapter. Returns final result which is
    // the longest/shortest chapter and it's length and ID.
    std::pair< int, std::string > longestAndShortest(std::vector<Chapter *> subCh,
                                                     std::pair <int, std::string > result,
                                                     std::string param ) const;

    // print longest/shorterst chapter and it's length. Used in printLongestInHierarchy-
    // and printShortestInHierarchy-functions. Parameters are result that
    // is get with longestAndShortest-function, chapter that is the original chapter
    // given by user and param that is "shortest" or "longest" determineting
    // which one is wanted
    void printLongestAndShortest(std::pair< int, std::string > result,
                                 std::string chapter, std::string param ) const;
};

#endif // BOOK_HH
