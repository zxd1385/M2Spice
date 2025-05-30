//
// Created by Novin##### on 5/1/2025.
//

#ifndef MNAANALISIS_H
#define MNAANALISIS_H
#include "LUdecomposition.h"
#include "../../Model/Node.h"
#include "../../Model/Element.h"
#include "../../Model/Graph.h"



class MNAanalisis {
    private:
    vector<Node*> nodes;
    vector<Element*> elements;
    Graph* graph;
    LUdecomposition ludecomposition;
    vector<vector<double>> coefficientMatrix;
    vector<vector<double>> Lmatrix;
    vector<vector<double>> Umatrix;
    vector<double> knownVector;
    public:
    MNAanalisis(){};
    MNAanalisis(vector<Node*> nodes , vector<Element*> elements);
    void simulateCircuit(double stopTime,double timeSteps);


};



#endif //MNAANALISIS_H
