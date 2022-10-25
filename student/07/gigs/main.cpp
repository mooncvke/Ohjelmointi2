/* COMP.CS.110 Project 2: GIGS
 * ===========================
 * EXAMPLE SOLUTION
 * ===========================
 *
 *  Acts as a simple gig calendar with n commands:
 * ARTISTS - Prints all known artist names
 * ARTIST <artist name> - Prints single artist's gigs
 * STAGES - Prints all known stage names and their locations
 * STAGE <stage name> - Prints all artists having a gig at the given stage
 * ADD_ARTIST <artist name> - Adds a new artist
 * ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 * an artist with the given date, town, and stage (the artist can't already
 * have a gig on the same date and there can't be other gigs at the same stage
 * at the same time)
 * CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 *
 *  The data file's lines should be in format
 * artist_name;date;town_name;stage_name.
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>


// GIGS: map<artists, map< date, vector< town, stage >>>
using GIGS = std::map< std::string, std::map < std::string, std::vector < std::string >>>;

// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim = ';')
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
                        (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
        (day <= month_sizes.at(stoi(month) - 1) or
        (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_input(GIGS &gigs){
    std::cout << "Give name for a input file: ";
    std::string inputFile;
    getline(std::cin, inputFile);

    std::ifstream file(inputFile);
    if ( not file ) {
        std::cout << "Error: File could not be read."<< std::endl;
        return EXIT_FAILURE;
    } else {
        std::string line;
        while( getline(file, line) ) {
            std::vector<std::string> result;
            std::string artist;
            std::string gigDate;
            std::map < std::string, std::vector< std::string>> gigInfo;

            result = split(line);
            artist = result.at(0);
            gigDate = result.at(1);

            // error checking
            if (result.size() != 4){
                std::cout << "Error invalid format in file." << std::endl;
                return EXIT_FAILURE;
            } else if (result.at(0) == "" || result.at(1) == "" || result.at(2) == "" || result.at(3) == "") {
                std::cout << "Error invalid format in file." << std::endl;
                return EXIT_FAILURE;
            }


            // remove first and second alkio from vector
            result.erase(result.begin());
            result.erase(result.begin());

            gigInfo.insert({gigDate, result});

            // can't find the artist from the gigs
            if ( gigs.find(artist) == gigs.end()){
                // create a new
                gigs.insert({artist, gigInfo});
            } else {
                // did find the artist -> add new gig date to the artist
                gigs.at(artist).insert({gigDate, result});
            }
        }
        file.close();
    }
    return EXIT_SUCCESS;
}

void artists( GIGS gigs)
{
    std::cout << "All artists in alphabetical order:" << std::endl;
    for ( auto &artist : gigs) {
        std::cout << artist.first << std::endl;
    }
}

void artist( GIGS gigs, std::string artist)
{
    std::cout << "Artist " << artist << " has the following gigs in the order they are listed: " << std::endl;

    for ( auto &artistInfo : gigs.at(artist) ) {
        std::cout << "- " << artistInfo.first << " : ";
        int i = 0;
        for ( auto &gigInfo : gigs.at(artist).at(artistInfo.first)) {
            if ( i == 0) {
                std::cout << gigInfo;
            } else {
                std::cout << ", "<< gigInfo;
            }
            ++i;
        }
        std::cout << std::endl;
    }
}

void stages ( GIGS gigs)
{
    std::map < std::string, std::vector< std::string >> stages;


    // go through gigs map
    for (auto &i : gigs) {
        // go through map inside gigs map
        for (auto &j : i.second) {
            std::vector < std::string > stage;
            // town is not in map
            if ( stages.find(j.second.at(0)) == stages.end()) {
                stage.push_back(j.second.at(1));
                stages.insert({j.second.at(0), stage});
            } else {
                // town is in the map
                stage = stages.at(j.second.at(0));
                // if stage ot in vector
                if ( find(stage.begin(), stage.end(), j.second.at(1)) == stage.end()) {
                    stage.push_back(j.second.at(1));
                    // update the map
                    stages.at(j.second.at(0)) = stage;
                }
            }
        }
    }
    std::cout << "All gig places in alphabetical order:" << std::endl;

    for (auto &town : stages) {
        for ( auto &stage : town.second) {
            std::cout << town.first << ", " << stage << std::endl;
        }
    }

}

void stage(GIGS gigs, std::string stage)
{
    std::vector < std::string > artists;
    // go through gigs map
    for (auto &artist : gigs) {
        // go through map inside gigs map
        for (auto &date : artist.second) {

            // town is not in map
            if ( date.second.at(1) == stage) {
                artists.push_back(artist.first);
            }
        }
    }

    std::cout << "Stage " << stage << " has gigs of the following artists:" << std::endl;
    for ( auto &artist : artists) {
        std::cout << "- " << artist << std::endl;
    }
}

void addArtist(GIGS &gigs, std::string artist)
{
    // add artist to gigs with empty value
    std::map< std::string, std::vector < std::string >> value;
    gigs.insert({artist, value});
}

void addGig(GIGS &gigs, std::vector<std::string> input) {
    // vector: command, artist, date, town, stage

    std::vector < std::string > stage;
    std::map < std::string, std::vector< std::string>> info;

    stage.push_back(input.at(3));
    stage.push_back(input.at(4));

    gigs.at(input.at(1)).insert( {input.at(2), stage });

    std::cout << "Gig added." << std::endl;
}

void cancel(GIGS &gigs, std::vector< std::string > input)
{
    std::string correctDate = "notTheDate";
    GIGS gigsCopy = gigs;

    for ( auto &date : gigsCopy.at(input.at(1))) {
        if ( date.first >= input.at(2)) {
            correctDate = "isTheDate";
        }
        if ( correctDate == "isTheDate") {
            gigs.at(input.at(1)).erase(date.first);
        }
    }
    std::cout << "Artist's gigs after the given date cancelled." << std::endl;

}

int main()
{
    GIGS gigs;
    int returnValue;
    returnValue = get_input(gigs);

    if( returnValue == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    // user interface
    bool val = true;
    while (val) {
        std::string userInput = "";
        std::cout << "gigs> ";
        getline(std::cin, userInput);

        // use split function to split userInput into vector
        std::vector< std::string > input;
        std::string userInputUpper = "";
        input = split(userInput, ' ' );

        for ( char letter : input.at(0)) {
            letter = toupper(letter);
            userInputUpper += letter;
        }

        input.at(0) = userInputUpper;

        // quit program
        if ( input.at(0) == "QUIT") {
            val = false;
        }
        // print all artists
        else if ( input.at(0) == "ARTISTS") {
            artists(gigs);
        }
        // print gigs of one artist
        // first check if input has enough parameters
        else if ( input.at(0) == "ARTIST") {
            if ( input.size() < 2 ) {
                std::cout << "Error: Invalid input." << std::endl;
            } else if ( gigs.find(input.at(1)) == gigs.end() ) {
                std::cout << "Error: Not found." << std::endl;
            } else {
                artist(gigs, input.at(1));
            }

        }
        else if ( input.at(0) == "STAGES") {
            stages(gigs);
        }
        else if ( input.at(0) == "STAGE") {
            // check if stage exists
            std::string check = "notFound";
            for( auto &i : gigs ) {
                for ( auto &j : i.second) {
                    if ( input.at(1) == j.second.at(1)) {
                        check = "found";
                    }
                }
            }
            if ( input.size() < 2 ) {
                std::cout << "Error: Invalid input." << std::endl;
            } else if ( check == "notFound" ) {
                std::cout << "Error: Not found." << std::endl;
            } else {
                stage(gigs, input.at(1));
            }
        }
        else if ( input.at(0) =="ADD_ARTIST") {
            if ( input.size() < 2 ) {
                std::cout << "Error: Invalid input." << std::endl;
            } else if (  gigs.find(input.at(1)) != gigs.end() ) {
                std::cout << "Error: Alredy exists." << std::endl;
            } else {
                addArtist(gigs, input.at(1));
            }
        }
        else if ( input.at(0) == "ADD_GIG") {

            std::string exists = "doesntExist";
            for ( auto &artist : gigs) {
                for ( auto &date : artist.second) {
                    if ( input.at(4) == date.second.at(1)) {
                        if ( artist.first == input.at(2)) {
                            exists = "alreadyExists";
                        }
                    }
                }
            }

            if ( input.size() < 5 ) {
                std::cout << "Error: Invalid input." << std::endl;
            } else if ( gigs.find(input.at(1)) == gigs.end() ) {
                std::cout << "Error: Not found." << std::endl;
            } else if(is_valid_date(input.at(2)) == false) {
                std::cout << "Error: Invalid date." << std::endl;
            } else if ( gigs.at(input.at(1)).find(input.at(2)) == gigs.at(input.at(1)).end() ) // date alredy taken
            {
                std::cout << "Error: Already exists." << std::endl;
            } else if (exists == "alreadyExists") {
                std::cout << "Error: Already exists." << std::endl;
            } else {
                addGig(gigs, input);
            }

        } else if ( input.at(0) == "CANCEL") {
            std::string check = "isNotGigs";
            for ( auto &date : gigs.at(input.at(1))) {
                if ( date.first >= input.at(2)) {
                    check = "isGigs";
                }
            }

            if ( input.size() < 3) {
                std::cout << "Error: Invalid input." << std::endl;
            } else if ( check == "isNotGigs" ) {
                std::cout << "Error: No gigs after the given date." << std::endl;
            }
            else {
                cancel(gigs, input);
            }

        }
        else {
            std::cout << "Error: Invalid input." << std::endl;
            continue;
        }
    }

    return EXIT_SUCCESS;
}
