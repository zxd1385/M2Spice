//
// Created by Novin##### on 5/1/2025.
//

#include "Resistor.h"

Resistor::Resistor(Node *firstNode, Node *secondNode, double R, string rName): resistor(R) , Element(firstNode, secondNode) {
    resistor_map[rName] = R;
}
double Resistor::getResistor() {
    return this->resistor;
}
void Resistor::setResistor(double R) {
    this->resistor = R;
}

