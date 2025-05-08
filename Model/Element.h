//
// Created by Novin##### on 5/1/2025.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once
#include <string>
using namespace std;
class Node;


class Element {
    Node* firstNode;
    Node* secondNode;
    public:
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
};



#endif //ELEMENT_H
