#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> data;
vector<string> split(string &currRow, char delimiter)
{
    vector<string> tokens;
    string token;
    stringstream ss(currRow);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
void readCSV(string &filename, bool hasHeader)
{
    ifstream fileObj(filename);
    if (!fileObj.is_open())
    {
        cout << "Error opening a file!!" << endl;
        return;
    }
    string row;
    if (hasHeader and getline(fileObj, row))
    {
        vector<string> currRow = split(row, ',');
        cout << "Header:";
        for (auto &col : currRow)
        {
            cout << col << "|";
        }
        cout << endl;
    }
    while (getline(fileObj, row))
    {
        vector<string> currRow = split(row, ',');
        vector<int> tmp;
        for (int i = 0; i < currRow.size(); i++)
        {
            tmp.push_back(stoi(currRow[i]));
        }
        data.push_back(tmp);
    }
    vector<int> x;
    vector<int> y;
    vector<int> xy;
    vector<int> xsquare;
    int sumx = 0, sumxy = 0, xsquaresum = 0, sumy = 0;
    for (auto row : data)
    {
        // row - x, y
        int x1 = row[0], y1 = row[1];
        xy.push_back(x1 * y1);
        xsquare.push_back(x1 * x1);
        x.push_back(x1);
        y.push_back(y1);
        sumx += x1;
        sumy += y1;
        sumxy += (x1 * y1);
        xsquaresum += (x1 * x1);
    }
    int n = data.size();
    double m = (n * (sumxy)-sumx * sumy) / (1.0 * n * xsquaresum - (sumx * sumx));
    double c = (sumy * xsquaresum - sumx * sumxy) / (1.0 * n * xsquaresum - (sumx * sumx));
    cout << m << " " << c << endl;
    fileObj.close();
}
int main()
{
    string inp = "inp.csv";
    readCSV(inp, true);
    return 0;
}
