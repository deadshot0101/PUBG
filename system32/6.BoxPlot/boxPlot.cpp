#include <bits/stdc++.h>
using namespace std;

float median(vector<float> v)
{
    int n = v.size();
    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[(n / 2) - 1] + v[n / 2]) / 2.0;
}

float quartile1(vector<float> v)
{
    vector<float> firstHalf(v.begin(), v.begin() + v.size() / 2);
    return median(firstHalf);
}

float quartile3(vector<float> v)
{
    int n = v.size();
    vector<float> secondHalf;
    if (n % 2 == 0)
    {
        secondHalf = vector<float>(v.begin() + n / 2, v.end());
    }
    else
    {
        secondHalf = vector<float>(v.begin() + n / 2 + 1, v.end());
    }
    return median(secondHalf);
}

float calculateIQR(float q1, float q3)
{
    return q3 - q1;
}

pair<float, float> calculateBounds(float q1, float q3, float iqr)
{
    float lowerBound = q1 - 1.5 * iqr;
    float upperBound = q3 + 1.5 * iqr;
    return {lowerBound, upperBound};
}

pair<float, float> findWhiskers(vector<float> v, float lowerBound, float upperBound)
{
    float lowerWhisker = v[0];
    float upperWhisker = v.back();

    for (float val : v)
    {
        if (val >= lowerBound)
        {
            lowerWhisker = val;
            break;
        }
    }
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] <= upperBound)
        {
            upperWhisker = v[i];
            break;
        }
    }
    return {lowerWhisker, upperWhisker};
}

vector<float> findOutliers(vector<float> v, float lowerBound, float upperBound)
{
    vector<float> outliers;
    for (float val : v)
    {
        if (val < lowerBound || val > upperBound)
        {
            outliers.push_back(val);
        }
    }
    return outliers;
}

int main()
{
    ifstream in("input.csv");
    if (!in.is_open())
    {
        cout << "Couldn't open file";
        exit(0);
    }
    ofstream out("output.csv");
    int i = 0;
    string line, mark;
    vector<float> arr;
    while (getline(in, line))
    {
        if (i == 0)
        {
            i++;
            continue;
        }
        stringstream str(line);
        getline(str, mark, ',');
        int x = stoi(mark);
        arr.push_back(x);
    }
    sort(arr.begin(), arr.end());

    float minValue = arr.front();
    float maxValue = arr.back();
    float q1 = quartile1(arr);
    float q2 = median(arr);
    float q3 = quartile3(arr);
    float iqr = calculateIQR(q1, q3);

    pair<float, float> bounds = calculateBounds(q1, q3, iqr);
    float lowerBound = bounds.first;
    float upperBound = bounds.second;

    pair<float, float> whiskers = findWhiskers(arr, lowerBound, upperBound);
    float lowerWhisker = whiskers.first;
    float upperWhisker = whiskers.second;

    vector<float> outliers = findOutliers(arr, lowerBound, upperBound);

    out << "Minimum value: " << minValue << "\n";
    out << "Quartile1 (Q1) value: " << q1 << "\n";
    out << "Median (Q2) value: " << q2 << "\n";
    out << "Quartile3 (Q3) value: " << q3 << "\n";
    out << "Maximum value: " << maxValue << "\n";
    out << "IQR: " << iqr << "\n";
    out << "Lower Whisker: " << lowerWhisker << "\n";
    out << "Upper Whisker: " << upperWhisker << "\n";
    out << "Outliers: ";
    for (float outlier : outliers)
    {
        out << outlier << " ";
    }
    out << "\n";

    cout << "Minimum value: " << minValue << endl;
    cout << "Q1: " << q1 << endl;
    cout << "Median: " << q2 << endl;
    cout << "Q3: " << q3 << endl;
    cout << "Maximum value: " << maxValue << endl;
    cout << "IQR: " << iqr << endl;
    cout << "Lower Whisker: " << lowerWhisker << endl;
    cout << "Upper Whisker: " << upperWhisker << endl;
    cout << "Outliers: ";
    for (float outlier : outliers)
    {
        cout << outlier << " ";
    }
    cout << endl;

    return 0;
}
