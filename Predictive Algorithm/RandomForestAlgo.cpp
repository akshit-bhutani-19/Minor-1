#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <mlpack/core/data/split_data.hpp> // For splitting the dataset
#include <iostream>

using namespace mlpack;
using namespace arma;

int main()
{
    // Load the entire dataset
    mat dataset; // This will hold both features and labels
    data::Load("tiger_data.csv", dataset); // Replace with your file path

    // Separate the features (X) and labels (Y)
    mat X = dataset.submat(0, 0, dataset.n_rows - 2, dataset.n_cols - 1); // All rows, all columns except the last one (features)
    rowvec Y = dataset.row(dataset.n_rows - 1); // Last row as labels

    // Convert Y to arma::Row<size_t>
    Row<size_t> labels = conv_to<Row<size_t>>::from(Y);

    // Split the data into training and testing sets (80% for training, 20% for testing)
    mat X_train, X_test;
    rowvec Y_train, Y_test;
    
    // Using the correct Split function for both features and labels
    data::Split(X, Y, X_train, Y_train, X_test, Y_test, 0.8);

    // Create the RandomForest object
    mlpack::RandomForest<> rf;

    // Train the model
    rf.Train(X_train, conv_to<Row<size_t>>::from(Y_train), 10 /* numClasses */, 100 /* numTrees */);  // Update numClasses as needed

    // Predict on the test data
    Row<size_t> predictions;
    rf.Classify(X_test, predictions);

    // Output predictions and compare with true labels
    predictions.print("Predictions:");
    Y_test.print("True Labels:");

    return 0;
}
