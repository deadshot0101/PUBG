#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ifstream file("input.csv");
    if (!file)
    {
        cout << "Error Opening File";
        exit(1);
    }
    string line;
    string col, row, count;
    map<string, map<string, int>> classrowcolmap;
    map<string, int> rowmap;
    map<string, int> colmap;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, row, ',');
        getline(str, col, ','); 
        getline(str, count, ',');
        int val = stoi(count);
        classrowcolmap[row][col] = val;
        rowmap[row] += val;
        colmap[col] += val;
    }
    int colSum = 0, rowSum = 0;
    for (auto c : colmap)
    {
        colSum += c.second;
    }
    for (auto r : rowmap)
    {
        rowSum += r.second;
    }
    ofstream out1("output.csv");
    out1 << "Column\\Row,BollyWood,,,TollyWood,,,Total\n";
    out1 << ",Count,t-weight,d-weight,Count,t-weight,d-weight,Count,t-weight,d-weight\n";
    for (auto r : rowmap)
    {
        row = r.first;
        out1 << row << ",";
        for (auto c : colmap)
        {
            col = c.first;
            int value = classrowcolmap[row][col];
            out1 << value << ",";
            out1 << fixed << setprecision(2) << ((float)value / rowmap[row]) * 100 << "%,";
            out1 << fixed << setprecision(2) << ((float)value / colmap[col]) * 100 << "%,";
        }
        out1 << rowmap[row] << ",";
        out1 << "100%,";
        out1 << fixed << setprecision(2) << ((float)rowmap[row] / rowSum) * 100 << "%\n";
    }
    out1 << "Total,";
    for (auto c : colmap)
    {
        col = c.first;
        out1 << colmap[col] << ",";
        out1 << fixed << setprecision(2) << ((float)colmap[col] / colSum) * 100 << "%,";
        out1 << "100%,";
    }
    out1 << colSum << ",100%,100%\n";
    out1.close();
    return 0;
}