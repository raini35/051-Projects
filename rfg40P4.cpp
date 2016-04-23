/*
 * rfg40P4.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #4
 *
 *  Due on: APR 13, 2016
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



class CounterTop
{
    friend ostream& operator<<( ostream &os, const CounterTop &rhsObj );
    
private:
    int orderYear, orderMonth, orderDay;
    int deliveryYear, deliveryMonth, deliveryDay;
    
    char stoneCode;
    
    double length;
    double depth;
    double height;
    
    int lengthEdgesToFinish;
    int depthEdgesToFinish;
    
    string orderNumber;
    string region;
    string fipsStateCode;
    string customerNameAddress;
    string delimiter;
    
public:
    //required constructors
    //you may change parameter identifiers, but the order and types of the parameters
    //must be the same as shown in the prototypes
    CounterTop();
    
    CounterTop(int oYYYY, int oMM, int oDD, int dYYYY, int dMM, int dDD,
               char sCode, double len, double dep, double hei, int lenF, int depF,
               string oNum, string reg, string stCode, string custNameAdd);
    
    CounterTop( const CounterTop &otherObj );
    
    //required basic mutator functions, in-line implementation
    //you may change parameter identifiers but NOT the function identifiers
    void setStoneCode(char sCode) { stoneCode = sCode; }
    
    void setLength( double len ) { length = len; }
    void setDepth( double dep ) { depth = dep; }
    void setHeight( double hei ) { height = hei; }
    
    void setLenEdgeF( int lenF ) { lengthEdgesToFinish = lenF; }
    void setDepEdgeF( int depF ) { depthEdgesToFinish = depF; }
    
    void setOrderNum( string oNum ) { orderNumber = oNum; }
    void setRegion( string reg ) { region = reg; }
    void setFIPS( string stCode ) { fipsStateCode = stCode; }
    void setCustomerNameAdd( string custNameAdd ) { customerNameAddress = custNameAdd; }
    
    
    //required basic accessor functions, in-line implementation
    //you may change parameter identifiers but NOT the function identifiers
    char getStoneCode() const { return stoneCode; }
    
    double getLength() const { return length; }
    double getDepth() const { return depth; }
    double getHeight() const { return height; }
    
    int getLenEdgeF() const { return lengthEdgesToFinish; }
    int getDepEdgeF() const { return depthEdgesToFinish; }
    
    string getOrderNum() const { return orderNumber; }
    string getRegion() const { return region; }
    string getFIPS() const { return fipsStateCode; }
    string getCustomerNameAdd() const { return customerNameAddress; }
    
    //required accessor functions that perform more detailed calculations
    //you may change parameter identifiers but NOT the function identifiers
    void setOrderDate(int yyyy, int mm, int dd);
    void setDeliveryDate(int yyyy, int mm, int dd);
    
    double getCounterTopArea() const;
    double getMaterialRequired() const;
    double getStoneCost() const;
    double getFinishingCost() const;
    double getTotalCost() const;
    
    
};


/***********************************************************************************************
 
 These are the constructors fo the class
 
 ***********************************************************************************************/

//Set the default constructor to zeroes & empty strings according to data type
CounterTop :: CounterTop() {
    orderYear = orderMonth = orderDay = deliveryYear =  deliveryMonth =
    deliveryDay = lengthEdgesToFinish = depthEdgesToFinish = 0;
    length = depth = height = 0.0;
    
    stoneCode = '';
    
    orderNumber = region = fipsStateCode = customerNameAddress = "";
    
}

//Set constructor so that it updates the value of the character according to
//individual inputs
CounterTop :: CounterTop (int oYYYY, int oMM, int oDD, int dYYYY, int dMM, int dDD,
                           char sCode, double len, double dep, double hei, int lenF, int depF,
                       string oNum, string reg, string stCode, string custNameAdd){
    orderYear = oYYYY;
    orderMonth = oMM;
    orderDay = oDD;
    deliveryYear = dYYYY;
    deliveryMonth = dMM;
    deliveryDay = dDD;
    
    stoneCode = sCode;
    
    length = len;
    depth = dep;
    height = hei;
    
    lengthEdgesToFinish = lenF;
    depthEdgesToFinish = depF;
    
    orderNumber = oNum;
    region = reg;
    fipsStateCode = stCode;
    customerNameAddress = custNameAdd;

    
}

