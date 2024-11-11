#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    double tmp, mini, maxi, new_mini, new_maxi;
    double sum = 0, cnt = 0, square_sum = 0, mean, standard_deviation;
    int opt;
    cout << "\nEnter option: \n1. Min-Max Normalization \n2. Z-Score Normalization\nOption: ";
    cin >> opt;

    if (opt == 1)
    {
        ifstream in1("input.csv");
        ofstream out1("output_MinMax.csv");
        if (!in1)
        {
            cout << "Error: Could not open input file for Min-Max normalization.";
            return 1;
        }
        if (!(in1 >> tmp))
        {
            cout << "Error: No data available in the file.";
            return 1;
        }
        mini = maxi = tmp;
        sum = tmp;
        cnt = 1;
        if (in1.fail())
        {
            cout << "Error: Non-numeric data encountered in the file. Program will exit." << endl;
            return 1;
        }
        while (in1 >> tmp)
        {

            if (in1.fail())
            {
                cout << "Error: Non-numeric data encountered in the file. Program will exit." << endl;
                return 1;
            }

            if (tmp > maxi)
                maxi = tmp;
            if (tmp < mini)
                mini = tmp;
            sum += tmp;
            cnt++;
        }

        in1.close();
        cout << mini << " " << maxi << " " << cnt << endl;

        if (maxi == mini)
        {
            cout << "Error: All values are the same, cannot perform Min-Max normalization.";
            return 1;
        }

        cout << "Enter new min: ";
        cin >> new_mini;
        cout << "Enter new max: ";
        cin >> new_maxi;

        if (new_mini == new_maxi)
        {
            cout << "Error: New min and max values cannot be the same for Min-Max normalization.";
            return 1;
        }

        in1.open("input.csv");
        if (!in1 || !out1)
        {
            cout << "Error: Could not reopen input file or open output file for writing.";
            return 1;
        }

        out1 << "Data,Normalized Data\n";
        out1 << fixed << setprecision(2);
        while (in1 >> tmp)
        {
            double normalized = (((tmp - mini) / (maxi - mini)) * (new_maxi - new_mini)) + new_mini;
            out1 << tmp << "," << normalized << "\n";
        }

        cout << "Min-Max normalization completed successfully.\n";
        in1.close();
        out1.close();
    }

    else if (opt == 2)
    {
        ifstream in3("input.csv");
        ofstream out2("output_ZScore.csv");

        if (!in3)
        {
            cout << "Error: Could not open input file for Z-Score normalization.";
            return 1;
        }

        while (in3 >> tmp)
        {
            sum += tmp;
            cnt++;
        }
        if (cnt <= 1)
        {
            cout << "Error: Not enough data points for Z-Score normalization.";
            return 1;
        }

        mean = sum / cnt;

        in3.clear();
        in3.seekg(0, ios::beg);
        while (in3 >> tmp)
        {
            square_sum += (tmp - mean) * (tmp - mean);
        }
        standard_deviation = sqrt(square_sum / (cnt - 1));

        if (standard_deviation == 0)
        {
            cout << "Error: Standard deviation is zero; data points are identical.";
            return 1;
        }

        in3.clear();
        in3.seekg(0, ios::beg);
        out2 << "Data,Z-Score Normalized Data\n";
        out2 << fixed << setprecision(2);
        while (in3 >> tmp)
        {
            double z_score = (tmp - mean) / standard_deviation;
            out2 << tmp << "," << z_score << "\n";
        }

        cout << "Z-Score normalization completed successfully.\n";
        in3.close();
        out2.close();
    }

    else
    {
        cout << "Invalid option! Please enter 1 or 2.";
    }
    return 0;
}
