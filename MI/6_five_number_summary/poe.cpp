#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double cal_median(vector<double>v)
{
    int n=v.size();
    return (n%2==0)?((v[(n/2)-1]+v[n/2])/2.0) : v[n/2];
}
int main()
{
    ifstream in("input.csv");
    vector<double>data;
    double value;
    while(in>>value)
    {
        data.push_back(value);
    }
    sort(data.begin(),data.end());
    cout<<"sorted data: ";
    for(auto it:data)
    cout<<it<<" ";
    cout<<"\n";
    double min,q1,median,q3,max;
    int n=data.size();
    min=data[0];
    max=data[n-1];
    median=cal_median(data);
    if(n%2==0)//even
    {
        vector<double>v(data.begin(),data.begin()+(n/2));
        q1=cal_median(v);
        vector<double>p(data.begin()+(n/2),data.end());
        q3=cal_median(p);
    }
    else
    {
        vector<double>v(data.begin(),data.begin()+(n/2));
        q1=cal_median(v);
        vector<double>p(data.begin()+(n/2)+1,data.end());
        q3=cal_median(p);
    }
    cout<<"min:"<<min<<"\n";
    cout<<"q1:"<<q1<<"\n";
    cout<<"median:"<<median<<"\n";
    cout<<"q3:"<<q3<<"\n";
    cout<<"max:"<<max<<"\n";
}