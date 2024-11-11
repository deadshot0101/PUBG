#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

vector<vector<int>> readCSV(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "File not found: " << filename << endl;
        exit(EXIT_FAILURE);
    }

 * @param filename The name of the CSV file to read.
 *
 * @return A 2D vector of integers.
 */
    vector<vector<int>> data;
    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        vector<int> row;
        getline(ss, value, ',');
        while (getline(ss, value, ','))
        {
            row.push_back(value[0] == 'Y' ? 1 : 0);
        }
        data.push_back(row);
    }
    return data;
}

double findPearsonCorrelation(const vector<vector<int>> &data, int cid1, int cid2)
{
    int n = data.size();
    int sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;

    for (int i = 0; i < n; ++i)
    {
        int x = data[i][cid1];
        int y = data[i][cid2];

        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
        sumY2 += y * y;
    }

    double numerator = (n * sumXY) - (sumX * sumY);
    double denominator = sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

    if (denominator == 0)
        return 0.0;
    return numerator / denominator;
}

void writeCSV(const string &filename, const vector<vector<string>> &data)
{
    ofstream file(filename);
    file << "cid-1,cid-2,Correlation coefficient,Type of correlation\n";
    for (const auto &row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i];
            if (i < row.size() - 1)
                file << ",";
        }
        file << "\n";
    }
}

int main()
{
    vector<vector<int>> data = readCSV("Correlation_Input.csv");
    int m = data[0].size();

    vector<vector<string>> output_data;

    cout << fixed << setprecision(16);
    for (int i = 0; i < m; ++i)
    {
        for (int j = i + 1; j < m; ++j)
        {
            double correlation = findPearsonCorrelation(data, i, j);
            string verdict = (correlation > 0) ? "Positive correlation" : (correlation < 0) ? "Negative correlation"
                                                                                            : "No relationship between entities";
            vector<string> row = {to_string(i + 1), to_string(j + 1), to_string(correlation), verdict};
            output_data.push_back(row);
        }
    }

    writeCSV("Correlation_Output.csv", output_data);
    cout << "Correlation data has been written to Correlation_Output.csv\n";
    return 0;
}
