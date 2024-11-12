#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double cal_support(vector<string>transactions,vector<int>itemset)
{
    double support=0,n=transactions.size();
    for(auto tran:transactions)
    {
        int valid=1;
        for(auto it:itemset)
        {
            if(tran[it]=='0')
            {
                valid=0;
                break;
            }
        }
        if(valid)
        support+=1;
    }
    
    return support/n;
}
void generate_combination(int n,int k,int st,vector<vector<int>>&combination,vector<int>&curr)
{
    if(curr.size()==k)
    {
        combination.push_back(curr);
        return;
    }
    for(int i=st;i<n;i++)
    {
        curr.push_back(i);
        generate_combination(n,k,i+1,combination,curr);
        curr.pop_back();
    }
}
vector<vector<int>>generate_freq_itemset(vector<string>transactions,vector<string>header,double min_support)
{
    vector<vector<int>>ans;
    int n=transactions[0].size(); //total items
    for(int i=1;i<=n;i++)
    {
        vector<vector<int>>combination;
        vector<int>curr;
        generate_combination(n,i,0,combination,curr);
        for(auto itemset:combination)
        {
            cout<<"{";
            for(auto i:itemset)
            cout<<header[i]<<" ";
            cout<<"}-> support:";
            double support=cal_support(transactions,itemset)*100;
            cout<<support<<"\n";
            if(support>=min_support)
            ans.push_back(itemset);

        }
    }
    return ans;
}
void generate_subset(int st,vector<int>itemset,vector<vector<int>>&subset,vector<int>&curr)
{
    if(!curr.empty())
    {
        subset.push_back(curr);
        return;
    }
    for(int i=st;i<itemset.size();i++)
    {
        curr.push_back(itemset[i]);
        generate_subset(i+1,itemset,subset,curr);
        curr.pop_back();
    }
}
vector<int>find_remaining_set(vector<int>subset,vector<int>itemset)
{
    vector<int>ans;
    for(auto it:itemset)
    {
        if(find(subset.begin(),subset.end(),it)==subset.end())
        ans.push_back(it);
    }
    return ans;
}
void find_association_rule(vector<vector<int>>freq_itemset,vector<string>transactions,vector<string>header,double min_confidence)
{
    for(auto itemset:freq_itemset) //for each itemset->generate all nonempty subset  rule:(subset->remaining)
    {
        vector<vector<int>>subsets;
        vector<int>curr;
        generate_subset(0,itemset,subsets,curr);
        //find remain set for each subset
        for(auto subset:subsets)
        {
            if(subset.size()==itemset.size()) //--> no remaining set
            continue;
            vector<int>remaining_set=find_remaining_set(subset,itemset);
            cout<<"rule:{";
            for(auto it:subset)
            {
                cout<<header[it]<<" ";
            }
            cout<<"}->{";
            for(auto it:remaining_set)
            {
                cout<<header[it]<<" ";
            }
            cout<<"} confidence=";
            double confidence=(cal_support(transactions,itemset)/cal_support(transactions,subset))*100;
            cout<<confidence;
            if(confidence>=min_confidence)
            {
                cout<<" valid rule\n";
            }
            else
            {
                cout<<" invalid rule\n";
            }
        }
    }
}
int main()
{
    ifstream in("transaction.csv");
    vector<string>header,transactions;
    string line;
    if(getline(in,line))
    {
        stringstream ss(line);
        string col_name;
        while(getline(ss,col_name,','))
        {
            header.push_back(col_name);
        }
    }
    while(getline(in,line))
    {
        stringstream ss(line);
        string tran="",s;
        while(getline(ss,s,','))
        {
            if(s=="TRUE")
                tran+='1';
            else if(s=="FALSE")
                tran+='0';
        }
        if(tran!="")
        transactions.push_back(tran);

    }
    cout<<"enter min_support value: ";
    double min_support;
    cin>>min_support;
    vector<vector<int>>freq_itemset=generate_freq_itemset(transactions,header,min_support);
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


    //association rule:
    double min_confidence;
    cout<<"\n\n\nassociation rule calculation start\nenter min_confidence:";
    cin>>min_confidence;
    find_association_rule(freq_itemset,transactions,header,min_confidence);

    in.close();
}