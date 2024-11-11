#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

double calculateGiniIndex(const vector<string> &data, const string &attribute, const string &target)
{
    map<string, map<string, int>> counts;

    for (const string &row : data)
    {
        stringstream ss(row);
        string value;
        vector<string> rowData;

        while (getline(ss, value, ','))
        {
            rowData.push_back(value);
        }

                string targetValue = rowData.back();
        int attributeIndex = (attribute == "Outlook") ? 0 : (attribute == "Temp")   ? 1
                                                        : (attribute == "Humidity") ? 2
                                                        : (attribute == "Wind")     ? 3
                                                                                    : -1;

        if (attributeIndex != -1)
        {
            counts[rowData[attributeIndex]][targetValue]++;
        }
    }

    double giniIndex = 0.0;

    for (const auto &outer : counts)
    {
        double total = 0;
        double pYes = 0;
        double pNo = 0;

        for (const auto &inner : outer.second)
        {
            total += inner.second;
            if (inner.first == "Yes")
            {
                pYes += inner.second;
            }
            else if (inner.first == "No")
            {
                pNo += inner.second;
            }
        }

        if (total == 0)
            continue;

        pYes /= total;
        pNo /= total;

        giniIndex += (1 - (pYes * pYes + pNo * pNo)) * (total / data.size());
    }

    return giniIndex;
}

int main()
{
    ifstream inputFile("giniinput.csv");
    ofstream outputFile("ginioutput.csv");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Error opening files!" << endl;
        return 1;
    }
    string line;
    vector<string> data;
    while (getline(inputFile, line))
    {
        if (!line.empty())
        {
            data.push_back(line);
        }
    }

    data.erase(data.begin());
    vector<string> attributes = {"Outlook", "Temp", "Humidity", "Wind"};

    for (const string &attribute : attributes)
    {
        double giniIndex = calculateGiniIndex(data, attribute, "PlayGame");
        outputFile << attribute << ": " << giniIndex << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Gini Index calculations are complete. Check output.txt for results." << endl;

    return 0;
}
