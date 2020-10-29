
#include <iostream>
#include <vector>

using namespace std;
void decimalTobinary(int var, vector<int> n, vector<vector <int>> &d){
    int k;
    for(int i = 0; i < n.size() ; i++)
    {    vector<int> temp;

        for(int j = var-1 ; j >= 0; j--)
        {
             k = n[i] >> j;
            if (k & 1)
                temp.push_back(1) ;
            else
                temp.push_back(0);
            
               //temp.push_back(n[i]%2);
                //n[i] = n[i]/2;
            

        }

        d.push_back(temp);

        
    }

}
int countones(vector<int> d){
    int count = 0;
    for (int i = 0; i < d.size(); i++){
        if (d[i] == 1){
            count++;
        }
    }
    return count;
}
void reorder(vector<vector<int>> &d, int var){
    vector<int> v;
   // int k = 0;
    //int a; //= 0;
    
    vector<int> v1;
    for(int i = 0; i < d.size(); i++)
    {
        for(int j = 0; j < var; j++){
            if(i == d.size() -1)
                break;
            v.push_back(d[i][j]);
            v1.push_back(d[i+1][j]);
            
   
        }
        
       
        if(countones(v) > countones(v1)){
           // vector<int> temp = d[i];
           // d[i] = d[i+1];
            //d[i+1] = temp;
            swap(d[i],d[i+1]);}
            v.clear();
            v1.clear();
        
    }
}

    




int main() {
   int var;
    cout << "input variables: ";
    cin >> var;
    vector<vector <int>> f;
    vector<vector <int>> e;

    vector<int> minterm;
    vector<int> dontcare;
    minterm.push_back(0);
    minterm.push_back(1);
    minterm.push_back(3);
    minterm.push_back(4);
    minterm.push_back(11);
    dontcare.push_back(5);

    vector<int> total;
  
    
   for(int f = 0; f < minterm.size(); f++){
       total.push_back(minterm[f]);
    }
    for(int g = 0; g < dontcare.size(); g++){
       total.push_back(dontcare[g]);
    }
    
    decimalTobinary(var,total, f);
   
           reorder(f, var);
  

    for(int i = 0; i < f.size(); i++)
    {
        for(int j = 0; j < var; j++){
        cout << f[i][j];
        }
       cout << endl;
    }
    
    return 0;
}