CounterTop::CounterTop( const CounterTop &otherObj ){
    orderYear = otherObj.orderYear;
    orderMonth = otherObj.orderMonth;
    orderDay = otherObj.orderDay;
    deliveryYear = otherObj.deliveryYear;
    deliveryMonth = otherObj.deliveryMonth;
    deliveryDay = otherObj.deliveryDay;
    
    stoneCode = otherObj.stoneCode;
    
    length = otherObj.length;
    depth = otherObj.depth;
    height = otherObj.height;
    
    lengthEdgesToFinish = otherObj.lengthEdgesToFinish;
    depthEdgesToFinish = otherObj.depthEdgesToFinish;
    
    orderNumber = otherObj.orderNumber;
    region = otherObj.region;
    fipsStateCode = otherObj.fipsStateCode;
    customerNameAddress = otherObj.customerNameAddress;

    
}

/***********************************************************************************************
 
 These are the member functions of the CounterTopclass
 
 ***********************************************************************************************/

void CounterTop::setOrderDate(int yyyy, int mm, int dd){
    orderYear = yyyy;
    orderMonth = mm;
    orderDay = dd;
  
}
void CounterTop::setDeliveryDate(int yyyy, int mm, int dd){
    deliveryYear = yyyy;
    deliveryMonth = mm;
    deliveryDay = dd;
}
double CounterTop::getCounterTopArea() const { return length * height;
}

double CounterTop::getMaterialRequired() const {
    return ceil(WASTAGE_MULTIPLIER * getCounterTopArea());
}

double CounterTop::getStoneCost() const{
    
    double materialCost;
    
    if (stoneCode == 'M'|| stoneCode == 'm')
    {
        materialCost = COST_OF_MARBLE;
    }
    else if (stoneCode == 'G'|| stoneCode == 'g')
    {
        materialCost = COST_OF_GRANITE;
    }
    else if (stoneCode == 'Q'|| stoneCode == 'q')
    {
        materialCost = COST_OF_QUARTZ;
    }
    
    return materialCost;
    
}

double CounterTop::getFinishingCost() const{
    double costOfEdgingLength;
    double costOfEdgingDepth;
    
    costOfEdgingLength = lengthEdgesToFinish * length * EDGING_COST;
    costOfEdgingDepth = depthEdgesToFinish * depth * EDGING_COST;
    
    return costOfEdgingDepth + costOfEdgingLength;
}

double CounterTop::getTotalCost() const{
    
    return getStoneCost() * getMaterialRequired() + getFinishingCost();
    
}
ostream& operator<<( ostream & os, const CounterTop& rhsObj ) {
    
    os << setw(4)<< rhsObj.orderYear << rhsObj.delimiter << setw(2)
    << rhsObj.orderMonth << rhsObj.delimiter << setw(2)<< rhsObj.orderDay
    << "  "<< rhsObj.deliveryYear << rhsObj.delimiter
    << setw(2) << rhsObj.deliveryMonth << rhsObj.delimiter << setw(2)
    << rhsObj.deliveryDay << setw(3) << rhsObj.stoneCode << setw(7)
    << rhsObj.length << setw(7) << rhsObj.depth << setw(7) << rhsObj.height
    << setw(3) << rhsObj.lengthEdgesToFinish << setw(3)<< rhsObj.depthEdgesToFinish
    << setw(7) << rhsObj.region << setw(10)<< rhsObj.getMaterialRequired()
    << setw(11) << rhsObj.getTotalCost() << endl;
    
    return os;
    
}

