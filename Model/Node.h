//
// Created by Novin##### on 5/1/2025.
//

#ifndef NODE_H
#define NODE_H
#pragma once
#include <vector>
#include "Element.h"
using namespace std;



class Node {
private:
    int nodeNumber;
    static double timeSteps;
    static double startTime;
    static double endTime;
    vector<double> nodeVoltages;
    vector<Element*> elements;
    public:
      Node(int nodeNumber);
      ~Node();
      static double getTimeSteps();
      static double getStartTime();
      static double getEndTime();
      vector<Element*> getNodes();
      void addElement(Element* element);
      void removeElement(Element* element);
      void addVoltage(double voltage);
      void removeVoltage();
      void setNodeNumber(int nodeNumber);
      int getNodeNumber();
      vector<double> getVoltages();

};



#endif //NODE_H
