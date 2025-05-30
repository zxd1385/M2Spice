//
// Created by Novin##### on 5/23/2025.
//

#include "Diode.h"
Diode::Diode(Node *firstNode, Node *secondNode, string dName, double Is, double n, double VT,vector<Node*> & nodes,  vector<Element*>& elements): dName(dName), Is(Is), n(n), VT(VT), Element(firstNode, secondNode) {
    this->currentVoltage = 0;
    this->intermediateResistor = new Resistor(firstNode,secondNode,1.0/linearizedConductance(),"__DR");
    this->intermediateCurrentSource = new CurrentSource(firstNode,secondNode,0,"__DC");
    elements.push_back(intermediateCurrentSource);
    elements.push_back(intermediateResistor);
    this->elements = elements;
    this->isZener = true;
}

Diode::Diode(Node* firstNode,Node* secondNode,string dName,vector<Node*> & nodes,  vector<Element*>& elements): dName(dName), Element(firstNode, secondNode){
    this->currentVoltage = 0;
    this->intermediateResistor = new Resistor(firstNode,secondNode,0.00001,"__DR");
//    this->intermediateCurrentSource = new CurrentSource(firstNode,secondNode,0,"__DC");
//    elements.push_back(intermediateCurrentSource);
    elements.push_back(intermediateResistor);
    this->elements = elements;
    this->isZener = false;
}