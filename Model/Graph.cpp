//
// Created by Novin##### on 5/1/2025.
//

#include "Graph.h"

#include <iostream>
#include <ostream>
Graph::Graph(vector<Element*> elements, vector<Node*> nodes):elements(elements), nodes(nodes) {
    DIM=0;
    V=0;
    G=0;
};
Graph::~Graph(){};
vector<vector<double>> Graph::buildMatrix(){


    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->getNodeNumber() != 0) {
            DIM++;
            G++;
        }
    }
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->getType() == "VoltageSource") {
            DIM++;
            V++;
        }
    }

    //zero Padding matrixe...
    for (int i = 0; i < DIM; i++) {
        vector <double> temp(DIM,0);
        matrix.push_back(temp);
    }
    int voltageSourceCount = 0;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->getType() == "Resistor") {
            cout << "Resistor recognized!" << endl;
            if (elements[i]->getFirstNode()->getNodeNumber()!=0 && elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                matrix[elements[i]->getFirstNode()->getNodeNumber()-1][elements[i]->getSecondtNode()->getNodeNumber()-1] = -1.0/elements[i]->getValue();
                matrix[elements[i]->getSecondtNode()->getNodeNumber()-1][elements[i]->getFirstNode()->getNodeNumber()-1] = -1.0/elements[i]->getValue();

            }
            if (elements[i]->getFirstNode()->getNodeNumber()!=0) {
                matrix[elements[i]->getFirstNode()->getNodeNumber()-1][elements[i]->getFirstNode()->getNodeNumber()-1]+= 1.0/elements[i]->getValue();
            }
            if (elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                matrix[elements[i]->getSecondtNode()->getNodeNumber()-1][elements[i]->getSecondtNode()->getNodeNumber()-1]+= 1.0/elements[i]->getValue();
            }

        }
        if (elements[i]->getType() == "VoltageSource") {
            cout << "VoltageSource recognized!" << endl;
            if (elements[i]->getFirstNode()->getNodeNumber()!=0) {
                matrix[G+voltageSourceCount][elements[i]->getFirstNode()->getNodeNumber()-1] = 1;
                matrix[elements[i]->getFirstNode()->getNodeNumber()-1][G+voltageSourceCount] = 1;
            }
            if (elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                matrix[G+voltageSourceCount][elements[i]->getSecondtNode()->getNodeNumber()-1] = -1;
                matrix[elements[i]->getSecondtNode()->getNodeNumber()-1][G+voltageSourceCount] = -1;
            }


            voltageSourceCount++;
        }
    }

    return matrix;
};

vector<double> Graph::buildInfoMatrix() {
    infoMatrix = vector<double>(DIM,0);
    int voltageSourceCount = 0;
    for (int i=0; i < elements.size(); i++) {
        if (elements[i]->getType() == "CurrentSource") {
            if (elements[i]->getFirstNode()->getNodeNumber()!=0) {
                infoMatrix[elements[i]->getFirstNode()->getNodeNumber()-1] = -elements[i]->getValue();
            }
            if (elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                infoMatrix[elements[i]->getSecondtNode()->getNodeNumber()-1] = elements[i]->getValue();
            }

        }
        if (elements[i]->getType() == "VoltageSource") {
            infoMatrix[G+voltageSourceCount] = elements[i]->getValue();
            voltageSourceCount++;
        }
    }
    return infoMatrix;
}

