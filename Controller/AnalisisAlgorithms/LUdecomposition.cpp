//
// Created by Novin##### on 5/1/2025.
//

#include "LUdecomposition.h"
#include <cmath>
#include <stdexcept>
using namespace std;

void LUdecomposition::decomposition(const vector<vector<double>>& coefficientMatrix) {
    int n = coefficientMatrix.size();
    if (coefficientMatrix[0].size() != n)
        throw runtime_error("Coefficient Matrix should be square!");

    LMatrix = vector<vector<double>>(n, vector<double>(n, 0.0));
    UMatrix = coefficientMatrix;
    permutation.resize(n);
    for (int i = 0; i < n; ++i)
        permutation[i] = i;

    for (int i = 0; i < n; ++i) {
        // Pivoting: Find max row in column i
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
            if (abs(UMatrix[k][i]) > abs(UMatrix[maxRow][i]))
                maxRow = k;

        if (abs(UMatrix[maxRow][i]) < 1e-12)
            throw runtime_error("Matrix is singular or nearly singular!");

        // Swap rows in U and permutation
        swap(UMatrix[i], UMatrix[maxRow]);
        swap(permutation[i], permutation[maxRow]);
        for (int j = 0; j < i; ++j)
            swap(LMatrix[i][j], LMatrix[maxRow][j]);

        // Compute L and update U
        for (int j = i + 1; j < n; ++j) {
            double factor = UMatrix[j][i] / UMatrix[i][i];
            LMatrix[j][i] = factor;
            for (int k = i; k < n; ++k)
                UMatrix[j][k] -= factor * UMatrix[i][k];
        }
        LMatrix[i][i] = 1.0;
    }
}

vector<double> LUdecomposition::forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b) {
    int n = L.size();
    vector<double> y(n);

    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j)
            y[i] -= L[i][j] * y[j];
        // Don't divide by L[i][i] unless non-unit diagonal
    }

    return y;
}

vector<double> LUdecomposition::backwardSubstitution(const vector<vector<double>>& U, const vector<double>& y) {
    int n = U.size();
    vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }

    return x;
}

vector<double> LUdecomposition::solveLU(const vector<vector<double>>& L, const vector<vector<double>>& U, const vector<double>& b) {
    int n = b.size();
    vector<double> pb(n);
    for (int i = 0; i < n; ++i)
        pb[i] = b[permutation[i]];  // apply permutation to b

    vector<double> y = forwardSubstitution(L, pb);
    vector<double> x = backwardSubstitution(U, y);
    return x;
}
vector<vector<double>> LUdecomposition::getLMat() {
    return this->LMatrix;
}
vector<vector<double>> LUdecomposition::getUMat() {
    return this->UMatrix;
}