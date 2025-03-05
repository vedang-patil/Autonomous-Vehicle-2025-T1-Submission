#include <iostream>
#include <fstream>
#include <string>

// Question 3: This is an extension task that requires you to decode sensor data from a CAN log file.
// CAN (Controller Area Network) is a communication standard used in automotive applications (including Redback cars)
// to allow communication between sensors and controllers.
//
// Your Task: Using the definition in the Sensors.dbc file, extract the "WheelSpeedRR" values
// from the candump.log file. Parse these values correctly and store them in an output.txt file with the following format:
// (<UNIX_TIME>): <DECODED_VALUE>
// eg:
// (1705638753.913408): 1234.5
// (1705638754.915609): 6789.0
// ...
// The above values are not real numbers; they are only there to show the expected data output format.
// You do not need to use any external libraries. Use the resources below to understand how to extract sensor data.
// Hint: Think about manual bit masking and shifting, data types required,
// what formats are used to represent values, etc.
// Resources:
// https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial
// https://www.csselectronics.com/pages/can-dbc-file-database-intro

int main() {
    std::ifstream dumpFile("candump.log");
    std::ofstream outputFile("output.txt");

    std::string unixTime, interface, idAndData;
    while (dumpFile >> unixTime >> interface >> idAndData) {
        // Discard random entries
        if (!(idAndData[0] == '7' && idAndData[1] == '0' && idAndData[2] == '5')) continue;
        // Instead of getting the id as a substring, just take the exact hex digits that corespond to the segment we are looking for,
        // which is 16 binary digits from idx 32 of the binary respresentation so that coresponds to 4 hex digits from idx 8 of the hex
        // representation. First four characters in the string are discared since they are part of the id and seperator.
        int val = std::stoi(idAndData.substr(12, 4), nullptr, 16);
        // Multiply with factor, and offset is 0
        double wheelSpeedRR = val * 0.1;
        outputFile << unixTime << ": " << wheelSpeedRR << "\n";
    }
}