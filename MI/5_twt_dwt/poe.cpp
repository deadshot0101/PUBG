#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main()
{
    ifstream in("input.csv");
    ofstream out("output1.csv");
    vector<string>item;
    string line;
    getline(in,line); //skip first header line
    vector<vector<double>>data;
    while(getline(in,line))
    {
        vector<double>v;
        stringstream ss(line);
        int i=0;
        string value;
        while(getline(ss,value,','))
        {
            if(i==0)
            item.push_back(value);
            else
            v.push_back(stod(value));
            i++;
        }
        data.push_back(v);
    }

    int n=data.size(),i,j;
    out<<"item,state1,t-wt(state1),d-wt(state1),state2,t-wt(state2),d-wt(state2),both_state,t-wt(both_state),d-wt(both_state)\n";
    for(i=0;i<n;i++)
    {
        out<<item[0]<<",";
        for(j=0;j<n;j++)
        {
            out<<data[i][j]<<","<<(data[i][j]/data[i][n-1])*100<<","<<(data[i][j]/data[n-1][j])*100<<",";
        }
        out<<"\n";
    }
    in.close();
    out.close();

}