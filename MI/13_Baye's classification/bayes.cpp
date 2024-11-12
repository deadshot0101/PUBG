#include<bits/stdc++.h>
#include<fstream>
using namespace std;
void calculateProbabilities(const vector<vector<string>> &data,map<string, int> &priorCounts,map<string, map<string, int>> &likelihoodCounts)
{
    for (const auto &row : data)
    {
        string outcome = row.back();
        priorCounts[outcome]++;

        for (int i = 0; i < row.size() - 1; ++i)
        {
            likelihoodCounts[outcome][row[i]]++;
        }
    }
}
string classify(const vector<string> &example,const map<string, int> &priorCounts,const map<string, map<string, int>> &likelihoodCounts,int totalSamples)
{
    double posteriorYes = (double)(priorCounts.at("Yes")) / totalSamples;
    double posteriorNo = (double)(priorCounts.at("No")) / totalSamples;
    cout << "Prior Probabilities:\n";
    cout << "P(Yes) = " << posteriorYes << "\n";
    cout << "P(No) = " << posteriorNo << "\n";
    for (const auto &feature : example)
    {
        double likelihoodYes = (likelihoodCounts.at("Yes").count(feature) ? (double)likelihoodCounts.at("Yes").at(feature) / priorCounts.at("Yes") : 0.0);
        double likelihoodNo = (likelihoodCounts.at("No").count(feature) ? (double)likelihoodCounts.at("No").at(feature) / priorCounts.at("No") : 0.0);
        posteriorYes *= likelihoodYes;
        posteriorNo *= likelihoodNo;
        cout << "For feature '" << feature << "':\n";
        cout << "P(" << feature << " | Yes) = " << likelihoodYes << "\n";
        cout << "P(" << feature << " | No) = " << likelihoodNo << "\n";
    }
    cout << fixed << setprecision(6);
    cout << "Final Probability P(Yes | D) = " << posteriorYes << "\n";
    cout << "Final Probability P(No | D) = " << posteriorNo << "\n";
    return (posteriorYes > posteriorNo) ? "Yes" : "No";
}
int main()
{
    ifstream file("bayes.csv");
    string line;
    vector<vector<string>> data;
    while (getline(file, line))
    {
        vector<string> tokens;
        string token;
        stringstream ss(line);
        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }
        data.push_back(tokens);
    }
    map<string, int> priorCounts;
    map<string, map<string, int>> likelihoodCounts;
    calculateProbabilities(data, priorCounts, likelihoodCounts);
    vector<string> example = {"Sunny", "Hot", "High", "FALSE"};
    int totalSamples = data.size();
    string result = classify(example, priorCounts, likelihoodCounts, totalSamples);
    cout << "Predicted: " << result << endl;
    return 0;
}
