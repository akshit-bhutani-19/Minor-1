#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to predict tiger population density
double predictTigerDensity(double prey, double ndvi, double nightlight, const vector<double>& coefficients) {
    // Coefficients: {b0, b1, b2, b3}
    return coefficients[0] + coefficients[1] * prey + coefficients[2] * ndvi + coefficients[3] * nightlight;
}

// Main function
int main() {
    // Coefficients from regression
    vector<double> coefficients = {-0.0871, 0.0565, 0.2822, -0.1252};

    // User input
    double prey, ndvi, nightlight, area;
    cout << "Enter average prey availability (normalized): ";
    cin >> prey;
    cout << "Enter average NDVI (normalized): ";
    cin >> ndvi;
    cout << "Enter average night light intensity (normalized): ";
    cin >> nightlight;
    cout << "Enter total area of reserve (in square kilometers): ";
    cin >> area;

    // Predict tiger density
    double density = predictTigerDensity(prey, ndvi, nightlight, coefficients);

    // Calculate total tiger population
    double totalPopulation = density * area;

    // Output results
    cout << fixed << setprecision(4);
    cout << "Predicted Tiger Density (per sq. km): " << density << endl;
    cout << "Estimated Total Tiger Population: " << totalPopulation << endl;

    return 0;
}
