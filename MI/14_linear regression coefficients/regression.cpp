#include <bits/stdc++.h>
#include <fstream>
using namespace std;
void calculateLinearRegression(const vector<double>& x, const vector<double>& y, double& b0, double& b1) {
    int n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    b1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    b0 = (sum_y - b1 * sum_x) / n;
}
int main() {
    vector<double> x, y;
    ifstream file("regression.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        double xi, yi;
            getline(ss, item, ',');
            xi = stod(item);
            getline(ss, item, ',');
            yi = stod(item); 
        x.push_back(xi);
        y.push_back(yi);
    }
    file.close();
    if (x.size() != y.size() || x.empty()) {
        cerr << "Mismatched x and y sizes or empty data." << endl;
        return 1;
    }
    double b0, b1;
    calculateLinearRegression(x, y, b0, b1);
    cout << "Calculated coefficients:" << endl;
    cout << "b0 (intercept) = " << b0 << endl;
    cout << "b1 (slope) = " << b1 << endl;
    return 0;
}
