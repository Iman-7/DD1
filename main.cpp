#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // to use string stream

#include <string.h>
#include <iomanip>
#include <algorithm>
#include <iterator>

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
using namespace std;



bool validation(vector <int>, vector<int>);
string decimalTobinary(int);
string pad(string, int);

//void decimalTobinary(int, vector<int>, vector<string>&);
void reorder(vector<vector<int>>&, int);


int main() {
    
    ifstream file("/Users/rawansameh/Downloads/case1.txt");
    string line; //a string variable used to store the values seperated with commas
    string nn, mm, dd; // to recive the values from the file (nn: no. of variables, mm: minterms, dd: don't care terms)
    
    int n; //number of variables
    vector <int> minterms;
    vector <int> dontcare;
    
    
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
            if ((stoi(line) >= 0) && (stoi(line) < pow(2, n)))
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
        
        file.close();
        
    }
    
    //a vector to store the common elements between the minterms and the don't care terms vectors (if any)
    vector<int> val(minterms.size() + dontcare.size());
    
    //an iterator to traverse the vector
    vector<int>::iterator it, out;
    
    sort(minterms.begin(), minterms.end());
    sort(dontcare.begin(), dontcare.end());
    
    out = set_intersection(minterms.begin(), minterms.end(), dontcare.begin(), dontcare.end(), val.begin());
    
    int validation_size = 0;
    for (int i = 0; i < val.size(); i++) //still have a problem!!! what if the common elemnt was zero????
        if ((val[i]) != 0)
            validation_size++;
    
    if (validation_size != 0)
    {
        cout << "Error! Common elements: ";
        for (it = val.begin(); it != out; it++)
            cout << *it << " ";
        cout << endl;
        return 0;
    }
    
    
     
     
    
    
    
    
    vector<int> total_decimal (minterms.size()+dontcare.size()); // a vector that contains all the minterms and the don't care terms in decimal (Basically the first column of the implication table)
    vector <string> total_binary (total_decimal.size());
    vector<string> first_column(total_binary.size());
    
    
    for (int i = 0; i < minterms.size(); i++) {
        total_decimal[i] = (minterms[i]);
    }
    
    int c = 0;
    for (int k = minterms.size(); k < total_decimal.size(); k++) {
        total_decimal[k] = (dontcare[c]);
        c++;
    }
    
    
    /*decimalTobinary(n, total_decimal, total_binary); //no. of inputs, v, v
     for (int i = 0; i < total_decimal.size(); i++)
     {
     cout << total_binary[i];
     cout << endl;
     }
     */
    // decimalTobinary(n, total, first); //edit it
    
    /* for (int i = 0; i < first.size(); i++)
     reorder(first, n);
     
     
     for (int i = 0; i < first.size(); i++)
     {
     for (int j = 0; j < n; j++) {
     cout << first[i][j];
     }
     cout << endl;
     }
     */
    
    
    for (int i = 0; i < total_decimal.size(); i++)
    {
        total_binary[i]= decimalTobinary(total_decimal[i]);
        
    }
    
    
    for (int i = 0; i < total_binary.size(); i++)
    {
        first_column[i] = pad(total_binary[i], n);
        cout << first_column[i] << endl;
    }
    
    
    
    return 0;
}

bool validation(vector <int> v1, vector <int> v2)
{
    //a vector to store the common elements between the minterms and the don't care terms vectors (if any)
    vector<int> val(v1.size() + v2.size());
    
    //an iterator to traverse the vector
    vector<int>::iterator it, out;
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    out = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), val.begin());
    
    if (val.size() > 0) /
        return true;
    return false;
    /* cout << "Error! The element(s) ";
     for (it = val.begin(); it != out; it++)
     cout << *it << " - ";
     cout << "cannot be minterms and don't care terms at the time!" << endl;*/
}


string decimalTobinary(int var) {
    if (var == 0)
        return var + "";
    
    if (var % 2 == 0)
        return decimalTobinary(var / 2) + "0";
    else
        return decimalTobinary(var / 2) + "1";
    
}

string pad(string binary, int var)
{
    int diff = var - binary.length();
    for (int i = 0; i < diff; i++)
        binary = "0" + binary;
    return binary;
}

/*void decimalTobinary(int var, vector<int> decimal, vector<string>& string_b) {
 
 int k;
 
 for (int i = 0; i < decimal.size(); i++)
 {
 string_b[i] = "";
 for (int j = var - 1; j >= 0; j--)
 {
 k = decimal[i] >> j;
 if (k & 1)
 string_b[i] = string_b[i] + "1";
 else
 string_b[i]= string_b[i] + "0";
 }
 
 }
 }*/

int countones(vector<int> d) {
    int count = 0;
    for (int i = 0; i < d.size(); i++) {
        if (d[i] == 1) {
            count++;
        }
    }
    return count;
}
void reorder(vector<vector<int>>& d, int var) {
    vector<int> v;
    
    vector<int> v1;
    for (int i = 0; i < d.size(); i++)
    {
        for (int j = 0; j < var; j++) {
            if (i == d.size() - 1)
                break;
            v.push_back(d[i][j]);
            v1.push_back(d[i + 1][j]);
            
        }
        
        
        if (countones(v) > countones(v1))
            swap(d[i], d[i + 1]);
        
        v.clear();
        v1.clear();
        
    }
}
