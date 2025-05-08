//
// Created by Novin##### on 5/1/2025.
//

#include "LUdecomposition.h"

#include <stdexcept>
using namespace std;

void LUdecomposition::decomposition(const vector<vector<double> > &coefficientMatrix) {
    int n = coefficientMatrix.size();
    if (coefficientMatrix[0].size() != n)
        throw runtime_error("Coefficient Matrix should be square!");

    LMatrix = vector<vector<double>>(n, vector<double>(n, 0.0));
    UMatrix = vector<vector<double>>(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        // row i calculation of U
        for (int k = i; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += LMatrix[i][j] * UMatrix[j][k];
            UMatrix[i][k] = coefficientMatrix[i][k] - sum;
        }

        // assaigning value to diagon of L
        LMatrix[i][i] = 1;

        // colomn i calculation of L
        for (int k = i + 1; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += LMatrix[k][j] * UMatrix[j][i];
            if (UMatrix[i][i] == 0)
                throw runtime_error("Diagonal element is zero!");
            LMatrix[k][i] = (coefficientMatrix[k][i] - sum) / UMatrix[i][i];
        }
    }


}
vector<double> LUdecomposition::forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b) {
    int n = L.size();
    vector<double> y(n);

    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
        // Assume diagonal of L is 1 (for Doolittle) or already handled
        if (L[i][i] != 1.0) y[i] /= L[i][i];
    }

    return y;
}
vector<double> LUdecomposition::backwardSubstitution(const vector<vector<double>>& U, const vector<double>& y) {
    int n = U.size();
    vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }

    return x;
}
vector<double> LUdecomposition::solveLU(const vector<vector<double>>& L,const vector<vector<double>>& U,const vector<double>& b) {
    vector<double> y = forwardSubstitution(L, b);
    vector<double> x = backwardSubstitution(U, y);
    return x;
}
vector<vector<double>> LUdecomposition::getLMat() {
    return this->LMatrix;
}
vector<vector<double>> LUdecomposition::getUMat() {
    return this->UMatrix;
}