//
// Created by Novin##### on 5/1/2025.
//

#include "CurrentSource.h"

CurrentSource::CurrentSource(Node* firstNode,Node* secondNode,double current , string cName): current(current), cName(cName), Element(firstNode,secondNode) {
  }

void CurrentSource::setCurrent(double current) {
  this->current = current;
}

double CurrentSource::getCurrent() {
  return this->current;
}