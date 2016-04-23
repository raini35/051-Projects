/*
 * rfg40P3.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #3
 *
 *  Due on: MAR 31, 2016
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

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

/***********************************************************************************************
 
 The following lines are the function prototypes of the functions needed in the program.
 
***********************************************************************************************/

char displayMenu();

void uploadFile (string fName, bool &loadSuccess, vector<char> &sCode, vector<double> &len, vector<double> &dep, vector<double> &hei, vector<int> &lenF, vector<int> &depF, vector<string> &oNum, vector<string> &reg);

void allDetails(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

void orderDetails(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

void summaryByStone(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

void summaryByRegion(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

bool clearAllVectors(vector<char> &sCode, vector<double> &len, vector<double> &dep, vector<double> &hei, vector<int> &lenF, vector<int> &depF, vector<string> &oNum, vector<string> &reg);


/***********************************************************************************************
 
 The constants used for the calculations.
 
 ***********************************************************************************************/

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


/***********************************************************************************************
 
 The outputs displayed when the data has an error.
 
 ***********************************************************************************************/
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


int main(int argc, const char * argv[]) {
    char reply;
    string fileNameAndPath;
    string fName;
    bool loadSuccess, allClear;
    vector<char> sCode;
    vector<double> len;
    vector<double> dep;
    vector<double> hei;
    vector<int> lenF;
    vector<int> depF;
    vector<string> oNum;
    vector<string> reg;
    
    cout << "Welcome to Claude's Custom Counters, Inc. Calculator\n";
    cout << "This application calculates cost and fabrication\n";
    cout << "data based on sales data input files.";
    
    do
    {
        reply = displayMenu();
        
        
        switch(reply) {
            case 'u':
            case 'U':
                //this gets the file name from the user
                cout << "What is path and name of the file you want to upload?\n";
                cout << "Make sure to right the appropriate path and file.\n";
                cin >> fileNameAndPath;
                
                uploadFile(fileNameAndPath, loadSuccess, sCode, len, dep, hei, lenF, depF, oNum, reg);
                
                if(loadSuccess)
                    cout << "\nFile was properly uploaded.\n";
                else
                    cout << "\nERROR: File was not properly uploaded.\n";
                
                break;
                
            case 'a':
            case 'A':
                allDetails(sCode, len, dep, hei, lenF, depF, oNum, reg);
                break;
                
            case 'o':
            case 'O':
                orderDetails(sCode, len, dep, hei, lenF, depF, oNum, reg);
                break;
                
            case 'r':
            case 'R':
                summaryByRegion(sCode, len, dep, hei, lenF, depF, oNum, reg);
                break;
                
            case 's':
            case 'S':
                summaryByStone(sCode, len, dep, hei, lenF, depF, oNum, reg);
                break;
                
            case 'c':
            case 'C':
                allClear = clearAllVectors(sCode, len, dep, hei, lenF, depF, oNum, reg);
                if(allClear)
                    cout << "\nVectors are all clear.\n";
                else
                    cout << "\nVectors are not all clear.\n";
                break;
            
            case 'q':
            case 'Q':
                break;
            
            default:
                cout << "\n\nThat is not one of the choices.\n";
                break;
    
        }
        
    }while((reply != 'q') && (reply != 'Q'));
    
    cout << "\nYou have quit the application.\n";
    cout << "Have a great day and come back soon!\n\n";
    
    return 0;
}


/***********************************************************************************************
 
 
 The following function displays the menu.
 
 
 ***********************************************************************************************/

char displayMenu() {
    char reply;
    
    cout << "\n\n\n";
    cout << setw(50) << right<<  "Upload a regional sales data file" << setw(5) << "U\n" ;
    cout << setw(50) << right<< "Display details (All loaded data)" << setw(5) << "A\n" ;
    cout << setw(50) << right<<  "List details for specific by Order number" << setw(5) << "O\n" ;
    cout << setw(50) << right<< "Display Summary by Region" << setw(5) << "R\n" ;
    cout << setw(50) << right<< "Display Summary by Stone code" << setw(5) << "S\n" ;
    cout << setw(50) << right<<  "Clear all vectors" << setw(5) << "C\n" ;
    cout << setw(50) << right<<  "Quit" << setw(5) << "Q\n" ;
    cout << "\n\n\n";
    cout << "Please enter your choice: ";
    cin >> reply;
    cin.ignore(500,'\n');
    return reply;
}


/***********************************************************************************************
 
 
 The following function uploads a file and stores it into the appropriate vectors.
 
 
 ***********************************************************************************************/


void uploadFile (string fName, bool &loadSuccess, vector<char> &sCode, vector<double> &len, vector<double> &dep, vector<double> &hei, vector<int> &lenF, vector<int> &depF, vector<string> &oNum, vector<string> &reg){
    {
        //the following are the variables of the program
        int original = static_cast<int>(sCode.size());
        string columnHeadings = "";
        string orderDate = "";
        string fileNameAndPath = fName;
        char material;
        string region;
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
            << setw(3) << "D" << setw(7) << "Region" << setw(10) << "Sq." << setw(11)
            << "Total" << endl;
            cout << setw(10) << "Date" << setw(12) << "Date"
            << setw(3) << "C" << setw(7) << "Len." << setw(7)
            << "Dep." << setw(7) << "Hei." << setw(3) << "E"
            << setw(3)<< "E"<< setw(7) << "       "<< setw(10)<< "Ft." << setw(11)
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
                  >> depthEdges >> orderNumber >> region >> fipsStateCode
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
                    (orderDateDay < 1) || (orderDateDay > 31))
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
                    
                    sCode.push_back (material);
                    len.push_back(length);
                    dep.push_back (depth);
                    hei.push_back(height);
                    lenF.push_back (lengthEdges);
                    depF.push_back(depthEdges);
                    oNum.push_back (orderNumber);
                    reg.push_back(region);
                    
                    //Outputs all the information
                    cout << setw(4)<< orderDateYear << delimiter << setw(2)<< orderDateMonth
                    << delimiter << setw(2)<< orderDateDay << "  "<< deliveryDateYear << delimiter
                    << setw(2) << deliveryDateMonth << delimiter << setw(2)<< deliveryDateDay
                    << setw(3) << material << setw(7) << length << setw(7)
                    << depth << setw(7) << height << setw(3) << lengthEdges
                    << setw(3)<< depthEdges<< setw(7) << region << setw(10)<< ceil(materialRequired)
                    << setw(11) << totalCost << endl;
                    
                }
                //This keeps the count of all the records without
                totalRecords = totalRecords + 1;
                
            }
            
            
            //The following is the summary table that is outputted
            //after while loop is executed
            cout << "\nCounts: Total Records = " << totalRecords
            << "      Records with Errors = " << recordsWithErrors
            << "      Records without Errors = " << recordsWithoutErrors << endl;
            
            /* Code was taken out because this part is shown in summaryByStone function
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
             */
        }
        
        if (original < sCode.size())
            loadSuccess = true;
        else
            loadSuccess = false;
        
    }

  
}


