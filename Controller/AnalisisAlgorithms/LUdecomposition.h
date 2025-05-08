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
    vector<vector<double>> getLMat();
    vector<vector<double>> getUMat();
};



#endif //LUDECOMPOSITION_H
