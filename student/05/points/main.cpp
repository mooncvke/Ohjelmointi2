#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string inputFile;
    cout << "Input file: ";
    cin >> inputFile;

    map< string, int > points;

    ifstream file(inputFile);
    if ( not file ) {
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        while ( getline(file, line))
        {
            if (line.length() < 1) {
                continue;
            } else {
                string name;
                string personsPoints;
                int point;

                string::size_type index = 0;
                index = line.find(':');

                name = line.substr(0, index);
                personsPoints = line.substr(index + 1);

                point = stoi(personsPoints);

                if ( points.find(name) != points.end()) {
                    points.at(name) = points.at(name) + point;
                } else {
                    points.insert( {name, point} );
                }
            }
        }
        file.close();

        cout << "Final scores: " << endl;
        for (auto &person : points) {
            cout << person.first << ": " << person.second << endl;
        }
        return EXIT_SUCCESS;
    }
}
