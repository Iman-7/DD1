#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // to use string stream

using namespace std;
int main() {

    ifstream file("C:/Users/Dell/Desktop/Fall 2020/Digital Design 1/Projects/case1.txt");
    string line; //a string variable used to store the values seperated with commas
    string nn, mm, dd; // to recive the values from the file (nn: no. of variables, mm: minterms, dd: don't care terms)

    int n; //number of variables
    vector <int> minterms;
    vector <int> dontcare;
    int count =0;

    
    //to validate the inputs, the numbers entered for the minterms/don't care terms must be integers that are >=0 and < 2^n 
    if (!file.is_open())
    {
        cout << "error opening the file" << endl;
        return 0;
    }
    else
    {
                //We have 3 lines in the text file
               
                //first line that has the number of variables
                getline(file, nn, '\n');
                n = stoi(nn); // we obtained the number of variables
                
                //second line that has the minterms
                getline(file, mm, '\n');
                stringstream data1(mm);
                while (getline(data1, line, ',')) 
                {
                   
                    //validation of the input values
                    if ((stoi(line) >= 0) && (stoi(line) < pow(2,n)))
                        minterms.push_back(stoi(line));
                    else
                    {
                        cout << "The minterm " << stoi(line) << " is invalid" << endl;
                        return 0;
                    }
                }
                
                //Third line that has the minterms
                getline(file, dd, '\n');
                stringstream data2(dd);
                while (getline(data2, line, ','))
                {
                    if ((stoi(line) >= 0) && (stoi(line) < pow(2, n)))
                        dontcare.push_back(stoi(line));
                    else
                    {
                        cout << "The don't care term " << stoi(line) << " is invalid" << endl;
                        return 0;
                    }
                    
                }

            //}
            file.close();

    }

    // checking that the data entry is working
    cout << "the number of variables is: " << n << endl;
    
    cout << "the minterms are: ";
    for (int i = 0; i < minterms.size(); i++)
        cout << minterms[i] << "\t";
    cout << endl;
   
    cout << "the don't care terms are: ";
    for (int i = 0; i < dontcare.size(); i++)
        cout << dontcare[i] << "\t";
    
	return 0;
}