/***********************************************************************************************
 
 The following lines are the function prototypes of the functions needed in the program.
 
 ***********************************************************************************************/

char displayMenu();
void uploadFile(string fName, bool &loadSuccess, vector<CounterTop> &vCounterTops);
void allDetails(const vector<CounterTop> &vCounterTops);
void orderDetails(const vector<CounterTop> &vCounterTops);
void summaryByStone(const vector<CounterTop> &vCounterTops);
void summaryByRegion(const vector<CounterTop> &vCounterTops);
bool clearVector(vector<CounterTop> &vCounterTops);


int main(int argc, const char * argv[]) {
    char reply;
    string fileNameAndPath;
    string fName;
    bool loadSuccess, allClear;
    vector<CounterTop> allCounterTops;
    
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
                
                uploadFile(fileNameAndPath, loadSuccess, allCounterTops);
                
                if(loadSuccess)
                    cout << "\nFile was properly uploaded.\n";
                else
                    cout << "\nERROR: File was not properly uploaded.\n";
                
                break;
                
            case 'a':
            case 'A':
                allDetails(allCounterTops);
                break;
                
            case 'o':
            case 'O':
                orderDetails(allCounterTops);
                break;
                
            case 'r':
            case 'R':
                summaryByRegion(allCounterTops);
                break;
                
            case 's':
            case 'S':
                summaryByStone(allCounterTops);
                break;
                
            case 'c':
            case 'C':
                allClear = clearVector(allCounterTops);
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

void uploadFile(string fName, bool &loadSuccess, vector<CounterTop> &vCounterTops) {
    {
        //the following are the variables of the program
        CounterTop tempCounterTop;
        int original = static_cast<int>(vCounterTops.size());
        string columnHeadings = "";
        string orderDate = "";
        string fileNameAndPath = fName;
        char material;
        string region;
        char delimiter = '/';
        double length, depth, height, minHeight = 0.0, maxHeight = 0.0,
        totalCost= 0.0, depthMax = 0.0, materialRequired= 0.0;
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
                    cout << setw(4)<< orderDateYear << delimiter <<setw(2)
                    << orderDateMonth << delimiter << setw(2) << orderDateDay
                    << "  "<< deliveryDateYear << delimiter << deliveryDateMonth
                    << delimiter<<  setw(2) << deliveryDateDay
                    << setw(3) << material << setw(7) << length << setw(7)
                    << depth << setw(7) << height << setw(3) << lengthEdges
                    << setw(3)<< depthEdges<< setw(10)<< static_cast<char>(materialRequired)
                    << setw(11)<< static_cast<char>(totalCost) << errors << "\n\n";
                    
                    recordsWithErrors = recordsWithErrors + 1;
                    
                }
                // if there are no mistakes the following code will execute
                else
                {
                    //the following code sets the values to the temporary CounterTop class
                    tempCounterTop.setOrderDate(orderDateYear, orderDateMonth, orderDateDay);
                    tempCounterTop.setDeliveryDate(deliveryDateYear, deliveryDateMonth, deliveryDateDay);
                    tempCounterTop.setStoneCode(material);
                    tempCounterTop.setLength(length);
                    tempCounterTop.setHeight(height);
                    tempCounterTop.setDepth(depth);
                    tempCounterTop.setLenEdgeF(lengthEdges);
                    tempCounterTop.setDepEdgeF(depthEdges);
                    tempCounterTop.setRegion(region);
                    tempCounterTop.setOrderNum(orderNumber);
                    tempCounterTop.setFIPS(fipsStateCode);
                    tempCounterTop.setCustomerNameAdd(customerInfo);
                    
                    //This sorts out the individual orders by material
                    if (material == 'M' || material == 'm')
                    {
                        mTotalSqFeet = mTotalSqFeet + tempCounterTop.getMaterialRequired();
                        mTotalCost = mTotalCost + tempCounterTop.getTotalCost();
                        mCount = mCount + 1;
                        
                    }
                    
                    else if (material == 'G'|| material == 'g')
                    {
                        gTotalSqFeet = gTotalSqFeet + tempCounterTop.getMaterialRequired();
                        gTotalCost = gTotalCost + tempCounterTop.getTotalCost();
                        gCount = gCount + 1;
                        
                    }
                    
                    else if (material == 'Q'|| material == 'q')
                    {
                        qTotalSqFeet = qTotalSqFeet + tempCounterTop.getMaterialRequired();
                        qTotalCost = qTotalCost + tempCounterTop.getTotalCost();
                        qCount = qCount + 1;
                    }
                    //This keeps the count of records without errors
                    recordsWithoutErrors = recordsWithoutErrors + 1;
                    
                    vCounterTops.push_back (tempCounterTop);
                    
                    //Outputs all the information
                    cout << tempCounterTop;
                    
                }
                //This keeps the count of all the records without
                totalRecords = totalRecords + 1;
                
            }
            
            //The following is the summary table that is outputted
            //after while loop is executed
            cout << "\nCounts: Total Records = " << totalRecords
            << "      Records with Errors = " << recordsWithErrors
            << "      Records without Errors = " << recordsWithoutErrors << endl;
            
        }
        
        if (original < vCounterTops.size())
            loadSuccess = true;
        else
            loadSuccess = false;
        
    }
    
    
}


