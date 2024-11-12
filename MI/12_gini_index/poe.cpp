#include <bits/stdc++.h>
#include <fstream>
using namespace std;
double cal_gini_index(vector<string> classlabel) {
    map<string, double> freq;
    for (auto &label : classlabel) {
        freq[label]++;
    }
    double gini = 1.0, n = classlabel.size();
    for (auto &it : freq) {
        double p = it.second / n;
        gini -= p * p;
    }
    return gini;
}
double cal_cond_gini_index(vector<string> attribute, vector<string> classlabel) {
    map<string, vector<string>> subsets;
    int n = classlabel.size();
    for (int i = 0; i < n; i++) {
        subsets[attribute[i]].push_back(classlabel[i]);
    }
    double cond_gini = 0.0;
    for (auto &subset : subsets) {
        double subset_size = subset.second.size();
        cond_gini += (subset_size / n) * cal_gini_index(subset.second);
    }
    return cond_gini;
}
int main() {
    ifstream in("input.csv");
    ofstream out("gini_output.csv");
    string s;
    getline(in, s); // skip first line
    vector<string> outlook, temp, humidity, windy, classlabel;

    while (getline(in, s)) {
        stringstream ss(s);
        int i = 0;
        string value;
        while (getline(ss, value, ',')) {
            if (i == 0) outlook.push_back(value);
            else if (i == 1) temp.push_back(value);
            else if (i == 2) humidity.push_back(value);
            else if (i == 3) windy.push_back(value);
            else if (i == 4) classlabel.push_back(value);
            i++;
        }
    }
    // Gini Index of classlabel
    double gini_T = cal_gini_index(classlabel);
    out << "Gini(T):" << gini_T << "\n";
    out << "attribute,Gini(X T),Reduction in Gini Index\n";
    double gini_XT = cal_cond_gini_index(outlook, classlabel);
    out << "outlook," << gini_XT << "," << gini_T - gini_XT << "\n";
    gini_XT = cal_cond_gini_index(temp, classlabel);
    out << "temp," << gini_XT << "," << gini_T - gini_XT << "\n";
    gini_XT = cal_cond_gini_index(humidity, classlabel);
    out << "humidity," << gini_XT << "," << gini_T - gini_XT << "\n";
    gini_XT = cal_cond_gini_index(windy, classlabel);
    out << "windy," << gini_XT << "," << gini_T - gini_XT << "\n";
    in.close();
    out.close();
}
