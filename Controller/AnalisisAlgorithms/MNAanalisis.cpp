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
    //cout << "Simulating Circuit" << endl;
    //capasitor impact...
    for (auto& element : this->elements) {

            element->updateDynamicElements(this->nodes,this->elements);
    }
    //cout << "Simulating Circuit" << endl;
    this->coefficientMatrix = this->graph->buildMatrix();
    ludecomposition.decomposition(coefficientMatrix);

    this->Lmatrix = this->ludecomposition.getLMat();

    this->Umatrix = this->ludecomposition.getUMat();




    int cycle = stopTime / timeSteps;

    for(int i=0;i<cycle;i++) {
        this->coefficientMatrix = this->graph->buildMatrix();
        ludecomposition.decomposition(coefficientMatrix);
        this->Lmatrix = this->ludecomposition.getLMat();
        this->Umatrix = this->ludecomposition.getUMat();
        this->knownVector = this->graph->buildInfoMatrix();


        vector <double> answers = this->ludecomposition.solveLU(Lmatrix,Umatrix,knownVector);



        for (auto& x : nodes ) {
            if (x->getNodeNumber() > 0)
            x->addVoltage(answers[x->getNodeNumber()-1]);
            else if (x->getNodeNumber() == 0)
                x->addVoltage(0);
        }
        int voltageSourceCount =-1;
        for (auto& x : elements ) {

            if (x->getType()=="VoltageSource") {
                x->updateValue(answers[nodes.size()+voltageSourceCount++]);


            }
            if (x->getType()=="Capacitor" || x->getType()=="Inductor" || x->getType()=="Diode") {


                x->updateValue(1.00);


            }
        }


    }


    //capacitor return imoact
    for (auto& element : this->elements) {

        element->redoDynamicElements(this->nodes,this->elements);
    }

};
void MNAanalisis::DCswipe(double startVal, double endVal, double increament, Element* e) {
    //capasitor impact...
    for (auto& element : this->elements) {

        element->updateDynamicElements(this->nodes,this->elements);
    }

    
    int cycle = (endVal - startVal) / increament;
    for(int i=0;i<cycle;i++) {
        e->DCswipeValue(startVal + i*increament);
        this->coefficientMatrix = this->graph->buildMatrix();
        ludecomposition.decomposition(coefficientMatrix);
        this->Lmatrix = this->ludecomposition.getLMat();
        this->Umatrix = this->ludecomposition.getUMat();
        this->knownVector = this->graph->buildInfoMatrix();


        vector <double> answers = this->ludecomposition.solveLU(Lmatrix,Umatrix,knownVector);



        for (auto& x : nodes ) {
            if (x->getNodeNumber() > 0)
                x->addVoltage(answers[x->getNodeNumber()-1]);
            else if (x->getNodeNumber() == 0)
                x->addVoltage(0);
        }
        int voltageSourceCount =-1;
        for (auto& x : elements ) {

            if (x->getType()=="VoltageSource") {
                x->updateValue(answers[nodes.size()+voltageSourceCount++]);
                //cout << nodes.size() << endl;
            }
            if (x->getType()=="Capacitor" || x->getType()=="Inductor" || x->getType()=="Diode") {


                x->updateValue(1.00);


            }
        }

        // for (auto x: answers) {
        //     cerr << x << endl;
        // }
    }


    //capacitor return imoact
    for (auto& element : this->elements) {

        element->redoDynamicElements(this->nodes,this->elements);
    }
}
