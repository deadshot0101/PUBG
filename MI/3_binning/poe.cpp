#include<bits/stdc++.h>
#include<fstream>
using namespace std;
vector<vector<double>> partion_equidepth(vector<double>data,int binsize)
{
    vector<vector<double>>v;
    int i=0;
    vector<double>p;
    for(auto it:data)
    {
        if(i==binsize)
        {
            i=0;
            v.push_back(p);
            p.clear();
        }
        p.push_back(it);
        i++;
    }
    if (!p.empty())
    {
        v.push_back(p);
    }
    return v;
}
vector<vector<double>> partion_equiwidth(vector<double>data,int total_bin)
{
    double min=data[0],max=data[data.size()-1];
    double binwidth=(max-min)/total_bin;
    vector<vector<double>> bins(total_bin);
    for(int i=0;i<total_bin;i++)
    {
        double lower=min+i*binwidth;
        double upper=lower+binwidth;
        for(auto value:data)
        {
            if(value>=lower&&value<upper)
            bins[i].push_back(value);
            else if(i==total_bin-1&&value==upper)
            bins[i].push_back(value);
        }
    }
    return bins;
    
}
vector<vector<double>>smoothing_mean(vector<vector<double>>bins)
{
    vector<vector<double>>v;
    
    for(auto bin:bins)
    {
        double mean=0;
        for(auto it:bin)
        {
            mean+=it;
        }
        mean/=(bin.size());
        vector<double>p;
        for(auto it:bin)
        {
            p.push_back(mean);
        }
        v.push_back(p);
        
    }
    return v;
}

vector<vector<double>>smoothing_median(vector<vector<double>>bins)
{
    vector<vector<double>>v;
    for(auto bin:bins)
    {
        int n=bin.size();
        double median=(n%2==0)?(bin[n/2-1]+bin[n/2])/2.0 : bin[n/2];
        vector<double>p;
        for(auto it:bin)
        {
            p.push_back(median);
        }
        v.push_back(p);
        
    }
    return v;
}

vector<vector<double>>smoothing_boundaries(vector<vector<double>>bins)
{
    vector<vector<double>>v;
    for(auto bin:bins)
    {
        double low=bin[0],high=bin[bin.size()-1];
        vector<double>p;
        for(auto it:bin)
        {
            double val=(abs(it-low)<abs(it-high))?low:high;
            p.push_back(val);
        }
        v.push_back(p);
    }
    return v;
}
int main()
{
    ifstream in("input.csv");
    vector<double>data;
    double val;
    while(in>>val)
    {
        data.push_back(val);
    }
    sort(data.begin(),data.end());
    int choice;
    cout<<"enter option 1 or 2:\n 1:partion into equidepth\n 2:partion into equiwidth\n";
    cin>>choice;
    vector<vector<double>>bins;
    if(choice==1)
    {
        int binsize;
        cout<<"enter bin size:";
        cin>>binsize;
        bins=partion_equidepth(data,binsize);
        for(auto it:bins)
        {
            cout<<"bin :";
            for(auto i:it)
            cout<<i<<" ";
            cout<<"\n";
        }
    }
    else
    {
        int total_bin;
        cout<<"enter total bins no. :";
        cin>>total_bin;
        bins=partion_equiwidth(data,total_bin);
        for(auto it:bins)
        {
            cout<<"bin :";
            for(auto i:it)
            cout<<i<<" ";
            cout<<"\n";
        }
    }

    
    vector<vector<double>>smooth_mean=smoothing_mean(bins);
    vector<vector<double>>smooth_median=smoothing_median(bins);
    vector<vector<double>>smooth_boundaries=smoothing_boundaries(bins);

    cout<<"\nsmoothing by mean:\n";
    for(auto it:smooth_mean)
    {
        cout<<"bin: ";
        for(auto i:it)
        cout<<i<<" ";
        cout<<"\n";
    }

    cout<<"\nsmoothing by median:\n";
    for(auto it:smooth_median)
    {
        cout<<"bin: ";
        for(auto i:it)
        cout<<i<<" ";
        cout<<"\n";
    }

    cout<<"\nsmoothing by boundaries:\n";
    for(auto it:smooth_boundaries)
    {
        cout<<"bin: ";
        for(auto i:it)
        cout<<i<<" ";
        cout<<"\n";
    }

}