/***********************************************************************************************
 
 
 The following function outputs all the data in the vectors.
 
 
 ***********************************************************************************************/

void allDetails(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg){
    
    string line1;
    double materialCost = 0.0, costOfMaterial= 0.0, costOfEdgingLength= 0.0, costOfEdgingDepth= 0.0, totalEdgingCost= 0.0, totalCost= 0.0, materialRequired= 0.0;
   
    cout << showpoint << fixed << setprecision(2);
    
    //The following are the headers for the columns
    cout << endl << setw(10) << "Order"<< setw(3) << "S" << setw(7) << "      "<< setw(7)
    << "      " << setw(7) << "      " << setw(3) << "L"
    << setw(3) << "D" << setw(9) << "  Region"<< setw(10) << "Sq." << setw(11)
    << "Total" << endl;
    cout << setw(10) << "Number" << setw(3) << "C" << setw(7) << "Len." << setw(7)
    << "Dep." << setw(7) << "Hei." << setw(3) << "E"
    << setw(3)<< "E"<< setw(9) << "         "<< setw(10)<< "Ft." << setw(11)
    << "Cost" << endl;
    
    line1.assign(80, '-');
    cout << line1 << endl;
    
    if ((sCode.size() == 0) && (len.size() == 0) && (dep.size() == 0) && (hei.size() ==0)
        && (lenF.size() == 0) && (depF.size() == 0) && (oNum.size() == 0) && (reg.size() == 0) )
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
        for( int i = 0; i < sCode.size();  i++)
        {
            if (sCode[i] == 'M'|| sCode[i] == 'm')
            {
                materialCost = COST_OF_MARBLE;
            }
            else if (sCode[i]  == 'G'|| sCode[i]  == 'g')
            {
                materialCost = COST_OF_GRANITE;
            }
            else if (sCode[i]  == 'Q'|| sCode[i]  == 'q')
            {
                materialCost = COST_OF_QUARTZ;
            }
            
            //These are the necessay calculations
            materialRequired = len[i] * hei[i] * WASTAGE_MULTIPLIER;
            costOfMaterial = materialCost * ceil(materialRequired);
            costOfEdgingLength = lenF[i] * len[i] * EDGING_COST;
            costOfEdgingDepth = dep[i] * dep[i] * EDGING_COST;
            totalEdgingCost = costOfEdgingDepth + costOfEdgingLength;
            
            totalCost = costOfMaterial + totalEdgingCost;
            
            cout << setw(10) << oNum[i] << setw(3) << sCode[i] << setw(7) << len[i] << setw(7)
            << dep[i]<< setw(7) << hei[i] << setw(3) << lenF[i]
            << setw(3)<< depF[i]<< setw(9) << reg[i] << setw(10)<< ceil(materialRequired) << setw(11)
            << totalCost << endl;
        }
    }

}


