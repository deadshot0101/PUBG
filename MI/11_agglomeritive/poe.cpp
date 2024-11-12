#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// Function to compute Euclidean distance between two points
double euclideanDistance(const vector<double>& point1, const vector<double>& point2) {
    double sum = 0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += pow(point1[i] - point2[i], 2);
    }
    return sqrt(sum);
}

// Function to display the distance matrix
void displayDistanceMatrix(const vector<vector<double>>& distanceMatrix, const vector<string>& labels) {
    int n = distanceMatrix.size();

    // Print column headings
    cout << "   \t";
    for (const auto& label : labels) {
        cout << label << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        // Print row heading
        cout << labels[i] << "\t";
        for (int j = 0; j < n; ++j) {
            cout << fixed << setprecision(2) << distanceMatrix[i][j] << "\t";
        }
        cout << endl; // New line after each row
    }
}

// Agglomerative hierarchical clustering using single linkage method
void agglomerativeClustering(vector<vector<double>>& points) {
    int n = points.size();
    vector<vector<double>> distanceMatrix(n, vector<double>(n, 0.0));
    vector<bool> clustered(n, false);
    vector<pair<int, int>> clusters; // To store clusters as pairs of indices

    // Compute the initial distance matrix
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            distanceMatrix[i][j] = euclideanDistance(points[i], points[j]);
            distanceMatrix[j][i] = distanceMatrix[i][j]; // Symmetric
        }
    }

    // Display the initial distance matrix
    vector<string> labels; // To store point labels
    for (int i = 0; i < n; ++i) {
        labels.push_back("Point " + to_string(i + 1)); // Generating labels
    }
    cout << "Initial Distance Matrix:\n";
    displayDistanceMatrix(distanceMatrix, labels);

    // Perform clustering
    while (n > 1) {
        // Find the two closest clusters
        double minDistance = numeric_limits<double>::max();
        int clusterA = -1, clusterB = -1;

        for (int i = 0; i < distanceMatrix.size(); ++i) {
            for (int j = i + 1; j < distanceMatrix.size(); ++j) {
                if (distanceMatrix[i][j] < minDistance) {
                    minDistance = distanceMatrix[i][j];
                    clusterA = i;
                    clusterB = j;
                }
            }
        }

        // Merge the clusters
        cout << "\nMerging clusters: " << labels[clusterA] << " and " << labels[clusterB] << " with distance: " << minDistance << endl;
        
        // Update the distance matrix
        for (int i = 0; i < distanceMatrix.size(); ++i) {
            if (i != clusterA && i != clusterB) {
                // Calculate the new distance using the single linkage method
                distanceMatrix[clusterA][i] = min(distanceMatrix[clusterA][i], distanceMatrix[clusterB][i]);
                distanceMatrix[i][clusterA] = distanceMatrix[clusterA][i]; // Ensure symmetry
            }
        }

        // Mark the second cluster as merged
        clustered[clusterB] = true;

        // Remove the merged cluster from the distance matrix
        for (int i = 0; i < distanceMatrix.size(); ++i) {
            distanceMatrix[clusterB][i] = numeric_limits<double>::max();
            distanceMatrix[i][clusterB] = numeric_limits<double>::max(); // Remove clusterB
        }

        // Update labels and reduce the size of the distance matrix
        labels[clusterA] = labels[clusterA] + " & " + labels[clusterB]; // Update label to reflect merge
        labels.erase(labels.begin() + clusterB); // Remove the second cluster label
        distanceMatrix.erase(distanceMatrix.begin() + clusterB); // Remove the second cluster row

        for (auto& row : distanceMatrix) {
            row.erase(row.begin() + clusterB); // Remove the second cluster column
        }

        n--; // Decrease the number of clusters
        cout << "\nUpdated Distance Matrix after merging:\n";
        displayDistanceMatrix(distanceMatrix, labels);
    }

    cout << "\nFinal cluster: " << labels[0] << endl; // Final merged cluster
}

int main() {
    fstream in("input.csv");
    vector<vector<double>> points;
    string line;
    // Read points from the CSV file
    while (getline(in, line)) {
        stringstream ss(line);
        string value;
        vector<double> point;

        while (getline(ss, value, ',')) {
            point.push_back(stod(value)); // Convert string to double and store in point
        }
        points.push_back(point); // Add point to the points vector
    }

    in.close();

    // Perform agglomerative clustering
    agglomerativeClustering(points);

    return 0;
}
