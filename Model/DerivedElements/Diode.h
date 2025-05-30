//
// Created by Novin##### on 5/23/2025.
//

#ifndef DIODE_H
#define DIODE_H
#include <iostream>
#include <ostream>

#include "../Element.h"
#include "CurrentSource.h"
#include "Resistor.h"
#include "../Node.h"


class Diode : public Element{
    private:
    string dName;
    double Is;
    double n;
    double VT;
    double currentVoltage;
    CurrentSource* intermediateCurrentSource;
    Resistor* intermediateResistor;
    Node* intermediateNode;
    vector<Element*> elements;
    bool isZener;
    public:
    Diode(Node* firstNode,Node* secondNode,string dName,double Is, double n,double VT,vector<Node*> & nodes,  vector<Element*>& elements);
    Diode(Node* firstNode,Node* secondNode,string dName,vector<Node*> & nodes,  vector<Element*>& elements);
    double linearizedConductance() {
        return Is*exp(min(40.0,currentVoltage/(n*VT)))/(n*VT);
    };
    double getCharachteristichCurve(double v) {
        return Is*(exp(min(40.0,v/(n*VT)))-1);
    };
    virtual string getType() {
        return "Diode";
    };
    virtual double getValue() {
        return Is;
    };
    virtual void updateValue(double value) {
        double v = this->getFirstNode()->getVoltages()[this->getFirstNode()->getVoltages().size()-1] - this->getSecondtNode()->getVoltages()[this->getSecondtNode()->getVoltages().size()-1];
        //cerr << currentVoltage << " " << v << endl;
        //intermediateResistor->changeMainValue(123);

        if (isZener) {
            if (abs(v- currentVoltage)<-1e8) {
                return;
            }
            else {
                //cerr<<"Current Voltage: "<<v<<endl;
                currentVoltage = v;
                // Clamp conductance to avoid division by near-zero or overflow
                double G = linearizedConductance(); // Min 1 μS to avoid R > 1M
                //G = G; // Max 1 kS to avoid R < 1 mΩ

                double R = 1.0 / G;

                // Set the clamped resistor
                intermediateResistor->changeMainValue(R);

                // Compute the current using safely clamped R
                double I = getCharachteristichCurve(currentVoltage) - v * G;
                intermediateCurrentSource->setCurrent(I);

                // Update voltage tracking

            }
        }
        else {
            if (v > 0 && this->intermediateResistor->getResistor() == 10000000 ) {

                this->intermediateResistor->changeMainValue(0.00001);
            }
            if (v<0 && this->intermediateResistor->getResistor() == 0.00001) {
                this->intermediateResistor->changeMainValue(10000000);

            }
        }






    };




};



#endif //DIODE_H
