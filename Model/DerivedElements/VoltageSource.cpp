//
// Created by Novin##### on 5/1/2025.
//

#include "VoltageSource.h"

#include "../Node.h"

string VoltageSource::getValueToSerialize() {
  if (this->getDependency() == "NAN") {
    return "VoltageSource " + this->getName() + " " + to_string(voltage) + " " + this->getFirstNode()->getName() + " " + this->getSecondtNode()->getName();
  }else if (this->getDependency() == "VCVS") {
    return "VCVS " + this->getName() + " " + this->getFirstNode()->getName() + " " + this->getSecondtNode()->getName() + " " +  to_string(this->getGain()) + " " + this->getFirstNodeDependent()->getName() + " " + this->getSecondNodeDependent()->getName();
  }else if (this->getDependency() == "CCVS") {
    return "CCVS " + this->getName() + " " + this->getFirstNode()->getName() + " " + this->getSecondtNode()->getName() + " " +  to_string(this->getGain()) + " " + this->getVoltageSourceDependent()->getName();
  }else if (this->getDependency() == "SIN") {
    return "VSIN " + this->getName() + " " + this->getFirstNode()->getName() + " " + this->getSecondtNode()->getName() + " " +  to_string(this->getAmplitude()) + " " + to_string(this->getOffset()) + " " + to_string(this->getFrequency());
  }else if (this->getDependency() == "PULSE") {
    return "VPULSE " + this->getName() + " " + this->getFirstNode()->getName() + " " + this->getSecondtNode()->getName() + " " +  to_string(this->getInitialVoltage()) + " " + to_string(this->getVoltageON()) + " " + to_string(this->getTimeDelay()) + " " + to_string(this->getTimeRise()) + " " + to_string(this->getTimeFall()) + " " + to_string(this->getCycle());
  }
}
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
VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double initialVoltage,double voltageON,double timeDelay,double timeRise,double timeFall,int cycle,string vName):initialVoltage(initialVoltage),voltageON(voltageON),timeDelay(timeDelay),timeRise(timeRise),timeFall(timeFall),cycle(cycle),Element(firstNode,secondNode) {
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

