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
    string nName;
    int nodeNumber;
    static double timeSteps;
    static double startTime;
    static double endTime;
    vector<double> nodeVoltages;
    vector<Element*> elements;
    public:
    Node(){};
      Node(int nodeNumber,string nName);
      ~Node(){};
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
    void setName(string name) {
        this->nName = nName;
    };
    string getName() {
        return nName;
    };
    void ClearElement()  {
        this->nodeVoltages.clear();
    }
      vector<double> getVoltages();

};



#endif //NODE_H