/***********************************************************************************************
 
 
 The following function shows the details of a specific order
 
 
 ***********************************************************************************************/

void orderDetails(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg){

    //the following are the variables of the program
    char material;
    string region;
    double materialCost = 0.0, length, depth, height,
    costOfMaterial= 0.0, costOfEdgingLength= 0.0, costOfEdgingDepth= 0.0,
    totalEdgingCost= 0.0, totalCost= 0.0, materialRequired= 0.0;
    int lengthEdges=0, depthEdges=0;
    string line1;
    string errors = "";
    string customerInfo, fipsStateCode, orderNumber;
    string orderSearch;
    bool loadSuccess = false;
    
    if ((sCode.size() == 0) && (len.size() == 0) && (dep.size() == 0) && (hei.size() ==0)
        && (lenF.size() == 0) && (depF.size() == 0) && (oNum.size() == 0) && (reg.size() == 0) )
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
        cout << "What order do you want to look at? ";
        cin >> orderSearch;
    
        cout << showpoint << fixed << setprecision(2);
    
        //The following are the headers for the columns
        cout << endl << setw(10) << "Order"<< setw(3) << "S" << setw(7) << "      "<< setw(7)
        << "      " << setw(7) << "      " << setw(3) << "L"
        << setw(3) << "D" << setw(9) << "  Region"<< setw(10) << "Sq." << setw(11)
        << "Total"<< endl;
        cout << setw(10) << "Number" << setw(3) << "C" << setw(7) << "Len." << setw(7)
        << "Dep." << setw(7) << "Hei." << setw(3) << "E"
        << setw(3)<< "E"<< setw(9) << "         "<< setw(10)<< "Ft." << setw(11)
        << "Cost" << endl;
    
        line1.assign(80, '-');
        cout << line1 << endl;
    
        if ((sCode.size() == 0) && (len.size() == 0) && (dep.size() == 0) && (hei.size() ==0)
            && (lenF.size() == 0) && (depF.size() == 0) && (oNum.size() == 0) && (reg.size() == 0) )
        {
            cout << "\nNo file has been loaded.\n";
        }
        else {
            //If there is an error then the following if statement will be outputted,
            //otherwise it will continue
            for( int i = 0; i < sCode.size(); i++)
            {
            if (oNum[i] == orderSearch)
                {
                    material = sCode[i];
                    length = len[i];
                    height = hei[i];
                    depth = dep[i];
                    lengthEdges = lenF[i];
                    depthEdges = depF[i];
        
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
                    materialRequired = len[i] * hei[i] * WASTAGE_MULTIPLIER;
                    costOfMaterial = materialCost * ceil(materialRequired);
                    costOfEdgingLength = lenF[i] * len[i] * EDGING_COST;
                    costOfEdgingDepth = dep[i] * dep[i] * EDGING_COST;
                    totalEdgingCost = costOfEdgingDepth + costOfEdgingLength;
            
                    totalCost = costOfMaterial + totalEdgingCost;

            
                    cout << setw(10) << oNum[i] << setw(3) << sCode[i] << setw(7) << len[i] << setw(7)
                    << dep[i]<< setw(7) << hei[i] << setw(3) << lenF[i]
                    << setw(3)<< depF[i]<< setw(9) << reg[i] << setw(10)<< ceil(materialRequired) << setw(11)
                    << totalCost << endl;
                
                    loadSuccess = true;
                }
        
            }
        }
    
        if(!loadSuccess)
        {
            cout << "ERROR: The Order Number you entered was not in the database.\n";
        
        }
        
    }
}


