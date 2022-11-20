#include "book.hh"

Book::Book():
    database_({})
{

}

Book::~Book(){

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

    std::map< std::string, Chapter > databaseAlphabetical;

    for (auto &chapter : database_) {
        databaseAlphabetical.insert( {chapter.first, chapter.second} );
    }

    for ( auto &chapter : databaseAlphabetical ) {
        std::cout << chapter.second.fullName_ << " --- " << chapter.second.id_ << std::endl;
    }
}

void Book::printLoop(int indent, int num, Chapter chapter, std::vector<Chapter*> subchapters) const
{
    for ( auto &subChapter : subchapters ) {
        if ( chapter.open_ ) { // chapter open
            std::cout << std::string(indent, ' ') << "- " << num << " " << chapter.fullName_ << " ( " << chapter.length_ << " )" << std::endl;
            if ( subChapter->subchapters_.size() > 0 ) {
                num = 1;
                ++indent;
                printLoop(indent, num, *subChapter, subChapter->subchapters_);
            } else {
                ++num;
                continue;
            }
        } if  ( !chapter.open_ ) { // chapter closed
            std::cout << "+ " << num << chapter.fullName_ << " ( " << chapter.length_ << " )" << std::endl;
            ++num;
            continue;
        }
        --indent;
    }
}

void Book::printContents(Params params) const
{
    int indent = 0;
    int num = 1;

    for ( auto &chapter : database_ ) {
            printLoop(indent, num, chapter.second, chapter.second.subchapters_);
    }


}

void Book::close(Params params) const
{

}

void Book::open(Params params) const
{

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
