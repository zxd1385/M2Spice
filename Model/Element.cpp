//
// Created by Novin##### on 5/1/2025.
//

#include "Element.h"
Element::Element(Node* firsttNode,Node* secondNode) {
    this->firstNode = firsttNode;
    this->secondNode = secondNode;
}
void Element::setFirstNode(Node *node) {
    this->firstNode = node;
}
void Element::setSecondtNode(Node *node) {
    this->secondNode = node;
}
Node* Element::getFirstNode() {
    return this->firstNode;
}
Node *Element::getSecondtNode() {
    return this->secondNode;
}




