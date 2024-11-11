#include <bits/stdc++.h>
using namespace std;
vector<string> sub_classes;
map<string, int> mainClass;
map<string, unordered_set<string>> dist_val;
map<string, int> dist_val_count;
map<string, map<string, int>> val_count;
double maxGain = DBL_MIN;
string root = "null";
ofstream fw("output_gain.csv", ios::out);
void calculateGain(string subClass, double mainC_gain)
{
    double totR = mainClass["Yes"] + mainClass["No"];
    double ent = 0;
    for (auto dv : dist_val[subClass])
    {
        double tR = dist_val_count[dv];
        double pR = val_count[dv]["Yes"], nR = val_count[dv]["No"];
        if (pR != 0)
            ent += -(tR / totR) * ((pR / tR) * log2(pR / tR));
        if (nR != 0)
            ent += -(tR / totR) * ((nR / tR) * log2(nR / tR));
    }
    cout << "InfoGain ( " << subClass << "|" << "PlayGame ) : " << ent << "\n";
    fw << "InfoGain ( " << subClass << "|" << "PlayGame )," << ent << "\n";
    double gain = mainC_gain - ent;
    cout << "Gain ( " << subClass << "|" << "PlayGame ) : " << gain << "\n\n";
    fw << "Gain ( " << subClass << "|" << "PlayGame )," << gain << "\n";
    if (gain > maxGain)
    {
        maxGain = gain;
        root = subClass;
    }
}
int main()
{
    fstream file("input.csv", ios::in);
    string line, word;
    string Day, Outlook, Temp, Humidity, wind, PlayGame;
    if (!file.is_open())
    {
        perror("Error in opening input file : ");
        return -1;
    }
    int j = 0;
    string main_class = "PlayGame";
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, Day, ',');
        getline(str, Outlook, ',');
        getline(str, Temp, ',');
        getline(str, Humidity, ',');
        getline(str, wind, ',');
        getline(str, PlayGame, ',');
        if (j == 0)
        {
            j++;
            sub_classes.push_back(Day);
            sub_classes.push_back(Outlook);
            sub_classes.push_back(Temp);
            sub_classes.push_back(Humidity);
            sub_classes.push_back(wind);
            continue;
        }
        dist_val["Day"].insert(Day);
        dist_val["Outlook"].insert(Outlook);
        dist_val["Temp"].insert(Temp);
        dist_val["Humidity"].insert(Humidity);
        dist_val["Wind"].insert(wind);
        mainClass[PlayGame]++;
        dist_val_count[Day]++;
        dist_val_count[Outlook]++;
        dist_val_count[Temp]++;
        dist_val_count[Humidity]++;
        dist_val_count[wind]++;
        val_count[Day][PlayGame]++;
        val_count[Outlook][PlayGame]++;
        val_count[Temp][PlayGame]++;
        val_count[Humidity][PlayGame]++;
        val_count[wind][PlayGame]++;
    }
    double posR = mainClass["Yes"], negR = mainClass["No"];
    double totR = posR + negR;
    double mainC_gain = -((posR / totR) * log2(posR / totR) + (negR / totR) * log2(negR / totR));
    cout << "Main Class Gain : " << mainC_gain << "\n";
    for (int i = 1; i < 5; i++)
    {
        calculateGain(sub_classes[i], mainC_gain);
    }
    cout << "Subclass : " << root << " has maximum gain . Hence it will be selected as root for splitting.\n";
    fw << "Subclass : " << root << " has maximum gain . Hence it will be selected as root for splitting.\n";
    return 0;
}
