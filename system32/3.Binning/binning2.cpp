#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <bits/stdc++.h>
using namespace std;
vector<int> read_csv(const string &file_name)
{
    vector<int> data;
    ifstream file(file_name);
    string line;

    if (file.is_open())
    {
        getline(file, line); // Skip header line
        while (getline(file, line))
        {
            try
            {
                data.push_back(stoi(line));
            }
            catch (const invalid_argument &e)
            {
                cerr << "Warning: Non-integer value encountered, skipping line." << endl;
            }
        }
        file.close();
    }
    else
    {
        cerr << "Error: Could not open the file." << endl;
    }

    return data;
}

void write_to_file(const string &file_name, const vector<int> &median_binned, const vector<double> &mean_binned, const vector<int> &boundaries_binned)
{
    ofstream file(file_name);
    if (file.is_open())
    {
        file << "Median Binning - ";
        for (const int &value : median_binned)
        {
            file << value << " ";
        }
        file << "\n";

        file << "Mean Binning - ";
        for (const double &value : mean_binned)
        {
            file << value << " ";
        }
        file << "\n";

        file << "Boundaries Binning - ";
        for (const int &value : boundaries_binned)
        {
            file << value << " ";
        }
        file << "\n";

        file.close();
        cout << "Success: Results saved to " << file_name << endl;
    }
    else
    {
        cerr << "Error: Could not write to file " << file_name << endl;
    }
}

vector<int> binning_by_median(vector<int> data, int bin_size)
{
    if (bin_size <= 0)
    {
        cerr << "Error: Bin size must be a positive integer." << endl;
        return data;
    }
    if (bin_size > data.size())
    {
        cerr << "Warning: Bin size larger than data size, adjusting to data size." << endl;
        bin_size = data.size();
    }

    sort(data.begin(), data.end());
    vector<int> binned_data;

    for (size_t i = 0; i < data.size(); i += bin_size)
    {
        vector<int> bin_data(data.begin() + i, data.begin() + min(i + bin_size, data.size()));
        int median = bin_data[bin_data.size() / 2];
        binned_data.insert(binned_data.end(), bin_data.size(), median);
    }

    return binned_data;
}

vector<double> binning_by_mean(vector<int> data, int bin_size)
{
    if (bin_size <= 0)
    {
        cerr << "Error: Bin size must be a positive integer." << endl;
        return vector<double>(data.begin(), data.end());
    }
    if (bin_size > data.size())
    {
        cerr << "Warning: Bin size larger than data size, adjusting to data size." << endl;
        bin_size = data.size();
    }

    sort(data.begin(), data.end());
    vector<double> binned_data;

    for (size_t i = 0; i < data.size(); i += bin_size)
    {
        vector<int> bin_data(data.begin() + i, data.begin() + min(i + bin_size, data.size()));
        double mean = accumulate(bin_data.begin(), bin_data.end(), 0.0) / bin_data.size();
        binned_data.insert(binned_data.end(), bin_data.size(), round(mean * 100) / 100);
    }

    return binned_data;
}

vector<int> binning_by_boundaries(vector<int> data, int bin_size)
{
    if (bin_size <= 0)
    {
        cerr << "Error: Bin size must be a positive integer." << endl;
        return data;
    }
    if (bin_size > data.size())
    {
        cerr << "Warning: Bin size larger than data size, adjusting to data size." << endl;
        bin_size = data.size();
    }

    sort(data.begin(), data.end());
    vector<int> binned_data;

    for (size_t i = 0; i < data.size(); i += bin_size)
    {
        vector<int> bin_data(data.begin() + i, data.begin() + min(i + bin_size, data.size()));
        int min_val = bin_data.front();
        int max_val = bin_data.back();
        for (const int &value : bin_data)
        {
            if (abs(value - min_val) < abs(value - max_val))
            {
                binned_data.push_back(min_val);
            }
            else
            {
                binned_data.push_back(max_val);
            }
        }
    }

    return binned_data;
}

int main()
{
    string file_name = "input.csv";
    string output_file = "output.csv";

    int bin_size;
    cout << "Enter the number of bins: ";
    cin >> bin_size;

    vector<int> data = read_csv(file_name);

    if (data.empty())
    {
        cerr << "Error: No data found or file could not be opened." << endl;
        return 1;
    }

    vector<int> median_binned = binning_by_median(data, bin_size);
    vector<double> mean_binned = binning_by_mean(data, bin_size);
    vector<int> boundaries_binned = binning_by_boundaries(data, bin_size);

    write_to_file(output_file, median_binned, mean_binned, boundaries_binned);
    return 0;
}
