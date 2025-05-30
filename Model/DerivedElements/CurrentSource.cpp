//
// Created by Novin##### on 5/1/2025.
//

#include "CurrentSource.h"

#include "../Node.h"

CurrentSource::CurrentSource(Node* firstNode,Node* secondNode,double current , string cName): current(current), cName(cName), Element(firstNode,secondNode) {
  this->dependency = "NAN";
  }
CurrentSource::CurrentSource(Node* firstNode,Node* secondNode,Node* firstNodeDependent,Node* secondNodeDependent,double g, string cName):dependency("VCCS") ,cName(cName), firstNodeDependent(firstNodeDependent),secondNodeDependent(secondNodeDependent),Gain(g), Element(firstNode,secondNode) {

}
CurrentSource::CurrentSource(Node* firstNode,Node* secondNode,VoltageSource* voltageSourceDependent,double g, string cName):dependency("CCCS") ,cName(cName),voltageSourceDependent(voltageSourceDependent),Gain(g), Element(firstNode,secondNode){}

void CurrentSource::setCurrent(double current) {
  this->current = current;
}

double CurrentSource::getCurrent() {
  return this->current;
}
double CurrentSource::getGain() {
  return this->Gain;
}
int CurrentSource::getFirstNodeDepent() {
  return this->firstNodeDependent->getNodeNumber();
}
int CurrentSource::getSecondNodeDepent() {
  return this->secondNodeDependent->getNodeNumber();
}
string CurrentSource::getDependency() {
  return this->dependency;
}
VoltageSource *CurrentSource::getVoltageSourceDependent() {
  return this->voltageSourceDependent;
}


