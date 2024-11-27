#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <mlpack/core/data/split_data.hpp> // For splitting the dataset
#include <iostream>

using namespace mlpack;
using namespace arma;

int main()
{
    // Load the training dataset
    mat X_train;
    rowvec Y_train;
    data::Load("training_data.csv", X_train, true);  // Assuming the last column is the label
    Y_train = X_train.row(X_train.n_rows - 1);  // Last row as labels
    X_train.shed_row(X_train.n_rows - 1);  // Remove the label row from features

    // Convert Y_train to Row<size_t>
    Row<size_t> labels_train = conv_to<Row<size_t>>::from(Y_train);

    // Load the testing dataset
    mat X_test;
    rowvec Y_test;
    data::Load("testing_data.csv", X_test, true);  // Assuming the last column is the label
    Y_test = X_test.row(X_test.n_rows - 1);  // Last row as labels
    X_test.shed_row(X_test.n_rows - 1);  // Remove the label row from features

    // Convert Y_test to Row<size_t>
    Row<size_t> labels_test = conv_to<Row<size_t>>::from(Y_test);

    // Create the RandomForest object
    mlpack::RandomForest<> rf;

    // Train the model
    rf.Train(X_train, labels_train, 10 /* numClasses */, 100 /* numTrees */);  // Update numClasses as needed

    // Predict on the test data
    Row<size_t> predictions;
    rf.Classify(X_test, predictions);

    // Output predictions and compare with true labels
    predictions.print("Predictions:");
    Y_test.print("True Labels:");

    return 0;
}
