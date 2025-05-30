//
// Created by Novin##### on 5/1/2025.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once
#include <string>
#include <vector>
using namespace std;
class Node;


class Element {
    Node* firstNode;
    Node* secondNode;

    public:
    static double timeSteps;
    Element(){};
    Element(Node* firstNode,Node* secondNode);
    ~Element(){};
    Node* getFirstNode();
    Node* getSecondtNode();
    void setFirstNode(Node* node);
    void setSecondtNode(Node* node);
    virtual void similate(){};
    virtual string getType(){};
    virtual double getValue(){};
    virtual void updateValue(double value){};
    virtual double getAddedVoltage(){};
    virtual void addValue(double,string){};
    virtual void updateDynamicElements( vector<Node*> & nodes,  vector<Element*>& elements){};
    virtual void redoDynamicElements( vector<Node*> & nodes,  vector<Element*>& elements){};
    virtual bool isSwitch(){};
};



#endif //ELEMENT_H