/***********************************************************************************************
 
 
 The following function outputs a summary table of the data by Region
 
 
 ***********************************************************************************************/

void summaryByRegion(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg){
    //the following are the variables of the program
    char material;
    string region;
    double materialCost = 0.0, length, depth, height,
    costOfMaterial= 0.0, costOfEdgingLength= 0.0, costOfEdgingDepth= 0.0,
    totalEdgingCost= 0.0, totalCost= 0.0, materialRequired= 0.0;
    double NTotalSqFeet= 0.0, STotalSqFeet= 0.0, ETotalSqFeet= 0.0,
    WTotalSqFeet= 0.0, OTotalSqFeet= 0.0, NTotalCost= 0.0, STotalCost= 0.0,
    ETotalCost= 0.0, WTotalCost= 0.0, OTotalCost= 0.0;
    int NCount=0, SCount=0, ECount=0, WCount = 0, OCount = 0;
    int lengthEdges=0, depthEdges=0;
    string line2;
   
    
    //If there is nothing in the vector, then it will not run.
    if ((sCode.size() == 0) && (len.size() == 0) && (dep.size() == 0) && (hei.size() ==0)
        && (lenF.size() == 0) && (depF.size() == 0) && (oNum.size() == 0) && (reg.size() == 0) )
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
        //If there is an error then the following if statement will be outputted,
        //otherwise it will continue
        for( int i = 0; i < sCode.size(); i++)
        {
            material = sCode[i];
            length = len[i];
            height = hei[i];
            depth = dep[i];
            lengthEdges = lenF[i];
            depthEdges = depF[i];
            region = reg[i];
        
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
            if (region == "North")
            {
                NTotalSqFeet = NTotalSqFeet + ceil(materialRequired);
                NTotalCost = NTotalCost + totalCost;
                NCount = NCount + 1;
            
            }
            else if (region == "South")
            {
                STotalSqFeet = STotalSqFeet + ceil(materialRequired);
                STotalCost = STotalCost + totalCost;
                SCount = SCount + 1;
            
            }
        
            else if (region == "East")
            {
                ETotalSqFeet = ETotalSqFeet + ceil(materialRequired);
                ETotalCost = ETotalCost + totalCost;
                ECount = ECount + 1;
            }
            else if (region == "West")
            {
                WTotalSqFeet = WTotalSqFeet + ceil(materialRequired);
                WTotalCost = WTotalCost + totalCost;
                WCount = WCount + 1;
            }
            else
            {
                OTotalSqFeet = OTotalSqFeet + ceil(materialRequired);
                OTotalCost = OTotalCost + totalCost;
                OCount = OCount + 1;
            }
        
        }
    
        //The following is the summary table that is outputted
        //after while loop is executed
    
        line2.assign(50, '-');
    
        cout << endl << setw(9) << "Region" << setw(8) << "Count"
        << setw(15) << "Square Feet" << setw(15)
        << "Cost" << endl;
        cout << line2 << endl;
    
        cout << setw(9) << "North" << setw(8) << NCount
        << setw(15) << NTotalSqFeet << setw(15)
        << NTotalCost << endl;
    
        cout << setw(9) << "South" << setw(8) << SCount
        << setw(15) << STotalSqFeet << setw(15)
        << STotalCost << endl;
    
        cout << setw(9) << "East" << setw(8) << ECount
        << setw(15) << ETotalSqFeet << setw(15)
        << ETotalCost << endl;
    
        cout << setw(9) << "West" << setw(8) << WCount
        << setw(15) << WTotalSqFeet << setw(15)
        << WTotalCost << endl;
    
        cout << setw(9) << "Other" << setw(8) << OCount
        << setw(15) << OTotalSqFeet << setw(15)
        << OTotalCost << endl;
        cout << line2 << "\n\n";

    }
}

