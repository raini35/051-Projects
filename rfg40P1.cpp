/*
 * rfg40P1.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #1
 *
 *  Due on: FEB 17, 2016
 *  Author: Rainier Go
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */

// these are all the necessary header files needed to use all of the commands
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

// these are all the constants used in the program
const double LENGTH_MIN = 5.0,
             LENGTH_MAX = 25.0,
             DEPTH_MIN = 5.0,
             MIN_MULTIPLIER = 0.58,
             MAX_MULTIPLIER = 0.80,
             WASTAGE_MULTIPLIER = 1.26,
             COST_OF_MARBLE = 92.99,
             COST_OF_GRANITE = 78.99,
             COST_OF_QUARTZ = 56.99,
             EDGING_COST = 4.99;

int main()
{
    // these are all the variables used in the program organized by data ype
    char material[256];
    
    double materialCost, length, depth, height, minHeight, maxHeight,
    costOfMaterial, costOfEdgingLength, costOfEdgingDepth,
    totalEdgingCost, totalCost, depthMax, materialRequired;
    int lengthEdges, depthEdges;
    
    string inputMaterial, line, line2, line3;
    string arrows = ">> ";
    
    cout << "Welcome to Claude's Custom Counters, Inc. Calculator\n"
         << "This application calculates cost and fabrication\n"
         << "data based on user entries.\n\n";
    
    cout << "Please enter the material code "
    << "(M - marble, G = granite, Q - quartz):\n"
    << arrows;
    cin.getline(material,256);
    
    // if/else if statement matches the respective material cost and input material to the input
        if (material[0] == 'm' || material[0] == 'M')
        {
            materialCost = COST_OF_MARBLE;
            inputMaterial = "Marble";
        }
        else if (material[0] == 'g' || material[0] == 'G')
        {
            materialCost = COST_OF_GRANITE;
            inputMaterial = "Granite";
        }
        else if (material[0] == 'q' || material[0] == 'Q')
        {
            materialCost = COST_OF_QUARTZ;
            inputMaterial = "Quartz";
        }
        else
        {
            cout << "The material selected is not a valid value\n"
                 << "The Program will exit now, Good-bye...\n";
            return 0;
        }
    
    // following statement automatically formats numbers to show decimal and 2 digits afterwards
    cout << fixed << showpoint << setprecision(2);
    
    cout << "Please enter counter top length (" << LENGTH_MIN << "' - " << LENGTH_MAX << "'): \n"
    << arrows;
    cin >> length;
    cin.ignore(500, '\n');
    
    // if else loop makes sure that data is valid and then sets depthMax to length
        if (length < LENGTH_MIN || length > LENGTH_MAX)
        {
            cout << "The length selected is not a valid value\n"
                 << "It should be between " << LENGTH_MIN << "' - " << LENGTH_MAX << "'." << endl
                 << "The Program will exit now, Good-bye...\n";
            return 0;
        }
        else
            depthMax = length;
    
    cout << "Please enter counter top depth (" << DEPTH_MIN << "' - " << depthMax << "'): \n"
    << arrows;
    cin >> depth;
    
    // if else loop makes sure that data is valid and then gets the necessary min and max height
        if (depth < DEPTH_MIN || depth > depthMax)
        {
            cout << "The depth selected is not a valid value\n"
                 << "It should be between " << DEPTH_MIN << "' - " << depthMax << "'." << endl
                 << "The Program will exit now, Good-bye...\n";
            return 0;
        }
        else
        {
            minHeight = depth * MIN_MULTIPLIER;
            maxHeight = depth * MAX_MULTIPLIER;
        }
    
    cout << "Please enter counter top height (" << minHeight << "' - " << maxHeight << "'): \n"
    << arrows;
    cin >> height;
    cin.ignore(500, '\n');
    
    // if else loop makes sure that data is valid
        if (height < minHeight || height > maxHeight)
        {
            cout << "The height selected is not a valid value\n"
                 << "It should be between " << minHeight << "' - " << maxHeight << "'." << endl
                 << "The Program will exit now, Good-bye...\n";
            return 0;
        }
    
    cout << "\nHow many length edges should be finished and polished (0 - 2)? \n"
    << arrows;
    cin >> lengthEdges;
    cin.ignore(500, '\n');
    
    // if else loop makes sure that data is valid
        if (lengthEdges < 0 || lengthEdges > 2)
        {
            cout << "The amount of edges selected is not a valid value\n"
                 << "It should be 0, 1, or 2." << endl
                 << "The Program will exit now, Good-bye...\n";
            return 0;
        }
    
    cout << "How many depth edges should be finished and polished (0 - 2)? \n"
    << arrows;
    cin >> depthEdges;
    cin.ignore(500, '\n');
    
    // if else loop makes sure that data is valid
        if (depthEdges < 0 || depthEdges > 2)
        {
            cout << "The amount of edges selected is not a valid value\n"
                 << "It should be 0, 1, or 2." << endl 
                 << "The Program will exit now, Good-bye...\n";
            return 0;
        }
    
    // the following are all the calculations. the round function rounds the material required
    materialRequired = length * height * WASTAGE_MULTIPLIER;
    costOfMaterial = round(materialRequired) * materialCost;
    costOfEdgingLength = lengthEdges * length * EDGING_COST;
    costOfEdgingDepth = depthEdges * depth * EDGING_COST;
    totalEdgingCost = costOfEdgingDepth + costOfEdgingLength;
    
    totalCost = costOfMaterial + totalEdgingCost;
    
    // the following assigns 14 and 16 spaces to line2 and line3 for formatting
    line2.assign(14, ' ');
    line3.assign(16, ' ');
    
    cout << endl << line2 << "Dimensions" << endl;
    
    /*setw() is set to 10 because the maximum digits possible for cost is 8
    and 10 makes sure that decimals will line up regardless of the inputs */
    cout << setw(10) << right << length << " feet - counter top length." << endl;
    cout << setw(10) << depth << " feet - counter top depth." << endl;
    cout << setw(10) << height << " feet - counter top height." << endl;
    cout << setw(10) << round(materialRequired) << " square feet - " << inputMaterial << " required to begin fabrication.\n" << endl;
    
    cout << line3 << "Costs" << endl;
    cout << setw(10) << right << costOfMaterial << " dollars - cost for " << inputMaterial << endl;
    cout << setw(10) << totalEdgingCost << " dollars - cost for edge finishing" << endl;
    
    line.assign(48, '-');
    cout << line << endl;
    cout << setw(10) << totalCost << " dollars - total cost" << endl;
    
    cout << endl << "Thank you for using Claude’s Custom Counters, Inc. Calculator\n\n";
    
}


