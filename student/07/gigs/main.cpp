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

using namespace std;
// GIGS: artists, date, town, stage
using GIGS = map< string, map < string, vector < string >>>;

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
    cout << "Give name for input file: ";
    string inputFile;
    getline(cin, inputFile);

    ifstream file(inputFile);
    if ( not file ) {
        cout << "Error: File could not be read."<< endl;
        return EXIT_FAILURE;
    } else {
        string line;
        while( getline(file, line) ) {
            vector<string> result;
            string artist;
            string gigDate;
            map < string, vector< string>> gigInfo;

            result = split(line);
            artist = result.at(0);
            gigDate = result.at(1);

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

void artists( GIGS &gigs)
{
    cout << "All artists in alphabetical order:" << endl;
    for ( auto &artist : gigs) {
        cout << artist.first << endl;
    }
}

void artist( GIGS gigs, string artist)
{
    cout << "Artist " << artist << " has the following gigs in the order they are listed: " << endl;

    for ( auto &artistInfo : gigs.at(artist) ) {
        cout << "- " << artistInfo.first << " : ";
        int i = 0;
        for ( auto &gigInfo : gigs.at(artist).at(artistInfo.first)) {
            if ( i == 0) {
                cout << gigInfo;
            } else {
                cout << ", "<< gigInfo;
            }
            ++i;
        }
        cout << endl;
    }
}

void stages ( GIGS gigs)
{
    map < string, vector< string >> stages;


    // go through gigs map
    for (auto &i : gigs) {
        // go through map inside gigs map
        for (auto &j : i.second) {
            vector < string > stage;
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
    cout << "All gig places in alphabetical order:" << endl;

    for (auto &town : stages) {
        for ( auto &stage : town.second) {
            cout << town.first << ", " << stage << endl;
        }
    }

}

void stage(GIGS &gigs, std::string stage)
{
    std::vector < string > artists;
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

void addArtist(GIGS &gigs, string artist)
{
    // add artist to gigs with empty value
    map< string, vector < string >> value;
    gigs.insert({artist, value});
}

void addGig(GIGS &gigs, vector<string> input) {
    // vector: command, artist, date, town, stage

    vector < string > stage;
    map < string, vector< string>> info;

    stage.push_back(input.at(3));
    stage.push_back(input.at(4));

    gigs.at(input.at(1)).insert( {input.at(2), stage });

    std::cout << "Gig added." << std::endl;
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
        vector< string > input;
        string userInputUpper = "";
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
                cout << "Error: Invalid input." << endl;
            } else if ( gigs.find(input.at(1)) == gigs.end() ) {
                cout << "Error: Not found." << endl;
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

        } else if ( input.at(0) =="ADD_ARTIST") {
            if ( input.size() < 2 ) {
                cout << "Error: Invalid input." << endl;
            } else if (  gigs.find(input.at(1)) != gigs.end() ) {
                std::cout << "Error: Alredy exists." << std::endl;
            } else {
                addArtist(gigs, input.at(1));
            }
        } else if ( input.at(0) == "ADD_GIG") {
            if ( input.size() < 5 ) {
                std::cout << "Error: Invalid input." << std::endl;
            } else if ( gigs.find(input.at(1)) == gigs.end() ) {
                std::cout << "Error: Not found." << std::endl;
            } else if(! is_valid_date(input.at(2))) {
                std::cout << "Error: Invalid date." << std::endl;
            } else {
                addGig(gigs, input);
            }

        } else if ( input.at(0) == "CANCEL") {

        }
        else {
            std::cout << "Error: Invalid input." << std::endl;
            continue;
        }
    }

    return EXIT_SUCCESS;
}
