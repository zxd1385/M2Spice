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
    MNAanalisis() {
        this->graph = new Graph(elements,nodes);
    };
    MNAanalisis(vector<Node*> nodes , vector<Element*> elements);
    void setBasicVectors(vector<Node*> nodes , vector<Element*> elements) {
        this->nodes = nodes;
        this->elements = elements;
        this->graph->setBasicVectors( elements,nodes);
    }
    void simulateCircuit(double stopTime,double timeSteps);
    void DCswipe(double startVal,double endVal,double increament,Element* e);


};



#endif //MNAANALISIS_H
