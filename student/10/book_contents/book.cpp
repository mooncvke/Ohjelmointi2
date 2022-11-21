#include "book.hh"

Book::Book():
    database_({})
{
}

Book::~Book()
{

    // free memory
    for( auto pair : database_ ) {
        delete pair.second;
    }
}

void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{

    if ( chapterExists(id)) {
        // error
        return;
    }

    // create and add new chapter
    Chapter *new_ch = new Chapter{id, fullName, length};
    database_.insert( {new_ch->id_, new_ch} );
}

void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{
    if ( chapterExists(subchapter) &&
         chapterExists(parentChapter))
    {
        // get pointers
        Chapter *parent = database_.at(parentChapter),
                *child = database_.at(subchapter);
        // add relation
        parent->subchapters_.push_back(child);
        child->parentChapter_ = parent;
    } else {
        // error
    }
}

void Book::printIds(Params params) const
{
    std::cout << "Book has " << database_.size() << " chapters:" << std::endl;

    DataAlphabet databaseAlphabet = databaseAlphabetical();

    for ( auto &chapter : databaseAlphabet ) {
        std::cout << chapter.second->fullName_ << " --- " << chapter.second->id_ << std::endl;
    }
}

void Book::printContents(Params params) const
{
    // find main chapters
    std::vector< Chapter* > mainChapters = {};
    for ( std::pair< std::string, Chapter* > pair : database_ ) {
        // if main chapter -> parent = null
        // doesn't have upper chapter
        if ( pair.second->parentChapter_ == nullptr ) {
            mainChapters.push_back(pair.second);
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
    // check if open, actually doesn't need to do this remove
    if ( database_.at(params.at(0))->open_ == true ) {
        database_.at(params.at(0))->open_ = false;

        goThroughRecursive(database_.at(params.at(0))->subchapters_, false);

    } else { return; }
}

void Book::open(Params params) const
{
    database_.at(params.at(0))->open_ = true;
}

void Book::openAll(Params params) const
{
    for ( auto ch : database_ ) {
        database_.at(ch.first)->open_ = true;
        goThroughRecursive(ch.second->subchapters_, true);
    }
}

void Book::printParentsN(Params params) const
{
    std::string ch = params.at(0);
    int num = stoi(params.at(1));
    std::vector< std::string > parents;

    while ( num > 0 ) {
        parents.push_back(database_.at(ch)->parentChapter_->id_);
        ch = database_.at(ch)->parentChapter_->id_;
        num--;
    }

    sort(parents.begin(), parents.end());
    std::cout << params.at(0) << " has " << params.at(1) << " parent chapters:" << std::endl;
    for ( auto parent : parents ) {
        std::cout << parent << std::endl;
    }
}

void Book::printSubchaptersN(Params params) const
{
    std::string ch = params.at(0);
    int num = stoi(params.at(1));
    std::vector< std::string > children;

    int length = 0;
    length += database_.at(params.at(0))->length_;
    std::string id = "";
    id = database_.at(params.at(0))->id_;
    std::pair< int, std::string > result = {length, id};

    for ( auto subCh : database_.at(params.at(0))->subchapters_ ) {
        if ( subCh->length_ > result.first ) {
            result.first = subCh->length_;
            result.second = subCh->id_;
        }
        result = longestThroughRecursive(subCh->subchapters_, result);
    }
    std::vector<std::string> res;
    res.push_back(result.second);
    res.push_back((std::to_string(result.first)));
    printParentsN(res);
}

void Book::printSiblingChapters(Params params) const
{

    Chapter* parentCh = database_.at(params.at(0))->parentChapter_;
    std::cout << params.at(0) << " has " << parentCh->subchapters_.size() - 1
              << " sibling chapters:" << std::endl;
    // add ids to vector to print them alphabetically
    std::vector< std::string > alphabetical;
    for ( auto ch : parentCh->subchapters_ ) {
        if ( ch->id_ != params.at(0) ) {
            alphabetical.push_back(ch->id_);
        }
    }
    std::sort(alphabetical.begin(), alphabetical.end());
    for ( auto i : alphabetical ) {
        std::cout << i << std::endl;
    }
}

void Book::printTotalLength(Params params) const
{
    int length = 0;
    length += database_.at(params.at(0))->length_;

    for ( auto subCh : database_.at(params.at(0))->subchapters_ ) {
        length += subCh->length_;
        length = countThroughRecursive(subCh->subchapters_, length);
    }

    std::cout << "Total length of " << params.at(0) << " is " << length << "." << std::endl;
}

void Book::printLongestInHierarchy(Params params) const
{
    int length = 0;
    length += database_.at(params.at(0))->length_;
    std::string id = "";
    id = database_.at(params.at(0))->id_;
    std::pair< int, std::string > result = {length, id};

    for ( auto subCh : database_.at(params.at(0))->subchapters_ ) {
        if ( subCh->length_ > result.first ) {
            result.first = subCh->length_;
            result.second = subCh->id_;
        }
        result = longestThroughRecursive(subCh->subchapters_, result);
    }
    std::cout << "With the length of " << result.first << ", " << result.second
              << " is the longest in " << params.at(0) << "'s hierarchy." << std::endl;
}

void Book::printShortestInHierarchy(Params params) const
{
    int length = 0;
    length += database_.at(params.at(0))->length_;
    std::string id = "";
    id = database_.at(params.at(0))->id_;
    std::pair< int, std::string > result = {length, id};

    for ( auto subCh : database_.at(params.at(0))->subchapters_ ) {
        if ( subCh->length_ < result.first ) {
            result.first = subCh->length_;
            result.second = subCh->id_;
        }
        result = shortestThroughRecursive(subCh->subchapters_, result);
    }
    std::cout << "With the length of " << result.first << ", " << result.second
              << " is the shortest in " << params.at(0) << "'s hierarchy." << std::endl;
}

void Book::printParent(Params params) const
{

}

void Book::printSubchapters(Params params) const
{

}

Chapter *Book::findChapter(const std::string &id) const
{
    Chapter *ptr = nullptr;
    // check if id exists
    if ( chapterExists(id) ) {
        ptr = database_.at(id);
    }
    return ptr;
}

bool Book::chapterExists(const std::string &id) const
{
    return database_.find(id) != database_.end();
}

void Book::printGroup(const std::string &id, const std::string &group, const IdSet &container) const
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
    if ( !ch->open_ || ch->subchapters_.empty( )) { return; }

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
                database_.at(subchapter->id_)->open_ = open;
                goThroughRecursive(subchapter->subchapters_, open);
            }
        }
    } else { return; }
}

int Book::countThroughRecursive(std::vector<Chapter *> subCh, int length) const
{
    if ( subCh.size() > 0 ) {
        for ( auto *subchapter : subCh) {
            if ( subchapter->subchapters_.size() > 0 ) {
                length += subchapter->length_;
                countThroughRecursive(subchapter->subchapters_, length);
            }
        }
    } else { return length; }
    return length;
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

std::map<std::string, Chapter *> Book::databaseAlphabetical() const
{
    DataAlphabet databaseAlphabetical;

    for (auto &chapter : database_) {
        databaseAlphabetical.insert( {chapter.first, chapter.second} );
    }
    return databaseAlphabetical;
}

