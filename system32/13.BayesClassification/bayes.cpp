#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <numeric>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string line, word;
    ifstream file("exp13_input.csv");
    ofstream outfile("output.csv");
    if (!outfile.is_open())
    {
        cout << "Could not open output file\n";
        return 1;
    }

    string day, outlook, three, four, five, six;
    map<string, double> parent;
    map<string, map<string, map<string, double>>> child;
    int count = 0;
    vector<string> title;

    if (file.is_open())
    {
        int i = 0;
        while (getline(file, line))
        {
            stringstream str(line);
            if (i == 0)
            {
                string heading;
                while (getline(str, heading, ','))
                {
                    title.push_back(heading);
                }
                i++;
                continue;
            }
            vector<string> columns;
            while (getline(str, word, ','))
            {
                columns.push_back(word);
            }
            int n = columns.size();
            parent[columns[n - 1]]++;
            for (int i = 1; i < n - 1; i++)
            {
                child[title[i]][columns[i]][columns[n - 1]]++;
            }
            count++;
        }

        vector<string> resultclass;
        for (auto it : parent)
        {
            resultclass.push_back(it.first);
        }
        vector<double> output(resultclass.size(), 1);

        outfile << "Calculations for new instance:\n";
        for (auto it : child)
        {
            string input;
        again:
            cout << "Enter " << it.first << " condition: ";
            cin >> input;
            auto curr = child[it.first].find(input);
            if (curr == child[it.first].end())
            {
                cout << "No match, try again.\n";
                goto again;
            }
            for (int i = 0; i < resultclass.size(); i++)
            {
                double val = child[it.first][input][resultclass[i]] / parent[resultclass[i]];
                output[i] *= val;
                outfile << "P(" << it.first << "=" << input << " | " << resultclass[i] << ") = "
                        << child[it.first][input][resultclass[i]] << " / " << parent[resultclass[i]]
                        << " = " << val << "\n";
            }
        }

        outfile << "\nFinal Probabilities:\n";
        for (int i = 0; i < resultclass.size(); i++)
        {
            output[i] *= parent[resultclass[i]] / count;
            outfile << "P(" << resultclass[i] << " | New Instance) = " << output[i] << "\n";
        }

        double sum = accumulate(output.begin(), output.end(), 0.0);
        outfile << "\nNormalized Probabilities:\n";
        for (int i = 0; i < resultclass.size(); i++)
        {
            outfile << resultclass[i] << " = " << (output[i] / sum) * 100 << "%\n";
        }

        // Determine the class with the highest probability
        int max_index = max_element(output.begin(), output.end()) - output.begin();
        outfile << "\nNew Instance belongs to class: " << resultclass[max_index] << "\n";

        cout << "Results saved to output.csv\n";
    }
    else
    {
        cout << "Could not open the input file\n";
    }

    return 0;
}
