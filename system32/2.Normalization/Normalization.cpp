#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    double tmp, mini, maxi, new_mini, new_maxi;
    double sum = 0, cnt = 0, square_sum = 0, mean = 0, standard_deviation;
    int opt;
    cout << "\nEnter Option: \n1.Min-Max Normalization \n2.Z-Score Normalization\nOption:";
    cin >> opt;
    if (opt == 1)
    {
        ifstream in1("input_MinMax.csv");
        ofstream out1("output_MinMax.csv");
        if (!in1)
        {
            cout << "Error Opening File";
            exit(1);
        }
        string line;
        getline(in1, line);
        getline(in1, line);
        tmp = stoi(line);
        mini = tmp;
        maxi = tmp;
        while (getline(in1, line))
        {
            double curr = stoi(line);
            mini = min(mini, curr);
            maxi = max(maxi, curr);
        }
        cout << mini << " " << maxi << endl;

        in1.close();
        cout << "Enter New Min:";
        cin >> new_mini;
        cout << "Enter New Max:";
        cin >> new_maxi;
        in1.open("input_MinMax.csv");
        out1 << "Data,Normalized Data\n";
        getline(in1, line);
        while (getline(in1, line))
        {
            double num = stoi(line);
            double tmp2 = ((num - mini) / (maxi - mini)) * (new_maxi - new_mini) + new_mini;
            out1 << fixed << setprecision(2) << num << "," << tmp2 << "\n";
        }
        in1.close();
        out1.close();
    }
    else if (opt == 2)
    {
        ifstream in1("input_ZScore.csv");
        ofstream out1("output_ZScore.csv");
        if (!in1)
        {
            cout << "Error Opening File";
            exit(1);
        }
        string line;
        vector<double> nums;
        getline(in1, line);
        while (getline(in1, line))
        {
            double num = stoi(line);
            nums.push_back(num);
            sum += num;
            cnt++;
        }
        mean = sum / (cnt * 1.0);
        for (int i = 0; i < nums.size(); i++)
        {
            square_sum += (nums[i] - mean) * (nums[i] - mean);
        }
        standard_deviation = sqrt(square_sum / cnt);
        out1 << "Data,Z-Score Normalized Data\n";
        for (int i = 0; i < nums.size(); i++)
        {
            double tmp = (nums[i] - mean) / standard_deviation;
            out1 << fixed << setprecision(2) << nums[i] << "," << tmp << "\n";
        }
        in1.close();
        out1.close();
    }
    else
    {
        cout << "Wrong Option";
    }
    return 0;
}