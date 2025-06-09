//
// Created by Novin##### on 5/1/2025.
//

#ifndef CAPACITOR_H
#define CAPACITOR_H
#include <iostream>
#include <ostream>

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
    Capacitor(){};
    Capacitor(Node* firstNode,Node* secondNode,string cName, double capacitance, double initializedVoltage, vector<Node*> & nodes,  vector<Element*>& elements);
    virtual void updateVoltage(double voltage) {
        voltages.push_back(voltage);
    };
    double getValue() override {
        return capacitance;
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
    virtual void updateDynamicElements( vector<Node*> & nodes,  vector<Element*>& elements){
        intermediateResistor->setResistor(timeSteps/capacitance);
        for (auto& x : nodes) {
        if (x->getNodeNumber()!=0)
            x->setNodeNumber(x->getNodeNumber() + 1);
        }
        this->intermediateNode->setNodeNumber(1);
    };
    virtual void redoDynamicElements( vector<Node*> & nodes,  vector<Element*>& elements) {
        for (auto& x : nodes) {
            if (x->getNodeNumber()!=0)
                x->setNodeNumber(x->getNodeNumber() - 1);
        }
    };
    string getValueToSerialize() override {
        return "Capacitor " + cName + " " + to_string(capacitance) + " " + this->getFirstNode()->getName() + " " + this->getSecondtNode()->getName();
    };
    void DCswipeValue(double value) override {
        capacitance = value;
    };
    vector<double> getTRANCurrent() override {
        return this->intermediateVoltageSource->getTRANCurrent();
    }
    void ClearElement() override {
        this->voltages.clear();
    }
    ~Capacitor(){};

};



#endif //CAPACITOR_H
