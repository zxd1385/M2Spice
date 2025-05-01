//
// Created by Novin##### on 5/1/2025.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include "Node.h"


class Element {
    Node* firstNode;
    Node* secondNode;
    public:
    Element(Node* firstNode,Node* secondNode);
    ~Element();
    Node* getFirstNode();
    Node* getSecondtNode();
    void setFirstNode(Node* node);
    void setSecondtNode(Node* node);
};



#endif //ELEMENT_H
