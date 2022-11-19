#include "book.hh"

Book::Book(){}

void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{

    // define values in chapter
    chapter_.id_=id;
    chapter_.fullName_=fullName;
    chapter_.length_=length;
    chapter_.chapterAddress_ = std::make_shared<Chapter>(chapter_); // points to chapter memory address
    // add chapter to database
    database_.insert( {chapter_.fullName_, chapter_ } );
}

void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{
    for ( auto subChap : database_ ) {
        if ( subChap.second.fullName_ == subchapter ) {
            for ( auto &parentChap : database_ ) {
                if( parentChap.second.fullName_ == parentChapter ) {
                    // add relation
                    subChap.second.parentChapter_ = &parentChap.second; // subchapterin parentchapteriin tallennetaan parentchapterin osoite
                    parentChap.second.subchapters_.push_back(&subChap.second); // lisätään parentchap:n subchapters vekktoriin subchap:n osoite
                }
            }
        }
    }
}

void Book::printIds(Params params) const
{
    std::cout << "Book has " << database_.size() << " chapters:" << std::endl;

    for ( auto &chapter : database_ ) {
        std::cout << chapter.second.fullName_ << " --- " << chapter.second.id_ << std::endl;
    }
}

void Book::printContents(Params params) const
{

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
