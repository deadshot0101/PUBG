#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;
double calculateMean(const vector<double>& data) {
    double sum = 0;
    for (double val : data) {
        sum += val;
    }
    return sum / data.size();
}
double calculateStandardDeviation(const vector<double>& data, double mean) {
    double sum = 0;
    for (double val : data) {
        sum += pow(val - mean, 2);
    }
    return sqrt(sum / (data.size()));
}
double calculateCovariance(const vector<double>& data1, const vector<double>& data2, double mean1, double mean2) {
    double covariance = 0;
    for (int i = 0; i < data1.size(); ++i) {
        covariance += (data1[i] - mean1) * (data2[i] - mean2);
    }
    return covariance / (data1.size());
}
double calculateCorrelation(const vector<double>& data1, const vector<double>& data2) {
    double mean1 = calculateMean(data1);
    double mean2 = calculateMean(data2);
    double stddev1 = calculateStandardDeviation(data1, mean1);
    double stddev2 = calculateStandardDeviation(data2, mean2);
    double covariance = calculateCovariance(data1, data2, mean1, mean2);
    return covariance / (stddev1 * stddev2);
}
int main() {   
    ifstream file("corelation.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    vector<double> column1, column2;
    string line, value1, value2;
    getline(file,line);
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, value1, ',');  
        getline(ss, value2, ',');  
        column1.push_back(stod(value1)); 
        column2.push_back(stod(value2));
    }
    file.close();
    double correlation = calculateCorrelation(column1, column2);
    cout << "Correlation Coefficient: " << correlation << endl;
    return 0;
}
