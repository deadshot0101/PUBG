#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

double mean(const vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

void linearRegression(const vector<double>& x, const vector<double>& y, double& m, double& b) {
    double x_mean = mean(x);
    double y_mean = mean(y);

    double numerator = 0.0;
    double denominator = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += (x[i] - x_mean) * (x[i] - x_mean);
    }

    m = numerator / denominator;
    b = y_mean - (m * x_mean);
}


void readCSV(const string& filename, vector<double>& x, vector<double>& y) {
    ifstream file(filename);
    string line, word;
    
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream s(line);
        double temp_x, temp_y;
        
        getline(s, word, ',');
        temp_x = stod(word);
        
        getline(s, word, ',');
        temp_y = stod(word);
        
        x.push_back(temp_x);
        y.push_back(temp_y);
    }
}

int main() {
    vector<double> x, y;
    string filename = "linear_regression_data.csv";  // Path to the CSV file

    
    readCSV(filename, x, y);

    if (x.size() != y.size() || x.empty()) {
        cout << "Error: Data in CSV file is inconsistent." << endl;
        return 1;
    }

    double m, b;
    linearRegression(x, y, m, b);

    cout << "Slope (m): " << m << endl;
    cout << "Intercept (b): " << b << endl;

    return 0;
}
