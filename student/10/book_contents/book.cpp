/* COMP.CS.110 Project 3: Book contents
 * Description:
 * Program gets book's table of contents from a file and user can find out info
 * about the book with different commands. In this book.cpp file these commands
 * are executed an they are: IDS, CONTENTS, CLOSE <ID>, OPEN <ID>, OPEN_ALL,
 * PARENTS <ID> <N>, SUBCHAPTERS <ID> <N>, SIBLINGS <ID>, LENGTH <ID>, LONGEST <ID>,
 * SHORTEST <ID>. More specific descriptions of all the commands are found from
 * book.hh file in functions that executes them.

* Program author
* Name: Tuuli Silvennoinen
* Student number: 150185558
* UserID: kftusi
* E-Mail: tuuli.silvennoinen@tuni.fi
*/

#include "book.hh"

Book::Book():
    database_({})
{
}

Book::~Book()
{
    // free memory
    for( auto chapter : database_ ) {
        delete chapter;
    }
}

void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{
    // check if chapter with given id already exists -> print error message
    if ( chapterExists(id)) {
        std::cout << "Error: Already exists." << std::endl;
    }
    // create and add a new chapter to the database_
    std::vector<Chapter*> subchapters;
    Chapter* parentChapter = nullptr;
    Chapter *new_ch = new Chapter{id, fullName, length, parentChapter, subchapters};
    database_.push_back( new_ch );
}

void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{
    // get pointers
    Chapter *parent = findChapter(parentChapter, false ),
            *child = findChapter(subchapter, false );
    // error checking
    if ( parent == nullptr ) {
        return;
    } if ( child == nullptr ) {
        return;
    }
    else {
        // add relation
        parent->subchapters_.push_back(child);
        child->parentChapter_ = parent;
    }
}

void Book::printIds(Params) const
{
    std::vector< std::pair<std::string, std::string >> names;
    std::cout << "Book has " << database_.size() << " chapters:" << std::endl;

    // go through database_ and add every chapter's name and id to the names vector
    for ( auto chapter : database_ ) {
        names.push_back( {chapter->fullName_, chapter->id_} );
    }
    // sort vector to alphabetical order and go through it to print chapters
    sort(names.begin(), names.end());
    for ( auto &name : names ) {
        std::cout << name.first << " --- " << name.second << std::endl;
    }
}

void Book::printContents(Params) const
{
    // find main chapters
    std::vector< Chapter* > mainChapters = {};
    for ( auto chapter : database_ ) {
        // if chapter is a main chapter it doesn't have a parent chapter.
        // if chapter doesn't have parent chapter add it to mainChapters-vector
        if ( chapter->parentChapter_ == nullptr ) {
            mainChapters.push_back(chapter);
        }
    }
    // print table of contents with printChaptersRecursive-function
    int index = 1;
    for ( Chapter *ptr : mainChapters ) {
        printChaptersRecursive(ptr, index, " ");
        index++;
    }
}

void Book::close(Params params) const
{
    // if chapter exists, close chapter and close all of its subchapters with
    // goThroughRecursive-function by changing open_value to false
    auto chapter = findChapter( params.at(0) );
    if ( chapter != nullptr ) {
        chapter->open_ = false;
        goThroughRecursive(chapter->subchapters_, false);
    }
}

void Book::open(Params params) const
{
    // if chapter exists open it by changing open_-value to true
    auto chapter = findChapter( params.at(0) );
    if ( chapter != nullptr ) {
        chapter->open_ = true;
    }
}

void Book::openAll(Params ) const
{
    // go through database_ and open every chapter by changing open_-value to true
    for ( auto chapter : database_ ) {
        chapter->open_ = true;
        goThroughRecursive(chapter->subchapters_, true);
    }
}

void Book::printParentsN(Params params) const
{
    auto chapter = findChapter( params.at(0) );
    int num = stoi(params.at(1));
    std::vector< std::string > parents;

    if ( chapter != nullptr ) {
        // if user gives value for level that is less than 1 print error-message
        if ( num < 1 ) {
            std::cout << "Error. Level can't be less than 1." << std::endl;
        }
        // get parent chapters with getParents-function and print parentchapters
        // with printChapters-function
        else {
            parents = getParents( chapter, num );
            printChapters( parents, chapter->id_, "parent");
        }
    }
}

