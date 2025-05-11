//
// Created by Novin##### on 5/1/2025.
//
#include <iostream>
#include "MNAanalisis.h"


MNAanalisis::MNAanalisis(vector<Node*> nodes , vector<Element*> elements) {
    this->nodes = nodes;
    this->elements = elements;
    this->graph = new Graph(elements,nodes);

};
void MNAanalisis::simulateCircuit(double stopTime,double timeSteps) {
    //capasitor impact...

    for (auto& element : this->elements) {

            element->updateDynamicElements(this->nodes,this->elements);
    }


    this->coefficientMatrix = this->graph->buildMatrix();

    ludecomposition.decomposition(coefficientMatrix);

    this->Lmatrix = this->ludecomposition.getLMat();

    this->Umatrix = this->ludecomposition.getUMat();




    int cycle = stopTime / timeSteps;

    for(int i=0;i<cycle;i++) {
        this->knownVector = this->graph->buildInfoMatrix();

        vector <double> answers = this->ludecomposition.solveLU(Lmatrix,Umatrix,knownVector);



        for (auto& x : nodes ) {
            if (x->getNodeNumber() > 0)
            x->addVoltage(answers[x->getNodeNumber()-1]);
            else if (x->getNodeNumber() == 0)
                x->addVoltage(0);
        }

        int voltageSourceCount =0;
        for (auto& x : elements ) {

            if (x->getType()=="VoltageSource") {
                x->updateValue(answers[nodes.size()+voltageSourceCount++]);

            }
            if (x->getType()=="Capacitor" || x->getType()=="Inductor") {

                x->updateValue(1.00);

            }
        }


    }


    //capacitor return imoact
    for (auto& element : this->elements) {

        element->redoDynamicElements(this->nodes,this->elements);
    }

};