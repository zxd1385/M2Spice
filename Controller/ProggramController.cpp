//
// Created by Novin##### on 5/1/2025.
//

#include "ProggramController.h"
int ProggramController::addResistor(string name, string node1, string node2, string value) {

    if (stod(value) <= 0.0 ) {
        return 0;
    }
    if (name[0] != 'R') {
        return -1;
    }
    if (Elements.find(name) != Elements.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(stoi(node1.substr(1)));
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(stoi(node2.substr(1)));
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val ;
    if (value[value.size()-1] == 'k') {
        val = stod(value.substr(0, value.size()-1))*1000;
    }
    else if (value[value.size()-1] == 'm') {
        val = stod(value.substr(0, value.size()-1))/1000.0;
    }
    else if (value[value.size()-1] == 'u') {
        val = stod(value.substr(0, value.size()-1))/1000000.0;
    }
    else if (value[value.size()-1] == 'M') {
        val = stod(value.substr(0, value.size()-1))*1000000.0;
    }
    else if (value[value.size()-1] == 'n') {
        val = stod(value.substr(0, value.size()-1))/1000000000.0;
    }
    Resistor* resistor = new Resistor(Nodes[node1], Nodes[node2],val,name);
    Elements[name] = resistor;
    elements.push_back(resistor);
    return 1;

}
int ProggramController::addCapacitor(string name, string node1, string node2, string value) {
    if (stod(value) <= 0.0 ) {
        return 0;
    }
    if (name[0] != 'C') {
        return -1;
    }
    if (Elements.find(name) != Elements.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(stoi(node1.substr(1)));
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(stoi(node2.substr(1)));
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val ;
    if (value[value.size()-1] == 'k') {
        val = stod(value.substr(0, value.size()-1))*1000;
    }
    else if (value[value.size()-1] == 'm') {
        val = stod(value.substr(0, value.size()-1))/1000.0;
    }
    else if (value[value.size()-1] == 'u') {
        val = stod(value.substr(0, value.size()-1))/1000000.0;
    }
    else if (value[value.size()-1] == 'M') {
        val = stod(value.substr(0, value.size()-1))*1000000.0;
    }
    else if (value[value.size()-1] == 'n') {
        val = stod(value.substr(0, value.size()-1))/1000000000.0;
    }
    Capacitor* capacitor = new Capacitor(Nodes[node1],Nodes[node2],name,val,0.0,nodes,elements);
    Elements[name] = capacitor;
    elements.push_back(capacitor);
    return 1;
}
int ProggramController::addInductor(string name, string node1, string node2, string value) {
    if (stod(value) <= 0.0 ) {
        return 0;
    }
    if (name[0] != 'L') {
        return -1;
    }
    if (Elements.find(name) != Elements.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(stoi(node1.substr(1)));
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(stoi(node2.substr(1)));
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val ;
    if (value[value.size()-1] == 'k') {
        val = stod(value.substr(0, value.size()-1))*1000;
    }
    else if (value[value.size()-1] == 'm') {
        val = stod(value.substr(0, value.size()-1))/1000.0;
    }
    else if (value[value.size()-1] == 'u') {
        val = stod(value.substr(0, value.size()-1))/1000000.0;
    }
    else if (value[value.size()-1] == 'M') {
        val = stod(value.substr(0, value.size()-1))*1000000.0;
    }
    else if (value[value.size()-1] == 'n') {
        val = stod(value.substr(0, value.size()-1))/1000000000.0;
    }
    Inductor* inductor = new Inductor(Nodes[node1],Nodes[node2],name,val,0.0,nodes,elements);
    Elements[name] = inductor;
    elements.push_back(inductor);
    return 1;
}
int ProggramController::addDiode(string name, string node1, string node2, string type) {
    if (type != "D" && type != "Z" ) {
        return 0;
    }
    if (name[0] != 'D') {
        return -1;
    }
    if (Elements.find(name) != Elements.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(stoi(node1.substr(1)));
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(stoi(node2.substr(1)));
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val ;
    if (type=="D") {
        Diode* diode = new Diode(Nodes[node1],Nodes[node2],name,nodes,elements);
        Elements[name] = diode;
        elements.push_back(diode);
    }else if (type=="Z") {
        Diode* diode = new Diode(Nodes[node1],Nodes[node2],name,1e-14,1.5,0.02585,nodes,elements);
        Elements[name] = diode;
        elements.push_back(diode);
    }


    return 1;
}
int ProggramController::addGND(string node) {
    Nodes[node]->setNodeNumber(0);
    return 0;
}
int ProggramController::addVoltageSource(string name,string node1, string node2,string value) {
    if (name[0] != 'V') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(stoi(node1.substr(1)));
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(stoi(node2.substr(1)));
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val ;
    if (value[value.size()-1] == 'k') {
        val = stod(value.substr(0, value.size()-1))*1000;
    }
    else if (value[value.size()-1] == 'm') {
        val = stod(value.substr(0, value.size()-1))/1000.0;
    }
    else if (value[value.size()-1] == 'u') {
        val = stod(value.substr(0, value.size()-1))/1000000.0;
    }
    else if (value[value.size()-1] == 'M') {
        val = stod(value.substr(0, value.size()-1))*1000000.0;
    }
    else if (value[value.size()-1] == 'n') {
        val = stod(value.substr(0, value.size()-1))/1000000000.0;
    }
    VoltageSource* voltagesource = new VoltageSource(Nodes[node1],Nodes[node2],val,name);
    Elements[name] = voltagesource;
    elements.push_back(voltagesource);
    return 1;
}
int ProggramController::addCurrentSource(string name,string node1, string node2,string value) {
    if (name[0] != 'C') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(stoi(node1.substr(1)));
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(stoi(node2.substr(1)));
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val ;
    if (value[value.size()-1] == 'k') {
        val = stod(value.substr(0, value.size()-1))*1000;
    }
    else if (value[value.size()-1] == 'm') {
        val = stod(value.substr(0, value.size()-1))/1000.0;
    }
    else if (value[value.size()-1] == 'u') {
        val = stod(value.substr(0, value.size()-1))/1000000.0;
    }
    else if (value[value.size()-1] == 'M') {
        val = stod(value.substr(0, value.size()-1))*1000000.0;
    }
    else if (value[value.size()-1] == 'n') {
        val = stod(value.substr(0, value.size()-1))/1000000000.0;
    }
    CurrentSource* currentsource = new CurrentSource(Nodes[node1],Nodes[node2],val,name);
    Elements[name] = currentsource;
    elements.push_back(currentsource);
    return 1;
}