/***********************************************************************************************
 
 
 The following function outputs a summary table of the data by material/stone code.
 
 
 ***********************************************************************************************/


void summaryByStone(const vector<char> &sCode, const vector<double> &len, const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF, const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg){
    
    //the following are the variables of the program
    char material;
    string region;
    double materialCost = 0.0, length, depth, height,
    costOfMaterial= 0.0, costOfEdgingLength= 0.0, costOfEdgingDepth= 0.0,
    totalEdgingCost= 0.0, totalCost= 0.0, materialRequired= 0.0;
    double mTotalSqFeet= 0.0, gTotalSqFeet= 0.0, qTotalSqFeet= 0.0,
    mTotalCost= 0.0, gTotalCost= 0.0, qTotalCost= 0.0;
    int mCount=0, gCount=0, qCount=0;
    int lengthEdges=0, depthEdges=0;
    string line2;
    
    //If there is nothing in the vector, then it will not run.
    if ((sCode.size() == 0) && (len.size() == 0) && (dep.size() == 0) && (hei.size() ==0)
        && (lenF.size() == 0) && (depF.size() == 0) && (oNum.size() == 0) && (reg.size() == 0) )
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
            //If there is an error then the following if statement will be outputted,
            //otherwise it will continue
            for( int i = 0; i < sCode.size(); i++)
            {
                material = sCode[i];
                length = len[i];
                height = hei[i];
                depth = dep[i];
                lengthEdges = lenF[i];
                depthEdges = depF[i];
                
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
 
            }
    
        //The following is the summary table that is outputted
        //after while loop is executed
        
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

}

/***********************************************************************************************
 
 
 The following function clears out all the vectors.
 
 
 ***********************************************************************************************/



bool clearAllVectors(vector<char> &sCode, vector<double> &len, vector<double> &dep, vector<double> &hei, vector<int> &lenF, vector<int> &depF, vector<string> &oNum, vector<string> &reg){
    bool clear;
    sCode.clear(); len.clear(); dep.clear(); hei.clear(); lenF.clear();
    depF.clear(); oNum.clear(); reg.clear();
    

    
    if ((sCode.size() == 0) && (len.size() == 0) && (dep.size() == 0) && (hei.size() ==0)
        && (lenF.size() == 0) && (depF.size() == 0) && (oNum.size() == 0) && (reg.size() == 0) )
        clear = true;
    else
        clear = false;
    
    return clear;
}