void Book::printSubchaptersN(Params params) const
{
    auto chapter = findChapter( params.at(0) );
    int num = stoi(params.at(1));
    std::vector< std::string > children;
    auto ogCh = chapter;

    if ( chapter != nullptr ) {
        // if user gives value for level that is less than 1 print error-message
        if ( num < 1 ) {
            std::cout << "Error. Level can't be less than 1." << std::endl;
        } else {
            while ( num > 0 ) {
                auto ogChapter = chapter;
                // check if chapter has subchapters
                if ( chapter->subchapters_.size() > 0 ) {
                    for ( auto subCh : chapter->subchapters_ ) {
                            children.push_back(subCh->id_);
                        // if subCh has subchapter, subCh will be chapter
                        // in next round of the loop
                        if ( subCh->subchapters_.size() > 0 ) {
                            chapter = subCh;
                        }
                    }
                    // if chapter is same as it was beginning of this round of the loop
                    // meaning none of chapter's subchapters had any subchapters
                    // and loop breaks
                    if ( chapter == ogChapter ) break;
                    num--;
                } else {
                    break;
                }
            }
            // print subchapters using printChapters-function
            printChapters( children, ogCh->id_, "sub");
        }
    }
}

void Book::printSiblingChapters(Params params) const
{
    auto chapter = findChapter(params.at(0));
    std::vector< std::string > siblings;
    if ( chapter != nullptr ) {
        // if chapter has a parent chapter it has sibling chapters
        if ( chapter->parentChapter_ != nullptr ) {
            // go through chapter's parent chapter's subchapters (=sibling chapters)
            for ( auto sibling : chapter->parentChapter_->subchapters_ ) {
                // chapter itself is not added to the vector
                if ( sibling != chapter ) {
                    siblings.push_back(sibling->id_);
                }
            }
        }
        // print siblings using printChapters-functions
        printChapters(siblings, chapter->id_, "sibling");
    }
}

void Book::printTotalLength(Params params) const
{
    auto chapter = findChapter(params.at(0));
    if ( chapter != nullptr ) {
        // get total length of chapter and its subchapters with
        // countThroughRecursive-function
        int length = chapter->length_;
        length = countThroughRecursive(chapter->subchapters_, length);

        std::cout << "Total length of " << params.at(0) << " is "
                  << length << "." << std::endl;
    }
}

void Book::printLongestInHierarchy(Params params) const
{
    auto chapter = findChapter(params.at(0));
    if ( chapter != nullptr ) {
        // first longest chapter is the first chapter in hierarchy (chapter given by user)
        // find longest chapter using longestAndShortestThroughRecursive-function
        std::pair< int, std::string > result = {chapter->length_, chapter->id_};
        result = longestAndShortest(chapter->subchapters_, result, "longest");
        // print with printLongestAndShortest-function
        printLongestAndShortest(result, chapter->id_, "longest");
    }
}

void Book::printShortestInHierarchy(Params params) const
{
    auto chapter = findChapter(params.at(0));
    if ( chapter != nullptr ) {
        // first shortest chapter is the first chapter in hierarchy (chapter given by user)
        // find shortest chapter using longestThroughRecursive-function
        std::pair< int, std::string > result = {chapter->length_, chapter->id_};
        result = longestAndShortest(chapter->subchapters_, result, "shortest");
        // print with printLongestAndShortest-function
        printLongestAndShortest(result, chapter->id_, "shortest");
    }
}

void Book::printParent(Params) const {}

void Book::printSubchapters(Params) const {}

Chapter *Book::findChapter(const std::string &id, bool printError ) const
{
    Chapter *ptr = nullptr;
    for ( auto chapter : database_ ) {
        // check if id exists
        if ( chapter->id_ == id ) {
            ptr = chapter;
        }
    }
    // print error-message if printError is true and chapter wasn't found
    if ( printError == true ) {
        if ( ptr == nullptr ) {
            std::cout << "Error: Not found: " << id << std::endl;
        }
    }
    // return pointer to the chapter, if chapter isn't found pointer is nullptr
    return ptr;
}

