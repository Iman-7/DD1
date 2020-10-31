#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // to use string stream
#include <bits/stdc++.h> //to use set intersection (STL) 
//#include <algorithm> // to use set intersection function

using namespace std;

bool validation(vector <int>, vector<int>);
string decimalTobinary(int);
string pad(string, int);
bool isGreyCode(string, string);
string replace(string, string);

//void decimalTobinary(int, vector<int>, vector<string>&);
//int countones(vector<string> d);
//void reorder(vector<vector<int>>&, int);


int main() {

    ifstream file("C:/Users/Dell/Desktop/Fall 2020/Digital Design 1/Projects/case5.txt");
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


    //print validation vector that stores all the common elements (if any)
    //just to understand - delte it later
   // for (int i = 0; i < val.size(); i++)
    //    cout << ((val[i]!=0)?val[i]:-1) << " ";

     /*

     // checking that the data entry is working
     cout << "the number of variables is: " << n << endl;

     cout << "the minterms are: ";
     for (int i = 0; i < minterms.size(); i++)
         cout << minterms[i] << "\t";
     cout << endl;

     cout << "the don't care terms are: ";
     for (int i = 0; i < dontcare.size(); i++)
         cout << dontcare[i] << "\t";
     */

     // Rawan Partttttttttttt




    vector<int> total_decimal(minterms.size() + dontcare.size()); // a vector that contains all the minterms and the don't care terms in decimal (Basically the first column of the implication table)
    vector <string> total_binary(total_decimal.size());
    vector<string> first_column(total_binary.size());
    vector <string> pi;
    vector <string> epi;

    
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
        //cout << total_binary[i];
        //cout << endl;
    }
    //cout << "bla bla " << endl;
  
    cout << "The binary equivalents of minterms and don't care terms are: " << endl;
  for (int i = 0; i < total_binary.size(); i++)
    {
       first_column[i] = pad(total_binary[i], n);
        cout << first_column[i] << endl;
    }

   for (int i = 0; i < first_column.size(); i++) {
      for (int j = i+1; j < first_column.size(); j++)
          if (isGreyCode(first_column[i], first_column[j]))
              pi.push_back (replace(first_column[i], first_column[j]));
   }

   cout << "The Prime Implicants (PIs) are: " << endl;
   for (int i = 0; i < pi.size(); i++) {
      cout << pi[i] << endl;
   }


   for (int i = 0; i < pi.size(); i++) {
       for (int j = i + 1; j < pi.size(); j++)
           if (isGreyCode(pi[i], pi[j]))
               epi.push_back(replace(pi[i], pi[j]));
   }
    
   cout << "The Essential Prime Implicants (EPIs) are: " << endl;
   for (int i = 0; i < epi.size(); i++) {
       cout << epi[i] << endl;
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

    if (val.size() > 0) // not correct 5alesssssssssssssssssssssss 34an el size keda keda hayb2a el sum bta3 el 2 sizes btoo3 el two vectors el tanyeen
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

/*int countones(vector<string> d) {
    int count = 0;
    for (int i = 0; i < d.size(); i++) {
        for (int j=0; j<d[i].size(); j++)
        if (d[i][j] == 1) {
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
}*/

bool isGreyCode(string s1, string s2) {

    int flag = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] != s2[i])
            flag++;
    }
    return (flag == 1);
}

string replace(string s1, string s2)
{
    string temp = "";
    for (int i = 0; i < s1.length(); i++)
        if (s1[i] != s2[i])
            temp = temp + "-";
        else
            temp = temp + s1[i];

    return temp;
}


