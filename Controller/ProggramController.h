//
// Created by Novin##### on 5/1/2025.
//

#ifndef PROGGRAMCONTROLLER_H
#define PROGGRAMCONTROLLER_H
#include"../Model/DerivedElements/Capacitor.h"
#include"../Model/DerivedElements/Inductor.h"
#include"../Model/DerivedElements/VoltageSource.h"
#include"../Model/Element.h"
#include"../Model/DerivedElements/Resistor.h"
#include"../Model/DerivedElements/Diode.h"
#include"../Model/DerivedElements/CurrentSource.h"
#include"../Model/Node.h"
#include"../Model/Graph.h"
#include"../Model/Circuit.h"
#include "AnalisisAlgorithms/MNAanalisis.h"

class ProggramController {
private:
    map<string,Node*> Nodes;
    map<string,Element*> Elements;
    vector<Element*> elements;
    vector<Node*> nodes;
    MNAanalisis* myAnalisis;
public:
    ProggramController(){};
    ~ProggramController(){};

    int addResistor(string name, string node1, string node2, string value);
    int addCapacitor(string name, string node1, string node2, string value);
    int addInductor(string name, string node1, string node2, string value);
    int addDiode(string name, string node1, string node2, string type);
    int addGND(string node);
    int addVoltageSource(string name, string node1, string node2, string value);
    int addCurrentSource(string name, string node1, string node2, string value);
    int deleteResistor(string name);
};



#endif //PROGGRAMCONTROLLER_H
