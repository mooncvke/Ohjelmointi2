#include "book.hh"

Book::Book(){}

void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{
    // define chapter
    Chapter chapter {};
    // define values in chapter
    chapter.id_=id;
    chapter.fullName_=fullName;
    chapter.length_=length;
    chapter.chapterAddress_ = std::make_shared<Chapter>(chapter); // points to chapter memory address
    std::cout<<chapter.id_<<std::endl;
}

void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{

}

void Book::printIds(Params params) const
{

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
