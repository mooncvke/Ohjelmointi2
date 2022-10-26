/* COMP.CS.110 Project 2: GIGS calender
 * Description:
 * Program is samll calender to keep track of different
 * artists and their gigs. First program asks user for input file
 * from where data is read. Input file needs to contain lines and in each
 * line contains artist's name, date, town and stage seperated by semicolons.
 *
 * After data has been read user can give different commands which are:
 * QUIT, ARTISTS, ARTIST, STAGES, STAGE, ADD_ARTIST, ADD_GIG, CANCEL.
 * Each command needs to be followed with enpugh parameters otherwise
 * program prints error message and asks for new input. Commands can be
 * given in upper- or lowercase.
 *
 * QUIT: requires only the command. Program terminates with return value EXIT_SUCCESS.
 * ARTISTS: requires only command. Prints all the artists saved to the calender.
 * ARTIST: requires artist's name as parameter. Prints all the gigs of given artist in chronological order.
 * STAGES: requires only the command. Prints all the stages saved to the calender in alphabetical order.
 * STAGE: requires name of the stage as parameter. Prints artists that have gigs at the given stage.
 * ADD-ARTIST: requires artist's name as parameter. Adds new artist to the calender.
 * ADD_GIG: requires artist's name, gig's date, town and stage as parameters. Adds gig to the given artist.
 * CANCEL: requires artist's name and date as parameters. Cancels given artist's gigs after given date.
 *
 * Program author
 * Name: Tuuli Silvennoinen
 * Student number: 150185558
 * UserID: kftusi
 * E-Mail: tuuli.silvennoinen@tuni.fi
*/

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>


// define data-structure used:
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

// check if input is valid. used when reading data-file and with add_gig-command
bool is_valid_input(GIGS gigs, std::vector< std::string > input)
{

    std::string exists = "doesntExist";
    // check if a gig already is booked to the venue on given date
    for ( auto &artist : gigs) {
        for ( auto &date : artist.second) {
            // if venue is already booked
            if ( input.at(3) == date.second.at(1))
            {
                // check if it's also booked on the same day -> there is already gig at same venue at same date
                // -> gig can not be booked, change exists-variable to "alreadyExists"
                if ( date.first == input.at(1)) {
                    exists = "alreadyExists";
                    continue;
                }
            }
        }
    }

    // check if valid date, if not return false
    if (! is_valid_date(input.at(1)) ) {
        std::cout << "Error: Invalid date." << std::endl;
        return false;
    }
    // cheeck if artist exists in gigs
    if ( gigs.find(input.at(0)) != gigs.end() ) {
        // check if artist already has gig at this date -> if does, print error message and return false
        if ( gigs.at(input.at(0)).find(input.at(1)) != gigs.at(input.at(0)).end() )
            {
                std::cout << "Error: Already exists." << std::endl;
                return false;
            }
    }
    // if gig already exists at the same venue and same date, print error message and return false
    if (exists == "alreadyExists") {
        std::cout << "Error: Already exists." << std::endl;
        return false;
    }

    // if no errors return true
    return true;
}

// get data from file and add it to the gigs data-structure
int get_input(GIGS &gigs) {
    // get name of the file from user
    std::cout << "Give a name for input file: ";
    std::string inputFile;
    getline(std::cin, inputFile);

    std::ifstream file(inputFile);
    // file can not be read -> program quits
    if ( not file ) {
        std::cout << "Error: File could not be read."<< std::endl;
        return EXIT_FAILURE;
    }
    // file can be read
    else {
        // read file one line by one line
        std::string line;
        while( getline(file, line) ) {
            // define variables used
            std::vector<std::string> result;
            std::string artist;
            std::string gigDate;
            std::map < std::string, std::vector< std::string>> gigInfo;

            // split line using split-function
            result = split(line);
            artist = result.at(0);
            gigDate = result.at(1);

            // error checking ( check if correct amount of parameters and if parameters not empty)
            // -> if errors, quit program
            if (result.size() != 4 || result.at(0) == "" || result.at(1) == "" || result.at(2) == "" || result.at(3) == ""){
                std::cout << "Error: Invalid format in file." << std::endl;
                return EXIT_FAILURE;
            }
            // check if parameters of line are valid usind is_valiid_input-function
            if ( is_valid_input(gigs, result) == false) {
                return EXIT_FAILURE;
            }
            // remove first and second element from result-vector
            result.erase(result.begin());
            result.erase(result.begin());

            // add to giginfo-map gig info (date, town, venue)
            gigInfo.insert({gigDate, result});

            // can't find the artist from the gigs
            if ( gigs.find(artist) == gigs.end()){
                // create a new artist to the gigs-map
                gigs.insert({artist, gigInfo});
            } else {
                // did find the artist -> add new gig date(and other gig info) to the artist
                gigs.at(artist).insert({gigDate, result});
            }
        }
        // close file
        file.close();
    }
    return EXIT_SUCCESS;
}

