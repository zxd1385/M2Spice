//
// Created by Novin##### on 5/1/2025.
//

#include "Inductor.h"
#include "../Element.h"
#include "CurrentSource.h"
#include "Resistor.h"
Inductor::Inductor(Node* firstNode,Node* secondNode,string iName, double inductance, double initializedCurrent,  vector<Node*> & nodes,  vector<Element*>& elements): iName(iName) , inductance(inductance), Element(firstNode,secondNode) {
    currents.push_back(initializedCurrent);
    intermediateResistor = new Resistor(this->getFirstNode(),this->getSecondtNode(),inductance/timeSteps,"__R");
    intermediateCurrentSource = new CurrentSource(this->getFirstNode(),this->getSecondtNode(),currents[0],"__C");
    elements.push_back(intermediateResistor);
    elements.push_back(intermediateCurrentSource);
}