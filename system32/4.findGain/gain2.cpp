    #include <bits/stdc++.h>
    using namespace std;

    // Function to calculate child entropy for a given attribute
    double child_entropy(int total, const map<string, map<string, int>> &child, const string &positiveLabel, const string &negativeLabel)
    {
        double entropy = 0;
        for (const auto &p : child)
        {
            int pr = 0, nr = 0;
            if (p.second.find(positiveLabel) != p.second.end())
                pr = p.second.at(positiveLabel);
            if (p.second.find(negativeLabel) != p.second.end())
                nr = p.second.at(negativeLabel);
            int tr = pr + nr;
            if (tr > 0)
            {
                if (pr > 0)
                {
                    entropy += -(pr / (double)total) * log2(pr / (double)tr);
                }
                if (nr > 0)
                {
                    entropy += -(nr / (double)total) * log2(nr / (double)tr);
                }
            }
        }
        return entropy;
    }

    int main()
    {
        ifstream fs("input.csv");
        string line;

        vector<string> attributes;
        map<string, map<string, map<string, int>>> attributeValues;
        map<string, int> parent;

        // Read the header to dynamically get attribute names
        if (getline(fs, line))
        {
            stringstream str(line);
            string attr;
            while (getline(str, attr, ','))
            {
                attributes.push_back(attr);
            }
        }

        // Prompt user to enter the target attribute (class attribute)
        string targetAttribute;
        cout << "Enter the name of the class attribute: ";
        cin >> targetAttribute;

        // Validate target attribute in header
        auto targetIt = find(attributes.begin(), attributes.end(), targetAttribute);
        if (targetIt == attributes.end())
        {
            cerr << "Error: Class attribute \"" << targetAttribute << "\" not found in data file header." << endl;
            return -1;
        }
        int classIndex = distance(attributes.begin(), targetIt);

        // Prompt the user for positive and negative class labels
        string positiveLabel, negativeLabel;
        cout << "Enter the label for the positive class (e.g., Yes, Play, True): ";
        cin >> positiveLabel;
        cout << "Enter the label for the negative class (e.g., No, False): ";
        cin >> negativeLabel;

        // Process each line of data
        while (getline(fs, line))
        {
            stringstream str(line);
            vector<string> values;
            string value;

            while (getline(str, value, ','))
            {
                values.push_back(value);
            }

            if (values.size() != attributes.size())
            {
                cerr << "Warning: Data line has mismatched attribute count. Skipping line.\n";
                continue;
            }

            string classLabel = values[classIndex];
            parent[classLabel]++;

            for (size_t j = 0; j < attributes.size(); ++j)
            {
                if (j != classIndex)
                    attributeValues[attributes[j]][values[j]][classLabel]++;
            }
        }

        int pos = parent[positiveLabel], neg = parent[negativeLabel];
        int total = pos + neg;

        double parentEntropy = 0;
        if (pos > 0)
            parentEntropy -= (pos / (double)total) * log2(pos / (double)total);
        if (neg > 0)
            parentEntropy -= (neg / (double)total) * log2(neg / (double)total);

        map<string, double> entropies, infoGains;
        for (const auto &attr : attributes)
        {
            if (attr != targetAttribute)
            {
                double entropy = child_entropy(total, attributeValues[attr], positiveLabel, negativeLabel);
                entropies[attr] = entropy;
                infoGains[attr] = parentEntropy - entropy;
            }
        }

        ofstream outputFile("output2.txt");
        if (!outputFile)
        {
            cerr << "Error opening file!" << endl;
            return -1;
        }

        outputFile << fixed << setprecision(5);
        outputFile << "Attribute    | Information Gain | Entropy\n";
        outputFile << "---------------------------------------------\n";
        for (const auto &ig : infoGains)
        {
            outputFile << setw(12) << left << ig.first << " | "
                    << setw(17) << left << ig.second << " | "
                    << setw(7) << left << entropies[ig.first] << endl;
        }

        string maxIGAttribute;
        double maxIG = -1;
        for (const auto &ig : infoGains)
        {
            if (ig.second > maxIG)
            {
                maxIG = ig.second;
                maxIGAttribute = ig.first;
            }
        }
        outputFile << "\nThe splitting attribute is selected as " << maxIGAttribute
                << " because it has the maximum information gain of " << maxIG << ".\n";

        outputFile.close();
        return 0;
    }
