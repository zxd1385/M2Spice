//
// Created by Novin##### on 5/1/2025.
//

#include "VoltageSource.h"

VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double voltage,string vName): Element(firstNode,secondNode){
  this->voltage = voltage;
  this->vName = vName;
  this->dependency = "NAN";
}
VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double g,Node* firstNodeDepent,Node* secondNodeDependent,string vName):firstNodeDependent(firstNodeDepent),secondNodeDependent(secondNodeDependent),Gain(g), Element(firstNode,secondNode){
  this->vName = vName;
  this->dependency = "VCVS";
  this->voltage = 0;
}
VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double g,VoltageSource* voltageSourceDependent,string vName):voltageSourceDependent(voltageSourceDependent),Gain(g), Element(firstNode,secondNode){
  this->vName = vName;
  this->dependency = "CCVS";
  this->voltage = 0;
}
VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double amplitude,double offset,double frequency,string vName):Amplitude(amplitude),offset(offset),frequency(frequency),Element(firstNode,secondNode) {
  this->vName = vName;
  this->dependency = "SIN";
  this->voltage = offset;
  this->time = 0;
}
VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double initialVoltage,double voltageON,double timeDelay,double timeRise,double timeFall,int cycle,string vName):initialVoltage(initialVoltage),voltageON(voltageON),timeDelay(timeDelay),timeRise(timeRise),timeFall(timeRise),cycle(cycle),Element(firstNode,secondNode) {
  this->vName = vName;
  this->dependency = "PULSE";
  this->voltage = initialVoltage;
  this->time = 0;
  this->cycleNow = 0;
}


double VoltageSource::getVoltage(){
  return this->voltage;
}

void VoltageSource::setVoltage(double voltage){
  this->voltage = voltage;
}

string VoltageSource::getDependency() {
  return this->dependency;
}
double VoltageSource::getGain() {
  return this->Gain;
}
Node *VoltageSource::getFirstNodeDependent() {
  return this->firstNodeDependent;
}
Node *VoltageSource::getSecondNodeDependent() {
  return this->secondNodeDependent;
}
VoltageSource *VoltageSource::getVoltageSourceDependent() {
  return this->voltageSourceDependent;
}

