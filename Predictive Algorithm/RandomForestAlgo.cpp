#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <mlpack/core/data/split_data.hpp>

using namespace mlpack;
using namespace mlpack::tree;
using namespace arma;

int main() {
    // Dataset: Features (X) and Target (Y)
    mat dataset;
    data::Load("tiger_data.csv", dataset, true); // Load dataset from CSV

    // Separate features (X) and targets (Y)
    mat X = dataset.submat(0, 0, dataset.n_rows - 2, dataset.n_cols - 1);
    rowvec Y = dataset.row(dataset.n_rows - 1);

    // Split data into training (80%) and testing (20%) sets
    mat X_train, X_test;
    rowvec Y_train, Y_test;
    data::Split(X, Y, X_train, X_test, Y_train, Y_test, 0.2);

    // Train Random Forest
    RandomForest<> rf;
    rf.Train(X_train, Y_train, 10, 100); // 10 classes, 100 trees

    // Predict on test data
    rowvec predictions;
    rf.Predict(X_test, predictions);

    // Calculate Mean Squared Error
    double mse = mean(square(predictions - Y_test));
    std::cout << "Mean Squared Error: " << mse << std::endl;

    // Feature importance (optional)
    arma::vec importances = rf.FeatureImportance();
    std::cout << "Feature Importances: " << importances.t() << std::endl;

    // User Input
    vec input = {0.8, 0.6, 0.2}; // Example inputs
    double density = rf.Predict(input);
    double area = 500; // Example area in square kilometers
    std::cout << "Predicted Density: " << density << std::endl;
    std::cout << "Estimated Total Tiger Population: " << density * area << std::endl;

    return 0;
}
