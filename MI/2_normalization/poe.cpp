#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double min_max_normalization(double val,double new_min,double new_max,double min,double max)
{
    return (((val-min)/(max-min))*(new_max-new_min))+new_min;
}

double z_score_normalization(double val,double mean,double sd)
{
    return (val-mean)/sd;
}
int main()
{
    ifstream in("input.csv");
    ofstream out("output.csv");
    vector<double>data;
    double val;
    while(in>>val)
    {
        data.push_back(val);
    }
    sort(data.begin(),data.end());
    double min=data[0];
    double max=data[data.size()-1];
    double new_max,new_min;
    cout<<"enter values for new_max and new_min\n";
    cin>>new_max>>new_min;
    // z-score
    //mean,sd
    double mean=0,sd=0;
    int n=data.size();
    for(auto val:data)
    {
        mean+=val;
    }
    mean/=n;
    for(auto val:data)
    {
        sd+=((val-mean)*(val-mean));
    }
    sd/=n;
    sd=sqrt(sd);
    //printing result in output.csv
    out<<"value,min_max,z-score\n";
    for(auto val:data)
    {
        out<<val<<","<<min_max_normalization(val,new_min,new_max,min,max)<<","<<z_score_normalization(val,mean,sd)<<"\n";
    }
    in.close();
    out.close();
}