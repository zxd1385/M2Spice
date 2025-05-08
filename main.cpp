#include <iostream>
#include <vector>
#include <iomanip>
#include "Controller/ProggramController.h"
#include "Controller/AnalisisAlgorithms/LUdecomposition.h"
#include "Model/Graph.h"
#include "Model/Node.h"
#include "Model/DerivedElements/Resistor.h"
#include "Model/DerivedElements/VoltageSource.h"

int main() {
    vector<Element*> elements;
    vector<Node*> nodes;
    Node GND(0);
    Node GPO(1);
    Node GPO2(2);
    Node GPO3(3);
    nodes.push_back(&GND);
    nodes.push_back(&GPO);
    nodes.push_back(&GPO2);
    nodes.push_back(&GPO3);

    Resistor R1 (&GPO,&GPO2,1);
    Resistor R2 (&GPO3,&GPO2,2);
    Resistor R3 (&GPO,&GND,4);
    VoltageSource V1(&GPO2,&GPO,2);
    VoltageSource V2(&GPO3,&GND,1);

    elements.push_back(&V1);
    elements.push_back(&R1);
    elements.push_back(&R2);
    elements.push_back(&R3);
    elements.push_back(&V2);

    Graph G(elements,nodes);
    vector<vector<double>> circuitMat = G.buildMatrix();
    vector<double> infoMat = G.buildInfoMatrix();

    for (int i = 0; i < circuitMat.size(); i++) {
        for (int j = 0; j < circuitMat[i].size(); j++) {
            cout<< setw(4) << circuitMat[i][j] << " ";
        }
        cout <<"   " << infoMat[i] << endl;
    }

cout << "------------------------------------------" << endl;
    LUdecomposition myLU;
    myLU.decomposition(circuitMat);
    vector<vector<double>> Lmat = myLU.getLMat();
    vector<vector<double>> Umat = myLU.getUMat();
    vector<double> x = myLU.solveLU(Lmat,Umat,infoMat);
    for (int i = 0; i < x.size(); i++) {
        cout << setw(4) << x[i] << endl;
    }
    // for (int i = 0; i < Lmat.size(); i++) {
    //     for (int j = 0; j < Lmat[i].size(); j++) {
    //         cout << setw(6) << fixed << setprecision(3)<< Lmat[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "--------------------------------------------" << endl;
    // for (int i = 0; i < Umat.size(); i++) {
    //     for (int j = 0; j < Umat[i].size(); j++) {
    //         cout << setw(4) << Umat[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
