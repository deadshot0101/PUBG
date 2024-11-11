#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void calculate_entropy(map<string, int> parent, map<string, map<string, map<string, int>>> child)
{
    ofstream file("output.csv");
    double positive = parent["Yes"], negative = parent["No"];
    double total = positive + negative;
    double parent_entropy = -((positive / total) * log2(positive / total) + (negative / total) * log2(negative / total));
    cout << parent_entropy << endl;
    map<string, double> child_entropy;
    map<string, double> info_gain;
    file << "Parent Entropy," << parent_entropy << "\n";
    file << "Child Class,Entropy,InfoGain\n";
    for (auto subclass : child)
    {
        double child_ent = 0;
        for (auto value : subclass.second)
        {
            double scpos = child[subclass.first][value.first]["Yes"];
            double scneg = child[subclass.first][value.first]["No"];
            double subclass_total = scpos + scneg;
            child_ent += -((subclass_total) / total) * ((scpos > 0 ? ((scpos / subclass_total) * log2(scpos / subclass_total)) : 0) + (scneg > 0 ? ((scneg / subclass_total) * log2(scneg / subclass_total)) : 0));
        }
        child_entropy[subclass.first] = child_ent;
        info_gain[subclass.first] = parent_entropy - child_ent;
        file << subclass.first << "," << child_entropy[subclass.first] << "," << info_gain[subclass.first] << "\n";
    }
}
int main()
{
    ifstream file("input.csv");
    string line;
    string Day, Level, Routine, PlayGame, Value;
    map<string, int> parent;
    map<string, map<string, map<string, int>>> child;
    if (!file)
    {
        cout << "Error Opening File";
        exit(1);
    }
    getline(file, line);
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, Day, ',');
        getline(str, Level, ',');
        getline(str, Routine, ',');
        getline(str, PlayGame, ',');
        getline(str, Value, ',');
        parent[PlayGame]++;
        child["Level"][Level][PlayGame]++;
        child["Routine"][Routine][PlayGame]++;
        child["Value"][Value][PlayGame]++;
    }
    calculate_entropy(parent, child);
    return 0;
}