/***********************************************************************************************
 
 
 The following function outputs all the data in the vectors.
 
 
 ***********************************************************************************************/

void allDetails(const vector<CounterTop> &vCounterTops){
    
    string line1;
    
    cout << showpoint << fixed << setprecision(2);
    
    //The following are the headers for the columns
    cout << endl << setw(10) << "Order"<< setw(3) << "S"
    << setw(7) << "      "<< setw(7) << "      " <<
    setw(7) << "      " << setw(3) << "L" << setw(3)
    << "D" << setw(9) << "  Region"<< setw(10) << "Sq." << setw(11)
    << "Total" << endl;
    
    cout << setw(10) << "Number" << setw(3) << "C" <<
    setw(7) << "Len." << setw(7) << "Dep." <<
    setw(7) << "Hei." << setw(3) << "E" <<
    setw(3)<< "E"<< setw(9) << "         "<<
    setw(10)<< "Ft." << setw(11) << "Cost" << endl;
    
    line1.assign(80, '-');
    cout << line1 << endl;
    
    if (vCounterTops.size() == 0)
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
        for( int i = 0; i < vCounterTops.size();  i++)
        {
            cout << vCounterTops[i];
        }
    }
    
}


/***********************************************************************************************
 
 
 The following function shows the details of a specific order
 
 
 ***********************************************************************************************/

/*void orderDetails(const vector<char> &sCode, const vector<double> &len,
                  const vector<double> &dep, const vector<double> &hei,
                  const vector<int> &lenF, const vector<int> &depF,
                  const vector<string> &oNum, const vector<string> &reg)*/
