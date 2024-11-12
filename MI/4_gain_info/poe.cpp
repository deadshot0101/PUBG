#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double cal_entropy(vector<string>classlable)
{
    map<string,double>freq;
    for(auto it:classlable)
    {
        freq[it]++;
    }
    double entropy=0.0,n=classlable.size();
    for(auto it:freq)
    {
        double p=(it.second)/n;
        entropy-=(p*log2(p));
    }
    return entropy;
}
double cal_cond_entropy(vector<string>attribute,vector<string>classlabel)
{
    map<string,vector<string>>subset;
    int n=classlabel.size(),i;
    for(i=0;i<n;i++)
    {
        subset[attribute[i]].push_back(classlabel[i]);
    }
    double cond_entropy=0.0;
    for(auto it:subset)
    {
        double subset_size=it.second.size();
        cond_entropy+=((subset_size/n)*cal_entropy(it.second));
    }
    return cond_entropy;
}
int main()
{
    ifstream in("input.csv");
    ofstream out("output.csv");
    string s;
    getline(in,s); //skip first line
    vector<string>outlook,temp,humidity,windy,classlable;
    while(getline(in,s))
    {
        stringstream ss(s);
        int i=0;
        string value;
        while(getline(ss,value,','))
        {
            if(i==0)
            outlook.push_back(value);
            if(i==1)
            temp.push_back(value);
            if(i==2)
            humidity.push_back(value);
            if(i==3)
            windy.push_back(value);
            if(i==4)
            classlable.push_back(value);
            i++;
        }
        
    }

    //entropy of classlable...i.e.->info(T)
    double info_T=cal_entropy(classlable);
    out<<"info(T):"<<info_T<<"\n";
    out<<"attribute,info(X T),Info_gain(X T)\n";

    double info_XT=cal_cond_entropy(outlook,classlable);
    out<<"outlook,"<<info_XT<<","<<info_T-info_XT<<"\n";

    info_XT=cal_cond_entropy(temp,classlable);
    out<<"temp,"<<info_XT<<","<<info_T-info_XT<<"\n";

    info_XT=cal_cond_entropy(humidity,classlable);
    out<<"humidity,"<<info_XT<<","<<info_T-info_XT<<"\n";

    info_XT=cal_cond_entropy(windy,classlable);
    out<<"windy,"<<info_XT<<","<<info_T-info_XT<<"\n";

    in.close();
    out.close();

}