#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

// Define the structure for a single Decision Tree node
struct TreeNode {
    int feature; // The feature index to split on
    double threshold; // The threshold value to split
    double value; // The predicted value at this leaf node (for regression)
    TreeNode* left; // Left child
    TreeNode* right; // Right child
};

// Decision Tree Class for Regression
class DecisionTree {
public:
    DecisionTree(int maxDepth, int minSamplesSplit)
        : maxDepth(maxDepth), minSamplesSplit(minSamplesSplit) {}

    // Train the decision tree on the dataset
    void Train(const vector<vector<double>>& X, const vector<double>& Y) {
        root = BuildTree(X, Y, 0);
    }

    // Make a prediction for a single data point
    double Predict(const vector<double>& sample) {
        return PredictRecursive(root, sample);
    }

private:
    int maxDepth;
    int minSamplesSplit;
    TreeNode* root;

    // Function to build the tree recursively
    TreeNode* BuildTree(const vector<vector<double>>& X, const vector<double>& Y, int depth) {
        int n_samples = X.size();
        int n_features = X[0].size();

        // If stopping conditions are met, return a leaf node
        if (depth >= maxDepth || n_samples <= minSamplesSplit) {
            return CreateLeaf(Y);
        }

        // Find the best split
        int bestFeature;
        double bestThreshold;
        double bestScore = std::numeric_limits<double>::infinity();
        vector<double> leftLabels, rightLabels;
        vector<vector<double>> leftX, rightX;

        // Loop over each feature and threshold to find the best split
        for (int feature = 0; feature < n_features; ++feature) {
            vector<double> thresholds;
            for (int i = 0; i < n_samples; ++i) {
                thresholds.push_back(X[i][feature]);
            }
            sort(thresholds.begin(), thresholds.end());
            thresholds.erase(unique(thresholds.begin(), thresholds.end()), thresholds.end());

            for (double threshold : thresholds) {
                vector<double> leftLabelsTemp, rightLabelsTemp;
                vector<vector<double>> leftXTemp, rightXTemp;

                for (int i = 0; i < n_samples; ++i) {
                    if (X[i][feature] <= threshold) {
                        leftXTemp.push_back(X[i]);
                        leftLabelsTemp.push_back(Y[i]);
                    } else {
                        rightXTemp.push_back(X[i]);
                        rightLabelsTemp.push_back(Y[i]);
                    }
                }

                double score = MeanSquaredError(leftLabelsTemp, rightLabelsTemp);
                if (score < bestScore) {
                    bestScore = score;
                    bestFeature = feature;
                    bestThreshold = threshold;
                    leftLabels = leftLabelsTemp;
                    rightLabels = rightLabelsTemp;
                    leftX = leftXTemp;
                    rightX = rightXTemp;
                }
            }
        }

        TreeNode* node = new TreeNode;
        node->feature = bestFeature;
        node->threshold = bestThreshold;
        node->left = BuildTree(leftX, leftLabels, depth + 1);
        node->right = BuildTree(rightX, rightLabels, depth + 1);
        return node;
    }

    // Function to create a leaf node
    TreeNode* CreateLeaf(const vector<double>& labels) {
        TreeNode* leaf = new TreeNode;
        leaf->left = leaf->right = nullptr;

        // The value at the leaf node is the mean of the labels
        leaf->value = Mean(labels);
        return leaf;
    }

    // Calculate the Mean Squared Error for the split (regression)
    double MeanSquaredError(const vector<double>& left, const vector<double>& right) {
        int n = left.size() + right.size();
        double leftMSE = CalculateMSE(left);
        double rightMSE = CalculateMSE(right);
        return (left.size() / double(n)) * leftMSE + (right.size() / double(n)) * rightMSE;
    }

    // Calculate the Mean Squared Error for a given set of labels
    double CalculateMSE(const vector<double>& labels) {
        int n = labels.size();
        if (n == 0) return 0.0;

        double mean = Mean(labels);
        double mse = 0.0;
        for (double label : labels) {
            mse += (label - mean) * (label - mean);
        }
        return mse / n;
    }

