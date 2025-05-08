//
// Created by Novin##### on 5/1/2025.
//

#ifndef LUDECOMPOSITION_H
#define LUDECOMPOSITION_H
#include "../ProggramController.h"
#include <vector>
using namespace std;


class LUdecomposition {
    private:
    vector<vector<double>> LMatrix;
    vector<vector<double>> UMatrix;
    public:
    LUdecomposition(){};
    ~LUdecomposition(){};
    void decomposition(const vector<vector<double>>& coefficientMatrix);
    vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b);
    vector<double> backwardSubstitution(const vector<vector<double>>& U, const vector<double>& y);
    vector<double> solveLU(const vector<vector<double>>& L,const vector<vector<double>>& U,const vector<double>& b);
    vector<vector<double>> getLMat();
    vector<vector<double>> getUMat();
};



#endif //LUDECOMPOSITION_H
