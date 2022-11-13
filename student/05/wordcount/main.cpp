#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    string inputFile = "";
    cout << "Input file: ";
    getline(cin, inputFile);

    map< string, set< int >> words;

    ifstream file(inputFile);
    if ( not file ) {
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        int row = 1;

        while(getline(file, line)) {

            line += ' ';

            int i = 0;
            int prev_i = 0;

            for ( char c : line ) {
                set< int > rows;
                string word = "";

                if ( c == ' ') {
                    word = line.substr(prev_i, i - prev_i);
                    prev_i = i + 1;

                    if( words.find(word) != words.end() ) {
                        rows = words.at(word);
                        rows.insert(row);
                        words.at(word) = rows;
                    } else {
                        rows.insert(row);
                        words.insert( {word, rows} );
                    }

                }
            ++i;
            }
            ++row;
        }
        file.close();
        for( auto &word : words) {
            cout << word.first << " " << word.second.size() << ": ";
            int i = 0;
            for ( auto num : word.second) {
                if ( i == 0 ) {
                    cout << num;
                } else {
                    cout << ", " << num;
                }
                ++i;
            }
            cout << endl;

         }

    }


}
