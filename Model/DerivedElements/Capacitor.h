//
// Created by Novin##### on 5/1/2025.
//

#ifndef CAPACITOR_H
#define CAPACITOR_H
#include "../Node.h"
#include <vector>
#include <string>

#include "Resistor.h"
#include "VoltageSource.h"
using namespace std;


class Capacitor : public Element {
public:
    string cName;
    double capacitance;
    Node* intermediateNode;
    VoltageSource* intermediateVoltageSource;
    Resistor* intermediateResistor;
    vector<double> voltages;

    Capacitor(Node* firstNode,Node* secondNode,string cName, double capacitance, double initializedVoltage, vector<Node*> & nodes,  vector<Element*>& elements);
    virtual void updateVoltage(double voltage) {
        voltages.push_back(voltage);
    };
    virtual string getType() {
        return "Capacitor";
    };
    virtual void updateValue(double value) {
        double voltage = voltages[voltages.size()-1] + intermediateNode->getVoltages()[intermediateNode->getVoltages().size()-1] - this->getSecondtNode()->getVoltages()[this->getSecondtNode()->getVoltages().size()-1] ;
        voltages.push_back(voltage);
        intermediateVoltageSource->setVoltage(voltage);
    };
    virtual double getAddedVoltage() {

    };
    ~Capacitor(){};

};



#endif //CAPACITOR_H
