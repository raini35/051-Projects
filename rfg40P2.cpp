/*
 *  rfg40P2.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #2
 *
 *  Due on: MAR 03, 2016
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
#include <fstream>
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

 const int EDGES_MIN = 0,
           EDGES_MAX = 2;

const string E1= "\n\tERROR: Order Date Improper Format",
    E2a= "\n\tERROR: Delivery Date Improper Format",
    E2b= "\n\tERROR: Delivery Date is equal to Order Date",
    E2c= "\n\tERROR: Delivery Date is too far from Order Date",
    E3= "\n\tERROR: Invalid Stone Code",
    E4= "\n\tERROR: Invalid length",
    E5= "\n\tERROR: Invalid depth",
    E6= "\n\tERROR: Invalid height",
    E7= "\n\tERROR: Invalid amount of length edges",
    E8 = "\n\tERROR: Invalid amount of depth edges";

 int main()
 {
     //the following are the variables of the program
     string columnHeadings = "";
     string orderDate = "";
     string fileNameAndPath = "";
     char material;
     char delimiter = '/';
     double materialCost = 0.0, length, depth, height, minHeight = 0.0, maxHeight = 0.0,
        costOfMaterial= 0.0, costOfEdgingLength= 0.0, costOfEdgingDepth= 0.0,
        totalEdgingCost= 0.0, totalCost= 0.0, depthMax = 0.0, materialRequired= 0.0;
     double mTotalSqFeet= 0.0, gTotalSqFeet= 0.0, qTotalSqFeet= 0.0,
        mTotalCost= 0.0, gTotalCost= 0.0, qTotalCost= 0.0;
     int mCount=0, gCount=0, qCount=0;
     int lengthEdges=0, depthEdges=0, recordsWithErrors=0, recordsWithoutErrors=0, totalRecords=0;
     int orderDateYear, orderDateMonth, orderDateDay, deliveryDateYear, deliveryDateMonth,
     deliveryDateDay;
     int errorFree = 1;
     string line1, line2;
     string errors = "";
     string customerInfo, fipsStateCode, orderNumber;
     ifstream inFileStream;
     
     //this gets the file name from the user
     cout << "Welcome. What is path and name of the file you want to read?\n";
     cout << "Make sure to right the appropriate path and file.\n";
     getline(cin, fileNameAndPath);
     
     //this opens the file
     inFileStream.open(fileNameAndPath.c_str());
 
     //if the file does not open then it will output the error message
     if ( !inFileStream )
     {
         cout << "\nERROR: Data file is not valid.\n";
         cout << "The program cannot continue.\n\n";
     }
     //if the file opens the programe executes the following
     else
     {
         cout << fileNameAndPath << " was successfully opened for reading!" << endl;

         cout << showpoint << fixed << setprecision(2);
         //The following are the headers for the columns
         cout << endl << setw(10) << "Order" << setw(12) << "Delivery"
         << setw(3) << "S" << setw(7) << "      "<< setw(7)
         << "      " << setw(7) << "      " << setw(3) << "L"
         << setw(3) << "D" << setw(10) << "Sq." << setw(11)
         << "Total" << endl;
         cout << setw(10) << "Date" << setw(12) << "Date"
         << setw(3) << "C" << setw(7) << "Len." << setw(7)
         << "Dep." << setw(7) << "Hei." << setw(3) << "E"
         << setw(3)<< "E"<< setw(10)<< "Ft." << setw(11)
         << "Cost" << endl;
         
         line1.assign(80, '-');
         cout << line1 << endl;
         
         //This reads all of the columns so that it doesn't get read
         //in the while loop
         getline(inFileStream, columnHeadings);
         
         while(inFileStream >> orderDateYear >> delimiter >> orderDateMonth
               >> delimiter >> orderDateDay >> deliveryDateYear >> delimiter
               >> deliveryDateMonth >> delimiter >>  deliveryDateDay
               >> material >> length >> depth >> height >> lengthEdges
               >> depthEdges >> orderNumber >> fipsStateCode
               && getline(inFileStream, customerInfo))

             
         {
             //this resets all the numbers that change during one
             //iteration of the while loop
             errorFree = 1;
             errors = "";
             depthMax = 0;
             minHeight = 0;
             maxHeight = 0;
             
             //The following if statements validates all of the data
             if ((orderDateYear < 1000) || (orderDateYear > 9999) ||
                 (orderDateMonth < 1) || ( orderDateMonth > 12) ||
                 (orderDateDay <1) || (orderDateDay >31))
             {
                 errors = errors + E1;
                 errorFree = 0;
             }

             
             if ((deliveryDateYear < 1000) || (deliveryDateYear > 9999) ||
                 (deliveryDateMonth < 1) || ( deliveryDateMonth > 12) ||
                 (deliveryDateDay <1) || (deliveryDateDay >31))
             {
                 errors = errors + E2a;
                 errorFree = 0;
             }
             
             if ((orderDateDay == deliveryDateDay) && (orderDateYear == deliveryDateYear)
                 && (orderDateMonth == deliveryDateMonth))
             {
                 errors = errors + E2b;
                 errorFree = 0;
             }
             
             if (deliveryDateYear > orderDateYear)
             {
                 deliveryDateMonth += (deliveryDateYear - orderDateYear) * 12;
             }
        
             if ((deliveryDateMonth - orderDateMonth) >4 )
             {
                 errors = errors + E2c;
                 errorFree = 0;
             }
             
             if ((material != 'M') && (material != 'm') && (material != 'G')&&
                 (material != 'g') && (material != 'Q')&& (material != 'q'))
             {
                 errors = errors + E3;
                 errorFree = 0;
             }

        
             if (length < LENGTH_MIN || length > LENGTH_MAX)
             {
                 errors = errors + E4;
                 errorFree = 0;
             }
             else
                 depthMax = length;
             
        
             if (depth < DEPTH_MIN || depth > depthMax)
             {
                 errors = errors + E5;
                 errorFree = 0;
             }
             else
             {
                 minHeight = depth * MIN_MULTIPLIER;
                 maxHeight = depth * MAX_MULTIPLIER;
             }
             
             if (height < minHeight || height > maxHeight)
             {
                 errors = errors + E6; 
                 errorFree = 0;
             }
             
            
             if (lengthEdges < EDGES_MIN || lengthEdges > EDGES_MAX)
             {
                 errors = errors + E7;
                 errorFree = 0;
             }
             
             
             if (depthEdges < EDGES_MIN || depthEdges > EDGES_MAX)
             {
                 errors = errors + E8;
                 errorFree = 0;
             }
            
             
             //If there is an error then the following if statement will be outputted,
             //otherwise it will continue
             if(errorFree == 0)
             {
    
                 materialRequired = 32;
                 totalCost = 32;
                 cout << setw(4)<< orderDateYear << delimiter <<setw(2)<< orderDateMonth << delimiter
                 <<  setw(2) << orderDateDay << "  "<< deliveryDateYear << delimiter <<
                 deliveryDateMonth << delimiter<<  setw(2) << deliveryDateDay
                 << setw(3) << material << setw(7) << length << setw(7)
                 << depth << setw(7) << height << setw(3) << lengthEdges
                 << setw(3)<< depthEdges<< setw(10)<< static_cast<char>(materialRequired) << setw(11)
                 << static_cast<char>(totalCost) << errors << "\n\n";
                 
                recordsWithErrors = recordsWithErrors + 1;
 
             }
             // if there are no mistakes the following code will execute
             else
             {
                 if (material == 'M'|| material == 'm')
                 {
                     materialCost = COST_OF_MARBLE;
                 }
                 else if (material == 'G'|| material == 'g')
                 {
                     materialCost = COST_OF_GRANITE;
                 }
                 else if (material == 'Q'|| material == 'q')
                 {
                     materialCost = COST_OF_QUARTZ;
                 }
          
                //These are the necessay calculations
                 materialRequired = length * height * WASTAGE_MULTIPLIER;
                 costOfMaterial = materialCost * ceil(materialRequired);
                 costOfEdgingLength = lengthEdges * length * EDGING_COST;
                 costOfEdgingDepth = depthEdges * depth * EDGING_COST;
                 totalEdgingCost = costOfEdgingDepth + costOfEdgingLength;
                 
                 totalCost = costOfMaterial + totalEdgingCost;
                 
                 //This sorts out the individual orders by material
                 if (material == 'M' || material == 'm')
                 {
                     mTotalSqFeet = mTotalSqFeet + ceil(materialRequired);
                     mTotalCost = mTotalCost + totalCost;
                     mCount = mCount + 1;
                     
                 }
                 
                 else if (material == 'G'|| material == 'g')
                 {
                     gTotalSqFeet = gTotalSqFeet + ceil(materialRequired);
                     gTotalCost = gTotalCost + totalCost;
                     gCount = gCount + 1;
                     
                 }
                
                 else if (material == 'Q'|| material == 'q')
                 {
                     qTotalSqFeet = qTotalSqFeet + ceil(materialRequired);
                     qTotalCost = qTotalCost + totalCost;
                     qCount = qCount + 1;
                }
                 //This keeps the count of records without errors
                 recordsWithoutErrors = recordsWithoutErrors + 1;
                 
                 //Outputs all the information
                 cout << setw(4)<< orderDateYear << delimiter << setw(2)<< orderDateMonth
                 << delimiter << setw(2)<< orderDateDay << "  "<< deliveryDateYear << delimiter
                 << setw(2) << deliveryDateMonth << delimiter << setw(2)<< deliveryDateDay
                 << setw(3) << material << setw(7) << length << setw(7)
                 << depth << setw(7) << height << setw(3) << lengthEdges
                 << setw(3)<< depthEdges<< setw(10)<< ceil(materialRequired) << setw(11)
                 << totalCost << endl;

             }
               //This keeps the count of all the records without
             totalRecords = totalRecords + 1;
             
         }
     
         
         //The following is the summary table that is outputted
         //after while loop is executed
         cout << "\nCounts: Total Records = " << totalRecords
         << "      Records with Errors = " << recordsWithErrors
         << "      Records without Errors = " << recordsWithoutErrors << endl;
         
         line2.assign(50, '-');
         
         cout << endl << setw(9) << "Stone" << setw(8) << "Count"
         << setw(15) << "Square Feet" << setw(15)
         << "Cost" << endl;
         cout << line2 << endl;
         
         cout << setw(9) << "Marble" << setw(8) << mCount
         << setw(15) << mTotalSqFeet << setw(15)
         << mTotalCost << endl;
         
         cout << setw(9) << "Granite" << setw(8) << gCount
         << setw(15) << gTotalSqFeet << setw(15)
         << gTotalCost << endl;
         
         cout << setw(9) << "Quartz" << setw(8) << qCount
         << setw(15) << qTotalSqFeet << setw(15)
         << qTotalCost << endl;
         cout << line2 << "\n\n";
     }
     




     return 0;
     
 }
