#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
using namespace std;

int main()
{
    ifstream file("input.csv");
    if (!file)
    {
        cout << "Error Opening File";
        return 1;
    }
    string line, col, row, count;
    map<string, map<string, int>> classrowcolmap;
    map<string, int> rowmap;
    map<string, int> colmap;
    set<string> rows; // To store unique row names
    set<string> cols; // To store unique column names
    getline(file, line);
    // Parse the file data
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
        rows.insert(row);
        cols.insert(col);
    }
    // Calculate column and row sums
    int colSum = 0, rowSum = 0;
    for (auto &c : colmap)
        colSum += c.second;
    for (auto &r : rowmap)
        rowSum += r.second;
    // Open output file
    ofstream out1("output.csv");
    // Dynamically write the header
    out1 << "Column\\Row";
    for (const auto &col : cols)
    {
        out1 << "," << col << ",t-weight,d-weight";
    }
    out1 << ",Total\n";
    out1 << ",";
    for (size_t i = 0; i < cols.size(); ++i)
    {
        out1 << "Count,t-weight,d-weight,";
    }
    out1 << "Count,t-weight,d-weight\n";
    // Write the data for each row
    for (const auto &row : rows)
    {
        out1 << row << ","; // Row name
        for (const auto &col : cols)
        {
            int value = classrowcolmap[row][col]; // Get value for current row and column
            // Write Count, t-weight, and d-weight
            out1 << value << ",";
            out1 << fixed << setprecision(2) << ((float)value / rowmap[row]) * 100 << "%,  "; // t-weight
            out1 << fixed << setprecision(2) << ((float)value / colmap[col]) * 100 << "%,  "; // d-weight
        }
        // Row totals and percentages
        out1 << rowmap[row] << ",  ";                                                       // Total for the row
        out1 << "100%,  ";                                                                  // t-weight for row total
        out1 << fixed << setprecision(2) << ((float)rowmap[row] / rowSum) * 100 << "%\n"; // d-weight for row total
    }
    // Write the column totals
    out1 << "Total,";
    for (const auto &col : cols)
    {
        out1 << colmap[col] << ",";                                                      // Column total count
        out1 << fixed << setprecision(2) << ((float)colmap[col] / colSum) * 100 << "%,"; // d-weight for column total
        out1 << "100%,";
    }
    out1 << colSum << ",100%,100%\n"; // Total counts and 100% for final totals
    out1.close();
    return 0;
}
