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
        return;
    }
    // create and add a new chapter
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

    for ( auto chapter : database_ ) {
        names.push_back({chapter->fullName_, chapter->id_});
    }
    sort(names.begin(), names.end());
    for ( auto name : names ) {
        auto chapter = findChapter(name.second, false);
        if ( chapter != nullptr ) {
            std::cout << chapter->fullName_ << " --- " << chapter->id_ << std::endl;
        }
    }
}

void Book::printContents(Params) const
{
    // find main chapters
    std::vector< Chapter* > mainChapters = {};
    for ( auto chapter : database_ ) {
        // if main chapter -> parent = null
        // doesn't have upper chapter
        if ( chapter->parentChapter_ == nullptr ) {
            mainChapters.push_back(chapter);
        }
    }
    int index = 1;
    for ( Chapter *ptr : mainChapters ) {
        printChaptersRecursive(ptr, index, " ");
        index++;
    }
}

void Book::close(Params params) const
{
    auto chapter = findChapter( params.at(0) );

    if ( chapter != nullptr ) {
        chapter->open_ = false;
        goThroughRecursive(chapter->subchapters_, false);
    }
}

void Book::open(Params params) const
{
    auto chapter = findChapter( params.at(0) );

    if ( chapter != nullptr ) {
        chapter->open_ = true;
    }
}

void Book::openAll(Params ) const
{
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
        if ( num < 1 ) {
            std::cout << "Error. Level can't be less than 1." << std::endl;
        } else {
            parents = returnParents( chapter, num );
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
        if ( num < 1 ) {
            std::cout << "Error. Level can't be less than 1." << std::endl;
        } else {
            while ( num > 0 ) {
                // has subchapters
                if ( chapter->subchapters_.size() > 0 ) {
                    for ( auto subCh : chapter->subchapters_ ) {
                        children.push_back(subCh->id_);
                        if ( subCh->subchapters_.size() > 0 ) {
                            chapter = subCh;
                        }
                    }
                    if ( chapter == ogCh ) break;
                    num--;
                } else {
                    break;
                }

            }
            // pritn children
            printChapters( children, ogCh->id_, "sub");
        }
    }
}

void Book::printSiblingChapters(Params params) const
{
    auto chapter = findChapter( params.at(0) );
    std::vector< std::string > siblings;

    if ( chapter != nullptr ) {
        for ( auto sibling : chapter->parentChapter_->subchapters_ ) {
            if ( sibling != chapter ) {
                siblings.push_back(sibling->id_);
            }
        }
        printChapters( siblings, chapter->id_, "sibling");
    }
}

void Book::printTotalLength(Params params) const
{
    auto chapter = findChapter(params.at(0));
    if ( chapter != nullptr ) {
        int length = chapter->length_;

        for ( auto subCh : chapter->subchapters_ ) {
            length += subCh->length_;
            length = countThroughRecursive(subCh->subchapters_, length);
        }
        std::cout << "Total length of " << params.at(0) << " is " << length << "." << std::endl;
    }
}

void Book::printLongestInHierarchy(Params params) const
{
    auto chapter = findChapter(params.at(0));
    if ( chapter != nullptr ) {
        int length = 0;
        length += chapter->length_;
        std::string id = "";
        id = chapter->id_;
        std::pair< int, std::string > result = {length, id};

        for ( auto subCh : chapter->subchapters_ ) {
            if ( subCh->length_ > result.first ) {
                result.first = subCh->length_;
                result.second = subCh->id_;
            }
            result = longestThroughRecursive(subCh->subchapters_, result);
        }
        std::cout << "With the length of " << result.first << ", " << result.second
                  << " is the longest in " << params.at(0) << "'s hierarchy." << std::endl;
    }
}

void Book::printShortestInHierarchy(Params params) const
{
    auto chapter = findChapter(params.at(0));
    if ( chapter != nullptr ) {
        int length = 0;
        length += chapter->length_;
        std::string id = "";
        id = chapter->id_;
        std::pair< int, std::string > result = {length, id};

        for ( auto subCh : chapter->subchapters_ ) {
            if ( subCh->length_ < result.first ) {
                result.first = subCh->length_;
                result.second = subCh->id_;
            }
            result = shortestThroughRecursive(subCh->subchapters_, result);
        }
        std::cout << "With the length of " << result.first << ", " << result.second
                  << " is the shortest in " << params.at(0) << "'s hierarchy." << std::endl;
    }
}

void Book::printParent(Params) const
{

}

void Book::printSubchapters(Params) const
{

}

