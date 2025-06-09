//
// Created by Novin##### on 5/1/2025.
//

#ifndef CURRENTSOURCE_H
#define CURRENTSOURCE_H
#include "VoltageSource.h"
#include "../Element.h"


class CurrentSource : public Element {
  private:
    string cName;
    double current;
    string dependency;
    double Gain;
    Node* firstNodeDependent;
    Node* secondNodeDependent;
    VoltageSource* voltageSourceDependent;

    public:
    CurrentSource(){};
      CurrentSource(Node* firstNode,Node* secondNode,double current, string cName);
    CurrentSource(Node* firstNode,Node* secondNode,Node* firstNodeDependent,Node* secondNodeDependent,double g, string cName);
    CurrentSource(Node* firstNode,Node* secondNode,VoltageSource* voltageSourceDependent,double g, string cName);
      double getCurrent();
      void setCurrent(double current);
    string getDependency();
    int getFirstNodeDepent();
    int getSecondNodeDepent();
    VoltageSource* getVoltageSourceDependent();
    double getGain();
    virtual string getType() {
        return "CurrentSource";
    };
    virtual double getValue() {
        return current;
    };
    string getName() {
        return cName;
    };
    Node* getFirstNodeDependentPointer() {
        return firstNodeDependent;
    }
    Node* getSecondNodeDependentPointer() {
        return secondNodeDependent;
    }
    void DCswipeValue(double value) override {
        current = value;
    };
    string getValueToSerialize() override;


};



#endif //CURRENTSOURCE_H
