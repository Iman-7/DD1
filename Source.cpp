#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // to use string stream
#include <bits/stdc++.h> //to use set intersection (STL) 
#include <cmath>
#include <unordered_set>
#include <unordered_map>
using namespace std;

bool validation(vector <int>, vector<int>);
string decimalTobinary(int);
string pad(string, int);
bool isGreyCode(string, string);
string replace(string, string);
void getMinterms(unordered_set<int>&, string, int, int);
string get_exp(string, const vector <string>);


int main() {

    ifstream file("C:/Users/Dell/Desktop/Fall 2020/Digital Design 1/Projects/case4.txt");
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
    for (int i = 0; i < val.size(); i++) 
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


    vector<int> total_decimal(minterms.size() + dontcare.size()); // a vector that contains all the minterms and the don't care terms in decimal (Basically the first column of the implication table)
    vector <string> total_binary(total_decimal.size());
    vector<string> first_column(total_binary.size());
    vector <string> second_column;
    vector <string> pi;
    vector<string> expression_var;
    string letters[] = { "a","b","c","d","e","f","g","h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t" };
    for (int i = 0; i < n; i++)
        expression_var.push_back(letters[i]);

    for (int i = 0; i < minterms.size(); i++) {
        total_decimal[i] = (minterms[i]);
    }

    int c = 0;
    for (int k = minterms.size(); k < total_decimal.size(); k++) {
        total_decimal[k] = (dontcare[c]);
        c++;
    }


    for (int i = 0; i < total_decimal.size(); i++)
    {
        total_binary[i] = decimalTobinary(total_decimal[i]);
       
    }

    cout << "The binary equivalents of minterms and don't care terms are (First Column): " << endl;
    for (int i = 0; i < total_binary.size(); i++)
    {
        first_column[i] = pad(total_binary[i], n);
        cout << first_column[i] << endl;
    }

    for (int i = 0; i < first_column.size(); i++) {
        for (int j = i + 1; j < first_column.size(); j++)
            if (isGreyCode(first_column[i], first_column[j]))
                second_column.push_back(replace(first_column[i], first_column[j]));
    }

    cout << "The Second Column is : " << endl;
    for (int i = 0; i < second_column.size(); i++) {
        cout << second_column[i] << endl;
    }

    vector<string> unchecked;
    vector<string> temp;
    int* checked = new int[second_column.size()];
    for (int i = 0; i < second_column.size(); i++) {
        for (int j = i + 1; j < second_column.size(); j++) {
            if (isGreyCode(second_column[i], second_column[j]))
            {
                checked[i] = 1;
                checked[j] = 1;
                pi.push_back(replace(second_column[i], second_column[j]));
            }

            if (checked[i] != 1)
                temp.push_back(second_column[i]);
        }
    }


    for (int i = 0; i < second_column.size(); i++)
    {
        if (checked[i] != 1 && temp[i] != second_column[i])
            unchecked.push_back(second_column[i]);
    }
    for (int i = 0; i < unchecked.size(); i++) {
        pi.push_back(unchecked[i]);
    }
    pi.erase(std::unique(pi.begin(), pi.end()), pi.end());

    cout << "The  Prime Implicants (PIs) are: " << endl;
    for (int i = 0; i < pi.size(); i++) {
        cout << pi[i] << endl;
    }

    vector<int> temp_pi;

    cout << "The  minterms of Prime Implicants are (correspondingly) : " << endl;
    for (int i = 0; i < pi.size(); i++) {
        unordered_set<int> pis;
        getMinterms(pis, pi[i], 0, n - 1); 
        for (int j = 0; j < total_decimal.size(); j++) {
            for (int element : pis) {
                if (element == total_decimal[j])
                    temp_pi.push_back(element);

            }
        }
        for (int element : pis)
            cout << element << "  ";
        cout << endl;
    }

// Finding EPIs 

    
    vector <int> temp_epi;

   for (int i = 0; i < pi.size(); i++) {
       unordered_set<int> mins;
       getMinterms(mins, pi[i], 0, n - 1); 
        for (int j = 0; j < minterms.size(); j++) {
           for (int element : mins) {
               if (element == minterms[j])
                   temp_epi.push_back(element);

           }
        }
    }

   unordered_map<int, int> freq;
   vector<int> not_covered, epi;

   for (int i = 0; i < temp_epi.size(); ++i) {
       if (freq.find(temp_epi[i]) == freq.end())
           freq[temp_epi[i]] = 1;
       else
           freq[temp_epi[i]]++;
   }

   for (pair<int, int> e : freq) {
       if (e.second == 1)
           epi.push_back(e.first);
       else
           not_covered.push_back(e.first);
   }

   cout << "EPIs are: " << endl;
   for (int i = 0; i < epi.size(); i++) {
       cout << epi[i] << endl;
   }

   cout << "The boolean expression of epis are: " << endl;
   for (int i = 0; i < epi.size(); i++)
       cout << get_exp(pad(decimalTobinary(epi[i]), n), expression_var) << endl;

   cout << "The minterms that are not covered by the essential PIs. are: " << endl;
   for (int i = 0; i < not_covered.size(); i++) {
       cout << not_covered[i] << endl;
   }

    return 0;
}

//generating the boolean expressions, for example: -11- becomes bc
string get_exp(string a, const vector <string> v)
{
    string temp = "";

    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] != '-')
        {
            if (a[i] == '0')
                temp = temp + v[i] + "\'";
            else
                temp = temp + v[i];
        }
    }
    return temp;
}
void getMinterms(unordered_set<int>& mins, string bin, int current, int index) {
    //001-01
    for (int i = index; i >= 0; --i) {
        if (bin[i] == '1') {
            current += pow(2, bin.length() - i - 1);
        }
        else if (bin[i] == '-') {
            bin[i] = '0';
            getMinterms(mins, bin, current, i);
            bin[i] = '1';
            getMinterms(mins, bin, current, i);
        }
    }
    if (mins.find(current) == mins.end())
        mins.insert(current);
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
