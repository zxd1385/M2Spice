//
// Created by Novin##### on 5/1/2025.
//

#ifndef INDUCTOR_H
#define INDUCTOR_H
#include "../Node.h"
#include <vector>
#include <string>

#include "Resistor.h"
#include "CurrentSource.h"
using namespace std;


class Inductor : public Element {
public:
    string iName;
    double inductance;
    CurrentSource* intermediateCurrentSource;
    Resistor* intermediateResistor;
    vector<double> currents;

    Inductor(Node* firstNode,Node* secondNode,string iName, double inductance, double initializedCurrent, vector<Node*> & nodes,  vector<Element*>& elements);
    virtual void updateVoltage(double voltage) {
        currents.push_back(voltage);
    };
    virtual string getType() {
        return "Inductor";
    };
    virtual void updateValue(double value) {
        double current = currents[currents.size()-1] + (this->getFirstNode()->getVoltages()[this->getFirstNode()->getVoltages().size()-1] - this->getSecondtNode()->getVoltages()[this->getSecondtNode()->getVoltages().size()-1])/intermediateResistor->getResistor() ;
        currents.push_back(current);
        intermediateCurrentSource->setCurrent(current);
    };
    virtual void updateDynamicElements( vector<Node*> & nodes,  vector<Element*>& elements){
        intermediateResistor->setResistor(inductance/timeSteps);

    };
    virtual double getAddedVoltage() {

    };

    ~Inductor(){};

};



#endif //INDUCTOR_H