Chapter *Book::findChapter(const std::string &id, bool printError ) const
{
    Chapter *ptr = nullptr;
    for ( auto chapter : database_ ) {
        // check if id exists
        if ( chapter->id_ == id ) {
            ptr = chapter;
        }
    }
    if ( printError == true ) {
        if ( ptr == nullptr ) {
            std::cout << "Error: Not found: " << id << std::endl;
        }
    }
    return ptr;
}

bool Book::chapterExists(const std::string &id) const
{
    for ( auto chapter : database_ ) {
        if ( chapter->id_ == id ) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void Book::printGroup(const std::string&, const std::string&, const IdSet&) const
{

}

IdSet Book::vectorToIdSet(const std::vector<Chapter *> &container) const
{
    IdSet ids = {};
    for ( Chapter *ptr : container ) {
        ids.insert(ptr->id_);
    }
    return ids;
}

void Book::printChaptersRecursive(Chapter *ch, int index, const std::string indent) const
{
    char sign = ch->open_ ? '-' : '+';

    std::cout << sign << indent << index << ". " << ch->fullName_
              << " ( " << ch->length_ << " )" << std::endl;

    // has no subchapters
    if ( !ch->open_ || ch->subchapters_.empty()) { return; }

    // iterate through subchapters
    index = 1;
    for ( Chapter *subch : ch->subchapters_ ) {
        printChaptersRecursive(subch, index, indent + "  ");
        index++;
    }
}

void Book::goThroughRecursive(std::vector<Chapter*> subCh, bool open ) const
{

    if ( subCh.size() > 0 ) {
        for ( auto *subchapter : subCh) {
            if ( subchapter->subchapters_.size() > 0 ) {
                subchapter->open_ = open;
                goThroughRecursive(subchapter->subchapters_, open);
            }
        }
    } else { return; }
}

int Book::countThroughRecursive(std::vector<Chapter *> subCh, int length) const
{
    if ( subCh.size() > 0 ) {
        for ( auto subchapter : subCh) {
            length += subchapter->length_;
            countThroughRecursive(subchapter->subchapters_, length);
        }
    }

    return length;
}

std::vector<std::string> Book::returnParents(Chapter *chapter, int num) const
{
    std::vector< std::string > parents;
    while ( num > 0 ) {
        // has parentchapter
        if ( chapter->parentChapter_ != nullptr ) {
                // add parent to parents vector
                parents.push_back(chapter->parentChapter_->id_);
                chapter = chapter->parentChapter_;
                num--;
            } else {
                break;
        }
    }
    return parents;
}

void Book::printChapters(std::vector<std::string> chapters, std::string chapter, std::string param ) const
{
    sort(chapters.begin(), chapters.end());
    if ( chapters.size() < 1 ) {
        if ( param == "sub" ) {
            std::cout << chapter << " has no " << param << "chapters." << std::endl;
            return;
        } else {
            std::cout << chapter << " has no " << param << " chapters." << std::endl;
            return;
        }
    } else {
        if ( param == "sub" ) {
            std::cout << chapter << " has " << chapters.size() << " " << param << "chapters:" << std::endl;
            for ( auto ch : chapters ) {
                std::cout << ch << std::endl;
            }
        } else {
            std::cout << chapter << " has " << chapters.size() << " " << param << " chapters:" << std::endl;
            for ( auto ch : chapters ) {
                std::cout << ch << std::endl;
            }
        }

    }
}

Chapter* Book::returnSubChapter(Chapter *chapter) const
{
    for ( auto subChapter : chapter->subchapters_ ) {
        chapter = subChapter;
        if ( subChapter->subchapters_.size() > 0 ) {
            returnSubChapter(chapter);
        }
    }
    return chapter;
}

std::pair< int, std::string > Book::longestThroughRecursive(std::vector<Chapter *> subCh, std::pair <int, std::string > result) const
{
    if ( subCh.size() > 0 ) {
        for ( auto *subchapter : subCh) {
            if ( subchapter->length_ > result.first ) {

                result.first = subchapter->length_;
                result.second = subchapter->id_;
            }
            if ( subchapter->subchapters_.size() > 0 ) {
                longestThroughRecursive(subchapter->subchapters_, result);
            }
        }
    } else { return result; }
    return result;
}

std::pair<int, std::string> Book::shortestThroughRecursive(std::vector<Chapter *> subCh, std::pair<int, std::string> result) const
{
    if ( subCh.size() > 0 ) {
        for ( auto *subchapter : subCh) {
            if ( subchapter->length_ < result.first ) {

                result.first = subchapter->length_;
                result.second = subchapter->id_;
            }
            if ( subchapter->subchapters_.size() > 0 ) {
                longestThroughRecursive(subchapter->subchapters_, result);
            }
        }
    } else { return result; }
    return result;
}


