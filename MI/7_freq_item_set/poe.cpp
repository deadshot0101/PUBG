#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double cal_support(vector<string>transactions,vector<int>itemset)
{
    double support=0;
    for(auto it:transactions)
    {
        bool valid=true;
        for(auto i:itemset)
        {
            if(it[i]=='0')
            {
                valid=false;
                break;
            }
        }
        if(valid)
        support++;
    }
    return support/transactions.size();
}
void generate_combination(int n,int size,int start,vector<int>&temp,vector<vector<int>>&combination)
{
    if(temp.size()==size)
    {
        combination.push_back(temp);
        return;
    }
    for(int i=start;i<n;i++)
    {
        temp.push_back(i);
        generate_combination(n,size,i+1,temp,combination);
        temp.pop_back();
    }
}
vector<vector<int>>cal_freq_itemset(vector<string>header,vector<string>transactions,double min_support)
{
    vector<vector<int>>ans;
    int n=transactions[0].size(); //n=no.of items
    for(int i=1;i<=n;i++)
    {
        vector<vector<int>>combination;
        vector<int>temp;
        generate_combination(n,i,0,temp,combination);
        for(auto it:combination) //cal support for each combinaation
        {
            cout<<"{";
            for(auto i:it)
            {
                cout<<header[i]<<" ";
            }
            cout<<"}: support=";
            double support=cal_support(transactions,it)*100;
            cout<<support<<"\n";
            if(support>=min_support)
            {
                ans.push_back(it);
            }
        }
    }
    return ans;
}
int main()
{
    ifstream in("transaction.csv");
    vector<string>header,transactions;
    string line;
    if (getline(in, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ','))
        {
            header.push_back(token);
        }
    }

    // Read transactions
    while (getline(in, line))
    {
        stringstream ss(line);
        string token, transaction = "";
        while (getline(ss, token, ','))
        {
            if (token == "TRUE")
                transaction += '1';
            else if (token == "FALSE")
                transaction += '0';
        }
        if (transaction != "")
            transactions.push_back(transaction);
    }
    double min_support;
    cout<<"enter min_support in percentage: ";
    cin>>min_support;
    vector<vector<int>>freq_itemset=cal_freq_itemset(header,transactions,min_support);

    //print final result
    cout<<"\n\nfreq itemsets:\n";
    for(auto it:freq_itemset)
    {
        cout<<"{";
        for(auto i:it)
        {
            cout<<header[i]<<" ";
        }
        cout<<"}\n";
    }
    in.close();
}