//
// Created by Novin##### on 5/1/2025.
//

#include "Graph.h"

#include <iostream>
#include <map>
#include <ostream>

#include "DerivedElements/CurrentSource.h"
double Gmin = 1e-12;
Graph::Graph(vector<Element*> elements, vector<Node*> nodes):elements(elements), nodes(nodes) {
    DIM=0;
    V=0;
    G=0;
};
Graph::~Graph(){};
vector<vector<double>> Graph::buildMatrix(){

    matrix.clear();
    DIM=0;
    V=0;
    G=0;
    map<Element*,int> voltageSourceMap;

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->getNodeNumber() != 0) {
            DIM++;
            G++;
        }
    }
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->getType() == "VoltageSource") {
            DIM++;
            voltageSourceMap[elements[i]]= V++;
        }
    }

    //zero Padding matrixe...
    for (int i = 0; i < DIM; i++) {
        vector <double> temp(DIM,0);
        matrix.push_back(temp);
    }
    int voltageSourceCount = 0;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->getType() == "Resistor" ) {
            if (elements[i]->getFirstNode()->getNodeNumber()!=0 && elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                matrix[elements[i]->getFirstNode()->getNodeNumber()-1][elements[i]->getSecondtNode()->getNodeNumber()-1] = -1.0/elements[i]->getValue();
                matrix[elements[i]->getSecondtNode()->getNodeNumber()-1][elements[i]->getFirstNode()->getNodeNumber()-1] = -1.0/elements[i]->getValue();

            }
            if (elements[i]->getFirstNode()->getNodeNumber()!=0) {
                matrix[elements[i]->getFirstNode()->getNodeNumber()-1][elements[i]->getFirstNode()->getNodeNumber()-1]+= 1.0/elements[i]->getValue() ;
            }
            if (elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                matrix[elements[i]->getSecondtNode()->getNodeNumber()-1][elements[i]->getSecondtNode()->getNodeNumber()-1]+= 1.0/elements[i]->getValue();
            }

        }
        if (elements[i]->getType() == "VoltageSource") {

            if (elements[i]->getFirstNode()->getNodeNumber()!=0) {
                matrix[G+voltageSourceCount][elements[i]->getFirstNode()->getNodeNumber()-1] = 1;
                matrix[elements[i]->getFirstNode()->getNodeNumber()-1][G+voltageSourceCount] = 1;
            }
            if (elements[i]->getSecondtNode()->getNodeNumber()!=0) {
                matrix[G+voltageSourceCount][elements[i]->getSecondtNode()->getNodeNumber()-1] = -1;
                matrix[elements[i]->getSecondtNode()->getNodeNumber()-1][G+voltageSourceCount] = -1;
            }
            VoltageSource* voltageSource = dynamic_cast<VoltageSource*>(elements[i]);
            if (voltageSource->getDependency() == "VCVS") {
                //cout << "VCVS recognized!" << endl;
                int firstNode = voltageSource->getFirstNode()->getNodeNumber()-1;
                int secondNode = voltageSource->getSecondtNode()->getNodeNumber()-1;
                int firstNodeDependentNumber = voltageSource->getFirstNodeDependent()->getNodeNumber()-1;
                int secondNodeDependentNumber = voltageSource->getSecondNodeDependent()->getNodeNumber()-1;
                double Gain = voltageSource->getGain();
                if (firstNodeDependentNumber >=0) {
                    matrix[G+voltageSourceCount][firstNodeDependentNumber] -= Gain;
                    //matrix[firstNodeDependentNumber][G+voltageSourceCount] -= Gain;
                }
                if (secondNodeDependentNumber >=0) {
                    matrix[G+voltageSourceCount][secondNodeDependentNumber] += Gain;
                    //matrix[secondNodeDependentNumber][G+voltageSourceCount] -= Gain;
                }


            }
            if (voltageSource->getDependency() == "CCVS") {
                int firstNode = voltageSource->getFirstNode()->getNodeNumber()-1;
                int secondNode = voltageSource->getSecondtNode()->getNodeNumber()-1;
                int voltageSourceDependentNumber = voltageSourceMap[voltageSource->getVoltageSourceDependent()];
                double Gain = voltageSource->getGain();
                matrix[G+voltageSourceCount][G+voltageSourceDependentNumber] -= Gain;
            }


            voltageSourceCount++;
        }
        if (elements[i]->getType() == "CurrentSource" ) {
            CurrentSource* currentSource = dynamic_cast<CurrentSource*>(elements[i]);
            if (currentSource->getDependency() == "VCCS") {
                int firstNodeNumber = currentSource->getFirstNode()->getNodeNumber()-1;
                int secondNodeNumber = currentSource->getSecondtNode()->getNodeNumber()-1;
                int firstNodeDependentIndex = currentSource->getFirstNodeDepent()-1 ;
                int secondNodeDependentIndex = currentSource->getSecondNodeDepent()-1 ;
                int Gain = currentSource->getGain();
                if (firstNodeNumber >= 0 && secondNodeDependentIndex >= 0) {
                    matrix[firstNodeNumber][secondNodeDependentIndex] -= Gain;
                }
                if (firstNodeNumber >= 0 && firstNodeDependentIndex >= 0) {
                    matrix[firstNodeNumber][firstNodeDependentIndex] += Gain;
                }
                if (secondNodeNumber >= 0 && secondNodeDependentIndex >= 0) {
                    matrix[secondNodeNumber][secondNodeDependentIndex] += Gain;
                }
                if (secondNodeNumber >= 0 && firstNodeDependentIndex >= 0) {
                    matrix[secondNodeNumber][firstNodeDependentIndex] -= Gain;
                }


            }
            if (currentSource->getDependency() == "CCCS") {
                int dependentVoltageSource = voltageSourceMap[currentSource->getVoltageSourceDependent()];
                int Gain = currentSource->getGain();
                int firstNodeNumber = currentSource->getFirstNode()->getNodeNumber()-1;
                int secondNodeNumber = currentSource->getSecondtNode()->getNodeNumber()-1;
                if (firstNodeNumber >= 0 ) {
                    matrix[firstNodeNumber][G+dependentVoltageSource] += Gain;
                    //matrix[G+dependentVoltageSource][firstNodeNumber] += Gain;
                }
                if (secondNodeNumber >= 0 ) {
                    matrix[secondNodeNumber][G+dependentVoltageSource] -= Gain;
                    //matrix[G+dependentVoltageSource][secondNodeNumber] -= Gain;
                }
            }
        }
    }

    // for (int i = 0; i < matrix.size(); i++) {
    //     for (int j = 0; j < matrix[i].size(); j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
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
    // cout << "______________________" << endl;
    // for (int i=0; i < infoMatrix.size(); i++) {
    //     cout << infoMatrix[i] << endl;
    // }
    return infoMatrix;
}

