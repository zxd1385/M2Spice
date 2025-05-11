#include <iostream>
#include <vector>
#include <iomanip>
#include "Controller/ProggramController.h"
#include "Controller/AnalisisAlgorithms/LUdecomposition.h"
#include "Controller/AnalisisAlgorithms/MNAanalisis.h"
#include "Model/Graph.h"
#include "Model/Node.h"
#include "Model/DerivedElements/Capacitor.h"
#include "Model/DerivedElements/CurrentSource.h"
#include "Model/DerivedElements/Inductor.h"
#include "Model/DerivedElements/Resistor.h"
#include "Model/DerivedElements/VoltageSource.h"

int main() {
    vector<Element*> elements;
    vector<Node*> nodes;
    Node GND(0);
    Node GPO1(1);
    Node GPO2(2);
    Node GPO3(3);
    Node GPO4(4);
    Node GPO5(5);
    nodes.push_back(&GND);
    nodes.push_back(&GPO1);
    nodes.push_back(&GPO2);
    nodes.push_back(&GPO3);
    nodes.push_back(&GPO4);
    nodes.push_back(&GPO5);

    Resistor R1 (&GPO3,&GPO2,1000,"R1");
    Resistor R2 (&GPO4,&GPO5,1000,"R2");
    R2.addValue(60,"R2P");
    Resistor R3 (&GPO5,&GND,1000,"R3");
    Resistor R4 (&GND,&GPO1,30,"R4");
    VoltageSource V1(&GPO1,&GPO2,10,"V1");
    VoltageSource V2(&GND,&GPO3,5,"V2");
    CurrentSource i1(&GND,&GPO1,1,"C1");
    Capacitor C1(&GPO1,&GND,"C1",0.001,2,nodes,elements);
    Inductor I1(&GPO1,&GND,"I1",1,0.01,nodes,elements);
    Resistor R5 (&GPO3,&GPO4,1000,"R5");

    elements.push_back(&C1);
    elements.push_back(&V2);
    elements.push_back(&V1);
    elements.push_back(&R1);
    elements.push_back(&R2);
    elements.push_back(&R3);
    elements.push_back(&R4);
    elements.push_back(&R5);
    elements.push_back(&i1);
    elements.push_back(&I1);


    MNAanalisis myAnalisis (nodes,elements);
    Element::timeSteps = 0.0001;
    myAnalisis.simulateCircuit(1,Element::timeSteps);
    for (int i = 0; i< nodes[1]->getVoltages().size(); i++) {
        cout << nodes[1]->getVoltages()[i] << endl;
    }

//     Graph G(elements,nodes);
//     vector<vector<double>> circuitMat = G.buildMatrix();
//     vector<double> infoMat = G.buildInfoMatrix();
//
//     for (int i = 0; i < circuitMat.size(); i++) {
//         for (int j = 0; j < circuitMat[i].size(); j++) {
//             cout<< setw(4) << circuitMat[i][j] << " ";
//         }
//         cout <<"   " << infoMat[i] << endl;
//     }
//
// cout << "------------------------------------------" << endl;
//     LUdecomposition myLU;
//     myLU.decomposition(circuitMat);
//     vector<vector<double>> Lmat = myLU.getLMat();
//     vector<vector<double>> Umat = myLU.getUMat();
//     vector<double> x = myLU.solveLU(Lmat,Umat,infoMat);
//     for (int i = 0; i < x.size(); i++) {
//         cout << setw(4) << x[i] << endl;
//     }
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
