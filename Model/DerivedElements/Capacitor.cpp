//
// Created by Novin##### on 5/1/2025.
//

#include "Capacitor.h"
#include "../Element.h"
#include "VoltageSource.h"
#include "Resistor.h"
Capacitor::Capacitor(Node* firstNode,Node* secondNode,string cName, double capacitance, double initializedVoltage,  vector<Node*> & nodes,  vector<Element*>& elements): cName(cName) , capacitance(capacitance), Element(firstNode,secondNode) {
    voltages.push_back(initializedVoltage);
    intermediateNode = new Node(1,"1");
    intermediateResistor = new Resistor(intermediateNode,this->getSecondtNode(),timeSteps/capacitance,"__R");
    intermediateVoltageSource = new VoltageSource(this->getFirstNode(),intermediateNode,voltages[0],"__V");
    nodes.push_back(intermediateNode);
    elements.push_back(intermediateResistor);
    elements.push_back(intermediateVoltageSource);
}


