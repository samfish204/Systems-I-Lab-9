// Copyright 2020 Samuel Fisher
// lab9
// CSE278 - Section B
// Professor Vendome
// This program takes in an input file
// from the command line and parses it
// to find integers. It then takes these
// integers and converts it to hexadecimal
// and then return the little endian
// of these hexadecimal numbers
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char* argv[]) {
    // Check file input
    if (argc != 2) {
        cerr << "Specify input file" << "\n"; return 0;
    }

    // Setup any necessary stream(s)
    ifstream input(argv[1]);
    if ( !input.good() ) {
        cerr << "Error opening input stream" << "\n"; return 0;
    }

    vector<string> strVec; string output;

    // Process input
    while (getline(input, output)) {
        // Split input data
        boost::split(strVec, output, boost::is_any_of(" "));

        // Stringstream to hold the hex value
        stringstream hexVal; int dec; hexVal << strVec[3];

        // Convert data
        dec = stoi(hexVal.str()); hexVal.str("");

        // Put data into stream as hex value
        hexVal << hex << dec;

        // Check to see if hex value size is even
        if (hexVal.str().size() % 2 == 1) {
            // Clear stringstream
            hexVal.str("");
            // Put data in the stream with a leading value
            hexVal << 0 << hex << dec;
        }

        string result = "| "; string temp = hexVal.str();

        // Print out hex in little ending splitting the pairs
        // with a " | " character (e.g., | 01 | )
        for (int i = temp.size() - 1; i > 0; i -= 2) {
            result = result + temp.at(i - 1) + temp.at(i) + " | ";
        }
        cout << result << "\n";
    }
    return 0;
}