void orderDetails(const vector<CounterTop> &vCounterTops) {
    
    //the following are the variables of the program
    string region;
    string line1;
    string errors = "";
    string customerInfo, fipsStateCode, orderNumber;
    string orderSearch;
    bool loadSuccess = false;
    
    if ((vCounterTops.size() == 0))
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
        
        if ((vCounterTops.size() == 0))
        {
            cout << "\nNo file has been loaded.\n";
        }
        else {
            //If there is an error then the following if statement will be outputted,
            //otherwise it will continue
            for( int i = 0; i < vCounterTops.size(); i++)
            {
                if (vCounterTops[i].getOrderNum() == orderSearch)
                {
                    cout << vCounterTops[i];
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

void summaryByRegion(const vector<CounterTop> &vCounterTops) {
    //the following are the variables of the program
    string region;
    double NTotalSqFeet= 0.0, STotalSqFeet= 0.0, ETotalSqFeet= 0.0,
    WTotalSqFeet= 0.0, OTotalSqFeet= 0.0, NTotalCost= 0.0, STotalCost= 0.0,
    ETotalCost= 0.0, WTotalCost= 0.0, OTotalCost= 0.0;
    int NCount=0, SCount=0, ECount=0, WCount = 0, OCount = 0;
    string line2;
    
    //If there is nothing in the vector, then it will not run.
    if ((vCounterTops.size() == 0))
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
        //If there is an error then the following if statement will be outputted,
        //otherwise it will continue
        for( int i = 0; i < vCounterTops.size(); i++)
        {            region = vCounterTops[i].getRegion();
            
            if (region == "North")
            {
                NTotalSqFeet = NTotalSqFeet + vCounterTops[i].getMaterialRequired();
                NTotalCost = NTotalCost + vCounterTops[i].getTotalCost();
                NCount = NCount + 1;
                
            }
            else if (region == "South")
            {
                STotalSqFeet = STotalSqFeet + vCounterTops[i].getMaterialRequired();
                STotalCost = STotalCost + vCounterTops[i].getTotalCost();
                SCount = SCount + 1;
                
            }
            
            else if (region == "East")
            {
                ETotalSqFeet = ETotalSqFeet + vCounterTops[i].getMaterialRequired();
                ETotalCost = ETotalCost + vCounterTops[i].getTotalCost();
                ECount = ECount + 1;
            }
            else if (region == "West")
            {
                WTotalSqFeet = WTotalSqFeet + vCounterTops[i].getMaterialRequired();
                WTotalCost = WTotalCost + vCounterTops[i].getTotalCost();
                WCount = WCount + 1;
            }
            else
            {
                OTotalSqFeet = OTotalSqFeet + vCounterTops[i].getMaterialRequired();
                OTotalCost = OTotalCost + vCounterTops[i].getTotalCost();
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

void summaryByStone(const vector<CounterTop> &vCounterTops){
    
    //the following are the variables of the program
    char material;
    double mTotalSqFeet= 0.0, gTotalSqFeet= 0.0, qTotalSqFeet= 0.0,
    mTotalCost= 0.0, gTotalCost= 0.0, qTotalCost= 0.0;
    int mCount=0, gCount=0, qCount=0;
    string line2;
    
    //If there is nothing in the vector, then it will not run.
    if (vCounterTops.size() == 0)
    {
        cout << "\nNo file has been loaded.\n";
    }
    else {
        //If there is an error then the following if statement will be outputted,
        //otherwise it will continue
        for( int i = 0; i < vCounterTops.size(); i++)
        {
            material = vCounterTops[i].getStoneCode();
            
            //This sorts out the individual orders by material
            if (material == 'M' || material == 'm')
            {
                mTotalSqFeet = mTotalSqFeet + vCounterTops[i].getMaterialRequired();
                mTotalCost = mTotalCost + vCounterTops[i].getTotalCost();
                mCount = mCount + 1;
                
            }
            
            else if (material == 'G'|| material == 'g')
            {
                gTotalSqFeet = gTotalSqFeet + vCounterTops[i].getMaterialRequired();
                gTotalCost = gTotalCost + vCounterTops[i].getTotalCost();
                gCount = gCount + 1;
                
            }
            
            else if (material == 'Q'|| material == 'q')
            {
                qTotalSqFeet = qTotalSqFeet + vCounterTops[i].getMaterialRequired();
                qTotalCost = qTotalCost + vCounterTops[i].getTotalCost();
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
 
 
 The following function clears out all the vectors. I just added this for the heck of it. 
 Unlike the others the function definition and prototype cannot contain 'const' or else it will
 not be able to delete the data inside the vector.
 
 
 ***********************************************************************************************/


bool clearVector(vector<CounterTop> &vCounterTops){
    bool clear;
    vCounterTops.clear();
    
    if (vCounterTops.size() == 0)
        clear = true;
    else
        clear = false;
    
    return clear;
}