#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <mlpack/core/data/split_data.hpp>
#include <iostream>

using namespace mlpack;
using namespace arma;

int main()
{
    // Load the training data
    mat trainingData;
    data::Load("training_data.csv", trainingData, true);

    // Load the testing data
    mat testingData;
    data::Load("testing_data.csv", testingData, true);

    // Split the data into features (X) and target (y)
    mat X_train = trainingData.submat(0, 0, trainingData.n_rows - 2, trainingData.n_cols - 1); // Features
    rowvec y_train = trainingData.row(trainingData.n_rows - 1);                               // Target

    mat X_test = testingData.submat(0, 0, testingData.n_rows - 2, testingData.n_cols - 1);
    rowvec y_test = testingData.row(testingData.n_rows - 1);

    // Convert targets to integer type for Random Forest
    Row<size_t> y_train_int = conv_to<Row<size_t>>::from(y_train * 1000); // Scale if needed
    Row<size_t> y_test_int = conv_to<Row<size_t>>::from(y_test * 1000);

    // Create the RandomForest model
    mlpack::regression::RandomForest<> rf(X_train, y_train_int, 10 /* numClasses */, 100 /* numTrees */, 2 /* minLeafSize */);

    // Predict on the test dataset
    Row<size_t> predictions;
    rf.Classify(X_test, predictions);

    // Rescale predictions back if scaled earlier
    rowvec predictions_rescaled = conv_to<rowvec>::from(predictions) / 1000.0;

    // Print the predictions and true values
    std::cout << "True Values:" << std::endl;
    y_test.t().print();
    std::cout << "Predictions:" << std::endl;
    predictions_rescaled.t().print();

    // Calculate Mean Squared Error (MSE)
    double mse = accu(square(predictions_rescaled - y_test)) / y_test.n_elem;
    std::cout << "Mean Squared Error: " << mse << std::endl;

    // R-squared Score
    double y_mean = mean(y_test);
    double total_variance = accu(square(y_test - y_mean));
    double explained_variance = total_variance - mse * y_test.n_elem;
    double r2 = explained_variance / total_variance;
    std::cout << "R-squared Score: " << r2 << std::endl;

    return 0;
}
