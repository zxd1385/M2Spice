//
// Created by Novin##### on 5/1/2025.
//

#include "VoltageSource.h"

VoltageSource::VoltageSource(Node* firstNode,Node* secondNode,double voltage,string vName): Element(firstNode,secondNode){
  this->voltage = voltage;
  this->vName = vName;
}
double VoltageSource::getVoltage(){
  return this->voltage;
}

void VoltageSource::setVoltage(double voltage){
  this->voltage = voltage;
}

