#include <utility>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <tuple>
#include <list>

using namespace std;

class Generate {
private:
    double min;
    double max;
    string file;
    int element;

public:
    double Points(double min, double max) {         // Generate random points!
        double listOfPoints = (double)rand() / RAND_MAX;
        return min + listOfPoints * (max - min);
    }

    int GeneratePoints() {          // Save points in text file!
        ofstream myFile;
        myFile.open(file, ios::out);
        for (int i = 0; i < 100;) {
            if (myFile.is_open() && myFile.good()) {
                myFile << Points(min, max) << " " << Points(min, max) << endl;
                cout << Points(min, max) << " " << Points(min, max) << endl;
                i++;
            }
            else {
                cout << "File is not open!" << endl;
                return 0;
            }
        }
        myFile.close();
    }

    vector<double> ReadPoints() {       // WON'T READ
        ifstream myFile;
        myFile.open(file, ifstream::in);
        vector<double> PointList;
        int length = myFile.tellg();
        char* buffer = new char[length];
        cout << "Reading " << length << " characters..." << endl;
        myFile.read(buffer, length);
        if (myFile.is_open() and myFile.good()) {
            cout << "All characters read successfully.";
            for (int j = 0; j < length;) {
                PointList.push_back(*buffer);
                j++;
            }
        }
        else {
            cout << "Error: Only " << myFile.gcount() << " could be read";
        }
        myFile.close();
        return PointList;
    }

    void ReadPoints2() {        // WORKS, BUT NEEDS IMPROVEMENTS!
        ifstream myFile(file);
        istream_iterator<double> start(myFile), end;
        vector<double> numbers(start, end);
        cout << "Read " << numbers.size() << " numbers" << endl;
        cout << "numbers read in:\n";
        copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, "\n"));
    }

    vector<string> ReadPoints3(bool debug) {            // SUPI DUPI!
        ifstream myFile(file);
        if (myFile.is_open() and myFile.good()) {
            vector<string> numbers_x[100];              // List of string elements with length of 100
            vector<string> numbers_y[100];              // List of string elements with length of 100
            vector<string> pointPair;
            string x_value, y_value;
            string line;

            while (getline(myFile, line)) {
                stringstream stream(line);              // Starting file stream
                getline(stream, x_value, ' ');          // Get X value of line
                getline(stream, y_value, ' ');          // Get Y value of line
                numbers_x->push_back(x_value + ' ');    // Adding X value to vector<string>
                numbers_y->push_back(y_value + ' ');    // Adding Y value to vector<string>
            }
            if (debug) {
                cout << "File opened successfully!" << endl;
                cout << "X-Values: " << endl;
                for (vector<string>::const_iterator x = numbers_x->begin(); x != numbers_x->end(); x++) {
                    cout << *x << ' ';  // One x Coordinate from list
                }
                cout << "\nY-Values: " << endl;
                for (vector<string>::const_iterator y = numbers_y->begin(); y != numbers_y->end(); y++) {
                    cout << *y << ' ';  // One y Coordinate from list
                }
                float length_x = numbers_x->size();     // Getting size of vector<string> containing x values
                float length_y = numbers_y->size();     // Getting size of vector<string> containing y values
                cout << "\n\n" << "Amount of X-Coordinates: " << length_x << endl;
                cout << "Amount of Y-Coordinates: " << length_y << endl;
            }

            pointPair.push_back(numbers_x->at(element));
            pointPair.push_back(numbers_y->at(element));

            cout << "\nPoints are: " << endl;
            for (int i = 0; i < pointPair.size(); i++) {
                if (i == 0) {
                    cout << "X: " << pointPair.at(i) << " ";
                }
                else {
                    cout << "Y: " << pointPair.at(i) << " ";
                }
            }
            myFile.close();
            return pointPair;
        }
        else {
            cout << "Failed to open file!" << endl;
        }
    }

    void displayPlot() {

    }

    Generate(double aMin, double aMax, string aFile, int aElement) {
        min = aMin; // Minimum for Point generation
        max = aMax; // Maximum for Point generation
        file = aFile;
        element = aElement;
    }
};

class DivideAndConquer {
private:
    int point_x;
    int point_y;
    string allPoints;
    double min = 0.001;
    double max = 2000.0;
    string file = ("points.txt");
    int element = 0;

public:
    vector<double> getMostMinsAndMaxs() {
        double mostLeft;        // Double value of most left (smallest X value)
        double mostRight;       // Double value of most right (greatest X value)
        double mostHigh;        // Double value of highest (greatest Y value)
        double mostDown;        // Double value of most down (smallest Y value)
        vector<double> allX;    // Vector to save all Points X-Values in
        vector<double> allY;    // Vector to save all Points Y-Values in
        bool debug = false;     // Get less output from ReadPoints3 method!

        for (element = 0; element < 100; element++) {                // Iterate through method and get each x and y value of list
            Generate gen(min, max, file, element);                   // Instantiate Generate class
            vector<string> point_string = gen.ReadPoints3(debug);    // Get X and Y Value from method
            vector<double> point_double(200);                        // Declaring vector of doubles with max 200 values
            transform(point_string.begin(), point_string.end(), point_double.begin(), [](const string& val) {
                return stod(val);   // Converts strings of "point_string" vector to doubles of "point_double" vector
                });
            cout << "\nChecking if " << point_double[0] << " is the most left X Coordinate..." << endl;
            allX.push_back(point_double.at(0));
            allY.push_back(point_double.at(1));
        }

        mostLeft = *min_element(allX.begin(), allX.end());
        mostRight = *max_element(allX.begin(), allX.end());
        mostHigh = *max_element(allY.begin(), allY.end());
        mostDown = *min_element(allY.begin(), allY.end());

        vector<double> mostValues(4);
        mostValues.push_back(mostLeft);
        mostValues.push_back(mostRight);
        mostValues.push_back(mostHigh);
        mostValues.push_back(mostDown);

        cout << "\nSize of all X and Y values: " << allX.size() + allY.size() << endl;

        for (vector<double>::const_iterator mostValue = mostValues.begin(); mostValue != mostValues.end(); mostValue++) {
            /*if (*mostValue == 0) {
                cout << "Most left: " << *mostValue << "\n";
            } else if (*mostValue == 1) {
                cout << "Most right: " << *mostValue << "\n";
            } else if (*mostValue == 2) {
                cout << "Most high: " << *mostValue << "\n";
            } else if (*mostValue == 3) {
                cout << "Most bottom: " << *mostValue << "\n";
            }*/
            //cout << *mostValue << endl;
        }

        return mostValues;
    }

    DivideAndConquer(string aPoints, int aPoint_x, int aPoint_y) {
        allPoints = aPoints;
        point_x = aPoint_x;
        point_y = aPoint_y;
    }

};

int main() {
    /*double min = 0.001;
    double max = 2000.0;
    string file = ("points.txt");
    int element = 0;
    Generate gen(min, max, file, element);*/

    string allPoints;
    int x = 1;
    int y = 2;

    DivideAndConquer div(allPoints, x, y);
    for (vector<double>::const_iterator mostValue = div.getMostMinsAndMaxs().begin(); mostValue != div.getMostMinsAndMaxs().end(); mostValue++) {
        cout << *mostValue << endl;
    }

    //cout << "\nMost left X-Value: " << div.getMostMinsAndMaxs();

    return 0;
}