// print all artists
void artists( GIGS gigs)
{
    std::cout << "All artists in alphabetical order:" << std::endl;
    for ( auto &artist : gigs) {
        std::cout << artist.first << std::endl;
    }
}

// print given artist's gigs
void artist( GIGS gigs, std::string artist)
{
    std::cout << "Artist " << artist << " has the following gigs in the order they are listed: " << std::endl;

    for ( auto &artistInfo : gigs.at(artist) ) {
        std::cout << "- " << artistInfo.first << " : ";
        int i = 0;
        for ( auto &gigInfo : gigs.at(artist).at(artistInfo.first)) {
            // when it's first element of gig info, do not print comma before string
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

// print all the stages
void stages ( GIGS gigs)
{
    // define map where stages are temporarily saved ( map< town, vector< venue >> )
    // when using map every stage is printed only once
    std::map < std::string, std::vector< std::string >> allStages;

    // go through gigs map
    for (auto &artist : gigs) {
        // go through map inside gigs map (containing gig info)
        for (auto &date : artist.second) {
            // define vector containing venues of one town and vector from gigs-map
            // that contains town and venues in that town
            std::vector < std::string > venues;
            std::vector < std::string > stage = date.second;
            // if town is not in allStages-map
            if ( allStages.find(date.second.at(0)) == allStages.end()) {
                // add venue to the venues vector
                venues.push_back(stage.at(1));
                // add to allStages-map pair: key is town, value is venues-vector
                allStages.insert({stage.at(0), venues});
            }
            // town is in the allStages-map
            else {
                // get already existing venues from allStages-map
                venues = allStages.at(stage.at(0));
                // if venue is not in venus-vector already
                if ( find(venues.begin(), venues.end(), stage.at(1)) == venues.end()) {
                    // add venue to the venues-vector and update the allStages-map
                    venues.push_back(stage.at(1));
                    allStages.at(date.second.at(0)) = venues;
                }
            }
        }
    }

    std::cout << "All gig places in alphabetical order:" << std::endl;

    // print all the stages from the allStages-map
    for (auto &town : allStages) {
        for ( auto &stage : town.second) {
            std::cout << town.first << ", " << stage << std::endl;
        }
    }

}

// print artists on one stage
void stage(GIGS gigs, std::string stage)
{
    // define vector containing artists performing on given stage
    std::vector < std::string > artists;
    // go through gigs-map
    for (auto &artist : gigs) {
        // go through map inside gigs-map
        for (auto &date : artist.second) {
            // if venue from the gigs-map is same as the
            // given venue -> add artist to the artists-vector
            if ( date.second.at(1) == stage) {
                artists.push_back(artist.first);
            }
        }
    }

    // print all the artists performing on the given stage
    std::cout << "Stage " << stage << " has gigs of the following artists:" << std::endl;
    for ( auto &artist : artists) {
        std::cout << "- " << artist << std::endl;
    }
}

// add new artist to the gigs-map
void addArtist(GIGS &gigs, std::string artist)
{
    // add artist to gigs-map with empty value, artist
    // doesn't have any gigs at this point thereforevalue is empty
    std::map< std::string, std::vector < std::string >> value;
    gigs.insert({artist, value});

    std::cout << "Artist added." << std::endl;
}

// add a new gig to gigs-map for given artist
void addGig(GIGS &gigs, std::vector<std::string> input) {
    // define vector containing venue info and map containing info abput the gig(key:artist, value: vector)
    std::vector < std::string > stage;
    std::map < std::string, std::vector< std::string>> info;

    // add tow and venue to the stage-vector
    stage.push_back(input.at(2));
    stage.push_back(input.at(3));

    // add to the gigs-map at the artist new gig with key: date, value: stage-vector
    gigs.at(input.at(0)).insert( {input.at(1), stage });

    std::cout << "Gig added." << std::endl;
}

// cancel given artist's gigs after given date
void cancel(GIGS &gigs, std::vector< std::string > input)
{
    // define string variable to track if correct date and copy of gigs
    std::string correctDate = "notTheDate";
    GIGS gigsCopy = gigs;

    // go through gigsCopy-map. if gone through gigs-map program would crash
    // because in loop from gigs is erased elements, therefore is needed to go through copy of the gigs
    for ( auto &date : gigsCopy.at(input.at(0))) {
        // if date from the map is bigger as given date
        if ( date.first > input.at(1)) {
            correctDate = "isTheDate";
        }
        // when date from the map is bigger than given -> remove date from gigs-map
        if ( correctDate == "isTheDate") {
            gigs.at(input.at(0)).erase(date.first);
        }
    }
    std::cout << "Artist's gigs after the given date cancelled." << std::endl;

}

int main()
{
    // define data-structure
    GIGS gigs;
    int returnValue;
    // get input from file with get_input-function
    returnValue = get_input(gigs);

    // if get_input-function returns EXIT_FAILURE, program quits
    if( returnValue == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    // user interface
    bool val = true;
    while (val) {
        std::string userInput = "";
        std::cout << "gigs> ";
        getline(std::cin, userInput);

        // split user input to vector with split-function
        std::vector< std::string > input;
        std::string userInputUpper = "";
        input = split(userInput, ' ' );

        // change command to uppercase
        for ( char letter : input.at(0)) {
            letter = toupper(letter);
            userInputUpper += letter;
        }
        // erase command from input vector
        input.erase(input.begin());

        // quit program
        if ( userInputUpper == "QUIT") {
            val = false;
        }
        // print all artists using artists-function
        else if ( userInputUpper == "ARTISTS") {
            artists(gigs);
        }
        // print gigs of one artist
        else if ( userInputUpper == "ARTIST") {
            // check if input have enough parameters
            if ( input.size() < 1 ) {
                std::cout << "Error: Invalid input." << std::endl;
            }
            // check if artist is in the gigs-map
            else if ( gigs.find(input.at(0)) == gigs.end() ) {
                std::cout << "Error: Not found." << std::endl;
            } else {
                artist(gigs, input.at(0));
            }
        }
        // print all the stages using stages-function
        else if ( userInputUpper == "STAGES") {
            stages(gigs);
        }
        // print gigs of one stage using stage-function
        else if ( userInputUpper == "STAGE") {
            // check if input has enough parameters
            if ( input.size() < 1 ) {
                std::cout << "Error: Invalid input." << std::endl;
                continue;
            }
            // check if stage exists
            std::string check = "notFound";
            for( auto &artist : gigs ) {
                for ( auto &date : artist.second) {
                    if ( input.at(0) == date.second.at(1)) {
                        check = "found";
                    }
                }
            }
            // if stage does not exist, print error message
            if ( check == "notFound" ) {
                std::cout << "Error: Not found." << std::endl;
            } else {
                stage(gigs, input.at(0));
            }
        }
        // add artist using add_artist function
        else if ( userInputUpper =="ADD_ARTIST") {
            // check if input has enough parameters
            if ( input.size() < 1 ) {
                std::cout << "Error: Invalid input." << std::endl;
            }
            // check if artist already exists
            else if (  gigs.find(input.at(0)) != gigs.end() ) {
                std::cout << "Error: Already exists." << std::endl;
            } else {
                addArtist(gigs, input.at(0));
            }
        }
        // add new gig using add_gig-function
        else if ( userInputUpper == "ADD_GIG") {
            // check if input has enough parameters
            if ( input.size() < 4 ) {
                std::cout << "Error: Invalid input." << std::endl;
            }
            // check if artist exists
            else if ( gigs.find(input.at(0)) == gigs.end() ) {
                std::cout << "Error: Not found." << std::endl;
            }
            // check if input parameters are valid using is_valid_input-function
            else if ( is_valid_input(gigs, input) == false) {
                continue;
            } else {
                addGig(gigs, input);
            }
        }
        // cancel artist's gigs after given date
        else if ( userInputUpper == "CANCEL") {
            // check if input has enough parameters
            if ( input.size() < 2) {
                std::cout << "Error: Invalid input." << std::endl;
                continue;
            }
            // check if artist exists
            else if ( gigs.find(input.at(0)) == gigs.end() ) {
                std::cout << "Error: Not found." << std::endl;
                continue;
            }
            // check if valid date with is_valid_date-function
            else if ( ! is_valid_date(input.at(1))) {
                std::cout << "Error: Invalid date." << std::endl;
                continue;
            }
            // check if there is gigs after given date
            std::string check = "isNotGigs";
            for ( auto &date : gigs.at(input.at(0))) {
                if ( date.first > input.at(1)) {
                    check = "isGigs";
                    continue;
                }
            }

            if ( check == "isNotGigs" ) {
                std::cout << "Error: No gigs after the given date." << std::endl;
                continue;
            } else {
                cancel(gigs, input);
            }

        }
        // if input is invalid
        else {
            std::cout << "Error: Invalid input." << std::endl;
            continue;
        }
    }

    return EXIT_SUCCESS;
}
