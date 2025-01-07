#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to perform matrix multiplication
vector<vector<double>> matrixMultiplication(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    int m = A[0].size();
    int p = B[0].size();

    vector<vector<double>> result(n, vector<double>(p, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Function to transpose a matrix
vector<vector<double>> transpose(const vector<vector<double>>& A) {
    int n = A.size();
    int m = A[0].size();

    vector<vector<double>> result(m, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][i] = A[i][j];
        }
    }
    return result;
}

// Function to invert a square matrix
vector<vector<double>> invertMatrix(const vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> augmented(n, vector<double>(2 * n, 0));

    // Create the augmented matrix [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
        }
        augmented[i][n + i] = 1;
    }

    for (int i = 0; i < n; i++) {
        // Make the diagonal element 1
        double diagElement = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= diagElement;
        }

        // Make all other elements in this column 0
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // Extract the inverse matrix
    vector<vector<double>> inverse(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = augmented[i][j + n];
        }
    }
    return inverse;
}

// Function to compute coefficients using the Normal Equation
vector<double> computeCoefficients(const vector<vector<double>>& X, const vector<double>& Y) {
    // Convert Y into a column vector
    vector<vector<double>> Y_col(Y.size(), vector<double>(1));
    for (size_t i = 0; i < Y.size(); i++) {
        Y_col[i][0] = Y[i];
    }

    // X^T * X
    vector<vector<double>> X_transpose = transpose(X);
    vector<vector<double>> XtX = matrixMultiplication(X_transpose, X);

    // Invert (X^T * X)
    vector<vector<double>> XtX_inv = invertMatrix(XtX);

    // X^T * Y
    vector<vector<double>> XtY = matrixMultiplication(X_transpose, Y_col);

    // Coefficients = (X^T * X)^-1 * (X^T * Y)
    vector<vector<double>> B = matrixMultiplication(XtX_inv, XtY);

    // Convert back to 1D vector
    vector<double> coefficients(B.size());
    for (size_t i = 0; i < B.size(); i++) {
        coefficients[i] = B[i][0];
    }
    return coefficients;
}

// Main function
int main() {
    // Input data: X matrix (1st column is bias term)
    vector<vector<double>> X = {
        {1, 0.8262, 0.64316, 0.1172},   // Bias, NDVI avg, Prey avg, Night light avg
        {1, 0.8519, 0.6445287, 0.1934},
        {1, 0.2800, 0.4854792, 0.14973},
        {1, 0.3315, 0.485479, 0.326068},
        {1, 0.5091, 0.626845, 0.11621},
        {1, 0.6364, 0.6130765, 0.20874},
        {1, 0.8876, 0.58520736, 0.10393},
        {1, 0.7641, 0.52852245, 0.2657},
        {1, 0.823816, 0.37612621, 0.242106},
        {1, 0.5786, 0.35900152, 0.38658},
        {1, 0.3459, 0.628574983, 0.64393},
        {1, 0.9543, 0.62507264, 0.834934},
        {1, 0.4949, 0.57737195, 0.203637},
        {1, 0.6590, 0.56316816, 0.34779017},
        {1, 0.3005, 0.5429728, 0.130490324},
        {1, 0.5214, 0.48359717, 0.276153}
    };

    // Target values: Tiger population per sq km
    vector<double> Y = {0.138473643, 0.179347826, 0.067667011, 0.03903866, 0.111801242, 0.194099379, 0.038818914, 0.036341111, 0.027634488, 0.03755456, 0.011304348, 0.032173913, 0.02141527, 0.053072626, 0.027214823, 0.047481181};

    // Compute coefficients
    vector<double> coefficients = computeCoefficients(X, Y);

    // Output coefficients
    cout << "Coefficients:\n";
    for (size_t i = 0; i < coefficients.size(); i++) {
        cout << "b" << i << " = " << fixed << setprecision(4) << coefficients[i] << endl;
    }

    return 0;
}
