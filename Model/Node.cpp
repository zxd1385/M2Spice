//
// Created by Novin##### on 5/1/2025.
//

#include "Node.h"
#include <vector>

double Node::timeSteps = 0.0;
double Node::startTime = 0.0;
double Node::endTime = 0.0;

using namespace std;
Node::Node(int nodeNumber, string nName){
  this->nodeNumber = nodeNumber;
  this->nName = nName;
}
int Node::getNodeNumber(){
  return this->nodeNumber;
}

void Node::setNodeNumber(int nodeNumber){
  this->nodeNumber = nodeNumber;
}

double Node::getTimeSteps(){
  return timeSteps;
}

double Node::getStartTime(){
  return startTime;
}
double Node::getEndTime(){
  return endTime;
}
vector<Element*> Node::getNodes(){
  return elements;
}
void Node::addElement(Element* element){
  elements.push_back(element);
}
void Node::removeElement(Element* element){
  for(int i = 0; i < elements.size(); i++){
    if(elements[i] == element){
      elements.erase(elements.begin() + i);
    }
  }


}
void Node::addVoltage(double voltage){
  nodeVoltages.push_back(voltage);
}
void Node::removeVoltage(){
  nodeVoltages.clear();
}
vector<double> Node::getVoltages(){
  return nodeVoltages;
}