bool Book::chapterExists(const std::string &id) const
{
    for ( auto chapter : database_ ) {
        // if chapter exists, return true. if it doesn't exist return false
        if ( chapter->id_ == id ) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void Book::printChaptersRecursive(Chapter *ch, int index, const std::string indent) const
{
    // if chapter is open, sign is '-' and if it's not open sign is '+'
    char sign = ch->open_ ? '-' : '+';

    std::cout << sign << indent << index << ". " << ch->fullName_
              << " ( " << ch->length_ << " )" << std::endl;

    // if chapter has no subchapters
    if ( !ch->open_ || ch->subchapters_.empty()) { return; }

    // iterate through subchapters and print them using this same function
    index = 1;
    for ( Chapter *subch : ch->subchapters_ ) {
        printChaptersRecursive(subch, index, indent + "  ");
        index++;
    }
}

void Book::goThroughRecursive(std::vector<Chapter*> subChapter, bool open ) const
{
    if ( subChapter.size() > 0 ) {
        // go through subChapter's subchapters and change their open_-value to
        // the value given in open-parameter
        for ( auto subchapter : subChapter ) {
            subchapter->open_ = open;
            if ( subchapter->subchapters_.size() > 0 ) {
                goThroughRecursive(subchapter->subchapters_, open);
            }
        }
    } else { return; }
}

int Book::countThroughRecursive(std::vector<Chapter *> subCh, int length) const
{
    if ( subCh.size() > 0 ) {
        // go through subchapters and add them to the length
        for ( auto subchapter : subCh) {
            length += subchapter->length_;
            length = countThroughRecursive(subchapter->subchapters_, length);
        }
    }
    // return total length
    return length;
}

std::vector<std::string> Book::getParents(Chapter *chapter, int num) const
{
    std::vector< std::string > parents;
    while ( num > 0 ) {
        // if chapter has parentchapter add parentchapter to parents-vector and give
        // chapter-variable value of parentChapter. if chapter doesn't have parent
        // chapter, loop will stop
        if ( chapter->parentChapter_ != nullptr ) {
                parents.push_back(chapter->parentChapter_->id_);
                chapter = chapter->parentChapter_;
                num--;
        } else {
            break;
        }
    }
    return parents;
}

void Book::printChapters(std::vector<std::string> &chapters,
                         std::string &chapterId, std::string param ) const
{
    // if chapters-vector's size is smaller than 1, it doesn't have any chapters
    if ( chapters.size() < 1 ) {
        // if to be printed is amount of subchapters, there's no space
        // between param and "chapter" other two possibilities with this
        // function ( parent chapters and sibling chapters ) are written with space
        if ( param == "sub" ) {
            std::cout << chapterId << " has no " << param << "chapters." << std::endl;
        } else {
            std::cout << chapterId << " has no " << param << " chapters." << std::endl;
        }
    } else {
        // vector is sorted to get chapters in alphabetical order. print chapters
        // with loop
        sort(chapters.begin(), chapters.end());
        // subchapter is written without space
        if ( param == "sub" ) {
            std::cout << chapterId << " has " << chapters.size() << " "
                      << param << "chapters:" << std::endl;
            for ( auto &ch : chapters ) {
                std::cout << ch << std::endl;
            }
        } else {
            std::cout << chapterId << " has " << chapters.size() << " "
                      << param << " chapters:" << std::endl;
            for ( auto &ch : chapters ) {
                std::cout << ch << std::endl;
            }
        }
    }
}



std::pair< int, std::string > Book::longestAndShortest(std::vector<Chapter *> subCh,
                                                       std::pair <int, std::string> result,
                                                       std::string param) const
{
    if ( subCh.size() > 0 ) {
        // if param is "longest", is meant to find out the longest chapter
        if ( param == "longest" ) {
            // go through subchapters and if chapter is longer than length(=result.first)
            // its length becames the new length
            for ( auto subchapter : subCh) {
                if ( subchapter->length_ > result.first ) {
                    result.first = subchapter->length_;
                    result.second = subchapter->id_;
                }
                result = longestAndShortest(subchapter->subchapters_,
                                            result, param);
            }
        }
        // if param is "shortest", is meant to find out the shortest chapter
        if ( param == "shortest" ) {
            // go through subchapters and if chapter is shorter than length(=result.first)
            // its length becames the new length
            for ( auto subchapter : subCh) {
                if ( subchapter->length_ < result.first ) {
                    result.first = subchapter->length_;
                    result.second = subchapter->id_;
                }
                if ( subchapter->subchapters_.size() > 0 ) {
                    result = longestAndShortest(subchapter->subchapters_,
                                                result, param);
                }
            }
        }
    }
    // return result that contains the length and ID of the longest/shortest chapter
    return result;
}

void Book::printLongestAndShortest(std::pair<int, std::string> result,
                                   std::string chapterId, std::string param) const
{
    // longest/shortest chapter is same chapter that was given by user
    if ( result.second == chapterId ) {
        std::cout << "With the length of " << result.first << ", "
                  << result.second << " is the " << param << " chapter in their"
                  << " hierarchy." << std::endl;
    } else {
        std::cout << "With the length of " << result.first << ", "
                  << result.second << " is the " << param << " chapter in "
                  << chapterId << "'s hierarchy." << std::endl;
    }
}
