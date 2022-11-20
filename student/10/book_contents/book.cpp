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


    std::map< std::string, Chapter* > databaseAlphabetical;

    for (auto &chapter : database_) {
        databaseAlphabetical.insert( {chapter.first, chapter.second} );
    }

    for ( auto &chapter : databaseAlphabetical ) {
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

        goThroughRecursive(database_.at(params.at(0))->subchapters_);

    } else { return; }
}

void Book::open(Params params) const
{
    database_.at(params.at(0))->open_ = true;
}

void Book::openAll(Params params) const
{

}

void Book::printParentsN(Params params) const
{

}

void Book::printSubchaptersN(Params params) const
{

}

void Book::printSiblingChapters(Params params) const
{

}

void Book::printTotalLength(Params params) const
{

}

void Book::printLongestInHierarchy(Params params) const
{

}

void Book::printShortestInHierarchy(Params params) const
{

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

void Book::goThroughRecursive(std::vector<Chapter*> subCh ) const
{
    if ( subCh.size() > 0 ) {
        for ( auto *subchapter : subCh) {
            if ( subchapter->subchapters_.size() > 0 ) {
                database_.at(subchapter->id_)->open_ = false;
                goThroughRecursive(subchapter->subchapters_);
            }
        }
    } else { return; }
}