    // Calculate the mean of a set of labels
    double Mean(const vector<double>& labels) {
        double sum = 0.0;
        for (double label : labels) {
            sum += label;
        }
        return sum / labels.size();
    }

    // Recursive function to predict a sample
    double PredictRecursive(TreeNode* node, const vector<double>& sample) {
        if (!node->left && !node->right) return node->value;
        if (sample[node->feature] <= node->threshold) {
            return PredictRecursive(node->left, sample);
        } else {
            return PredictRecursive(node->right, sample);
        }
    }
};

// Random Forest Class for Regression
class RandomForest {
public:
    RandomForest(int nTrees, int maxDepth, int minSamplesSplit)
        : nTrees(nTrees), maxDepth(maxDepth), minSamplesSplit(minSamplesSplit) {}

    // Train the Random Forest model
    void Train(const vector<vector<double>>& X, const vector<double>& Y) {
        for (int i = 0; i < nTrees; ++i) {
            vector<vector<double>> X_bootstrap;
            vector<double> Y_bootstrap;
            BootstrapSampling(X, Y, X_bootstrap, Y_bootstrap);
            DecisionTree tree(maxDepth, minSamplesSplit);
            tree.Train(X_bootstrap, Y_bootstrap);
            trees.push_back(tree);
        }
    }

    // Predict for a given sample
    double Predict(const vector<double>& sample) {
        vector<double> predictions;
        for (auto& tree : trees) {
            predictions.push_back(tree.Predict(sample));
        }
        return Mean(predictions);
    }

private:
    int nTrees;
    int maxDepth;
    int minSamplesSplit;
    vector<DecisionTree> trees;

    // Perform bootstrap sampling
    void BootstrapSampling(const vector<vector<double>>& X, const vector<double>& Y,
                           vector<vector<double>>& X_bootstrap, vector<double>& Y_bootstrap) {
        int n_samples = X.size();
        srand(time(0)); // Set random seed
        for (int i = 0; i < n_samples; ++i) {
            int idx = rand() % n_samples;
            X_bootstrap.push_back(X[idx]);
            Y_bootstrap.push_back(Y[idx]);
        }
    }

    // Calculate the mean of predictions (average for regression)
    double Mean(const vector<double>& predictions) {
        double sum = 0.0;
        for (double prediction : predictions) {
            sum += prediction;
        }
        return sum / predictions.size();
    }
};

// Main Function to demonstrate Random Forest
int main() {
    vector<vector<double>> X = {
        {0.8262, 0.64316, 0.1172},   // Prey Avg, NDVI avg, Night light average
        {0.8519, 0.6445287, 0.1934},
        {0.2800, 0.4854792, 0.14973},
        {0.3315, 0.485479, 0.326068},
        {0.5091, 0.626845, 0.11621},
        {0.6364, 0.6130765, 0.20874},
        {0.8876, 0.58520736, 0.10393},
        {0.7641, 0.52852245, 0.2657},
        {0.823816, 0.37612621, 0.242106},
        {0.5786, 0.35900152, 0.38658},
        {0.3459, 0.628574983, 0.64393},
        {0.9543, 0.62507264, 0.834934},
        {0.4949, 0.57737195, 0.203637},
        {0.6590, 0.56316816, 0.34779017},
        {0.3005, 0.5429728, 0.130490324},
        {0.5214, 0.48359717, 0.276153}
    };
    vector<double> Y = {0.138473643, 0.179347826, 0.067667011, 0.03903866, 0.111801242, 0.194099379, 0.038818914, 0.036341111, 0.027634488, 0.03755456, 0.011304348, 0.032173913, 0.02141527, 0.053072626, 0.027214823, 0.047481181};

    // Create a Random Forest model
    RandomForest rf(100 , 10 ,4);
    rf.Train(X, Y);

    // Predict for a new sample
    vector<double> newSample = {0.8262 , 0.62507264, 0.1135};
    double prediction = rf.Predict(newSample);

    // Output the prediction
    cout << "Predicted tiger density " << prediction << endl;

    return 0;
}