#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>

using namespace mlpack;
using namespace arma;

int main()
{
    // Load or generate your dataset
    mat X_train; // Features
    rowvec Y_train; // Labels

    // Convert Y_train to arma::Row<size_t>
    Row<size_t> labels = conv_to<Row<size_t>>::from(Y_train);

    // Create the RandomForest object
    mlpack::RandomForest<> rf;

    // Train the model
    rf.Train(X_train, labels, 10 /* numClasses */, 100 /* numTrees */);

    // Predict on test data
    mat X_test; // Test features
    Row<size_t> predictions;
    rf.Classify(X_test, predictions);

    // Output predictions
    predictions.print("Predictions:");

    return 0;
}
