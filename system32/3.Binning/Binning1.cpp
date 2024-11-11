#include <iostream>
#include <bits/stdc++.h>
using namespace std;
vector<int> read_csv(string filename)
{
    vector<int> data;
    ifstream in1(filename);
    if (!in1)
    {
        cout << "Error opening File";
        return data;
    }
    string line;
    getline(in1, line);
    while (getline(in1, line))
    {
        data.push_back(stoi(line));
    }
    return data;
}
void write_csv(string filename, const vector<vector<int>> binned_data, const vector<vector<int>> &median_binned, const vector<vector<double>> &mean_binned, const vector<vector<int>> &boundaries_binned)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Error opening File";
    }
    file << "Bins - \n";
    for (int i = 0; i < binned_data.size(); i++)
    {
        file << "Bin" << i + 1 << ": ";
        for (auto val : binned_data[i])
        {
            file << val << " ";
        }
        file << "\n";
    }
    file << "\n";
    file << "Median Binning -\n";
    for (int i = 0; i < median_binned.size(); i++)
    {
        file << "Bin" << i + 1 << ": ";
        for (auto val : median_binned[i])
        {
            file << val << " ";
        }
        file << "\n";
    }
    file << "\n";
    file << "Mean Binning -\n";
    for (int i = 0; i < mean_binned.size(); i++)
    {
        file << "Bin" << i + 1 << ": ";
        for (auto val : mean_binned[i])
        {
            file << val << " ";
        }
        file << "\n";
    }
    file << "\n";
    file << "Boundaries Binning -\n";
    for (int i = 0; i < boundaries_binned.size(); i++)
    {
        file << "Bin" << i + 1 << ": ";
        for (auto val : boundaries_binned[i])
        {
            file << val << " ";
        }
        file << "\n";
    }
    file.close();
    cout << "Success: Result saved";
}
vector<vector<int>> create_bins(vector<int> data, int bins)
{

    int totalSize = data.size();
    int size = (totalSize / bins) + (totalSize % bins > 0);
    sort(data.begin(), data.end());
    vector<vector<int>> result;
    for (int i = 0; i < totalSize; i += size)
    {
        vector<int> tmp;
        int j = i;
        for (; j < min(totalSize, i + size); j++)
        {
            tmp.push_back(data[j]);
        }
        result.push_back(tmp);
    }
    for (auto res : result)
    {
        for (auto val : res)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    return result;
}
vector<vector<int>> binning_by_median(vector<int> data, int bins)
{
    int totalSize = data.size();
    int binsize = (totalSize / bins) + (totalSize % bins > 0);
    sort(data.begin(), data.end());
    vector<vector<int>> binned_data;
    for (int i = 0; i < totalSize; i += binsize)
    {
        vector<int> bin(data.begin() + i, data.begin() + min(i + binsize, totalSize));
        int median = bin[bin.size() / 2];
        vector<int> tmp(bin.size(), median);
        binned_data.push_back(tmp);
    }
    return binned_data;
}
vector<vector<double>> binning_by_mean(vector<int> data, int bins)
{
    int totalSize = data.size();
    int binsize = (totalSize / bins) + (totalSize % bins > 0);
    sort(data.begin(), data.end());
    vector<vector<double>> binned_data;
    for (int i = 0; i < totalSize; i += binsize)
    {
        vector<int> bin(data.begin() + i, data.begin() + min(i + binsize, totalSize));
        double mean = accumulate(bin.begin(), bin.end(), 0.0) / bin.size();
        vector<double> tmp(bin.size(), round(mean * 100) / 100);
        binned_data.push_back(tmp);
    }
    return binned_data;
}
vector<vector<int>> binning_by_boundaries(vector<int> data, int bins)
{
    int totalSize = data.size();
    int binsize = (totalSize / bins) + (totalSize % bins > 0);
    sort(data.begin(), data.end());
    vector<vector<int>> binned_data;
    for (int i = 0; i < totalSize; i += binsize)
    {
        vector<int> bin(data.begin() + i, data.begin() + min(i + binsize, totalSize));
        int mini = bin.front();
        int maxi = bin.back();
        vector<int> tmp;
        for (auto val : bin)
        {
            if (abs(val - mini) <= abs(val - maxi))
            {
                tmp.push_back(mini);
            }
            else
            {
                tmp.push_back(maxi);
            }
        }
        binned_data.push_back(tmp);
    }
    return binned_data;
}
int main()
{
    string filename = "input.csv";
    string output_file = "output.csv";
    int bins;
    cout << "Enter number of bins:";
    cin >> bins;
    vector<int> data = read_csv(filename);
    if (data.empty())
    {
        cerr << "Error: No data found or file could not be opened." << endl;
        return 1;
    }
    vector<vector<int>> binned_data = create_bins(data, bins);
    vector<vector<int>> median_binned = binning_by_median(data, bins);
    vector<vector<double>> mean_binned = binning_by_mean(data, bins);
    vector<vector<int>> boundaries_binned = binning_by_boundaries(data, bins);
    write_csv(output_file, binned_data, median_binned, mean_binned, boundaries_binned);
}