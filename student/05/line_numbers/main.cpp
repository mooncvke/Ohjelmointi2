#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file;
    string output_file;

    cout << "Input file: ";
    cin >> input_file;
    cout << "Output file: ";
    cin >> output_file;

    string lines[8];
    ifstream file(input_file);
    if ( not file ) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return 1;
    } else {
        ofstream oFile(output_file);
        int i = 0;
        string line;
        while( getline(file, line) ) {
            ++i;

            oFile << i << " " << line << endl;
        }
        file.close();
        oFile.close();
    }


    return 0;
}
