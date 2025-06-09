//
// Created by Novin##### on 5/1/2025.
//

#include "ProggramController.h"
#include <fstream>
double convert(string value) {
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
    else {
        val = stod(value);
    }
    return val;
}



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
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(value);
    //cerr << val << endl;
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
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(value);
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
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(value);
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
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
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
    isGNDdetermined = true;
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
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(value);
    VoltageSource* voltagesource = new VoltageSource(Nodes[node1],Nodes[node2],val,name);
    Elements[name] = voltagesource;
    elements.push_back(voltagesource);
    return 1;
}
int ProggramController::addVSIN(string name, string node1, string node2, string amplitude, string offset, string frequency) {
    if (name[0] != 'V') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double amp = convert(amplitude);
    double ofset = convert(offset);
    double freq = convert(frequency);
    VoltageSource* voltagesource = new VoltageSource(Nodes[node1],Nodes[node2],amp,ofset,freq,name);
    Elements[name] = voltagesource;
    elements.push_back(voltagesource);
    return 1;
}
int ProggramController::addVPULSE(string name, string node1, string node2, string initialVoltage, string voltageON, string timeDelay, string timeRise, string timeFall, string cycle) {
    if (name[0] != 'V') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double iniv = convert(initialVoltage);
    double voltageon = convert(voltageON);
    double timedelay = convert(timeDelay);
    double timerise = convert(timeRise);
    double timefall = convert(timeFall);
    double cycl = convert(cycle);
    VoltageSource* voltagesource = new VoltageSource(Nodes[node1],Nodes[node2],iniv,voltageon,timedelay,timerise,timefall,cycl,name);
    Elements[name] = voltagesource;
    elements.push_back(voltagesource);
    return 1;
}

int ProggramController::addVCVS(string name, string node1, string node2, string gain, string firstNodeDependent, string secondNodeDependent) {
    if (name[0] != 'V') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }
    if (Nodes.find(firstNodeDependent) == Nodes.end() || Nodes.find(secondNodeDependent) == Nodes.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(gain);
    VoltageSource* voltagesource = new VoltageSource(Nodes[node1],Nodes[node2],val,Nodes[node1],Nodes[node2],name);
    Elements[name] = voltagesource;
    elements.push_back(voltagesource);
    return 1;
}
int ProggramController::addCCVS(string name, string node1, string node2, string gain, string voltageSourceDependent) {
    if (name[0] != 'V') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }
    if (Elements.find(voltageSourceDependent) == Elements.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(gain);
    VoltageSource* voltagesource = new VoltageSource(Nodes[node1],Nodes[node2],val,dynamic_cast<VoltageSource*>(Elements[voltageSourceDependent]),name);
    Elements[name] = voltagesource;
    elements.push_back(voltagesource);
    return 1;
}
int ProggramController::addCCCS(string name, string node1, string node2, string gain, string dependentVoltageSource) {
    if (name[0] != 'C') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }
    if (Elements.find(dependentVoltageSource) == Elements.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }

    double val = convert(gain);
    CurrentSource* currentsource = new CurrentSource(Nodes[node1],Nodes[node2],dynamic_cast<VoltageSource *>(Elements[dependentVoltageSource]),val,name);
    Elements[name] = currentsource;
    elements.push_back(currentsource);
    return 1;
}
int ProggramController::adVCCS(string name, string node1, string node2, string gain, string firstNodeDependent, string secondNodeDependent) {
    if (name[0] != 'C') {
        return 0;
    }
    if (Elements.find(name) != Elements.end()) {
        return -1;
    }
    if (Nodes.find(firstNodeDependent) == Nodes.end() || Nodes.find(secondNodeDependent) == Nodes.end()) {
        return -2;
    }

    if (Nodes.find(node1) == Nodes.end()) {
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }

    double val = convert(gain);
    CurrentSource* currentsource = new CurrentSource(Nodes[node1],Nodes[node2],Nodes[firstNodeDependent],Nodes[secondNodeDependent],val,name);
    Elements[name] = currentsource;
    elements.push_back(currentsource);
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
        Node* newNode = new Node(-1,node1);
        Nodes[node1] = newNode;
        nodes.push_back(newNode);
    }
    if (Nodes.find(node2) == Nodes.end()) {
        Node* newNode = new Node(-1,node2);
        Nodes[node2] = newNode;
        nodes.push_back(newNode);
    }
    double val = convert(value);
    CurrentSource* currentsource = new CurrentSource(Nodes[node1],Nodes[node2],val,name);
    Elements[name] = currentsource;
    elements.push_back(currentsource);
    return 1;
}
int ProggramController::deletElement(string name) {
    if (Elements.find(name) == Elements.end()) {
        return 0;
    }
    delete Elements[name];
    Elements.erase(name);
    this->clearFloatingNodesAfterClearElement();
    return 1;
}




int ProggramController::printTransientVoltage(string step, string stop, string start, string maxStep, string node,vector<vector<double>>& results ) {
    if (Nodes.find(node) == Nodes.end()) {
        return 0;
    }
    if (!isGNDdetermined) {
        return -1;
    }
    ClearAll();
    double currentTime = convert(step);
    Element::timeSteps = convert(step);
    double Tstop = convert(stop);
    double Tstart = convert(start);
    double Tmax = convert(maxStep);
    cerr <<  currentTime << " " << Tstop << " " << step << " " << Tstart << endl;
    myAnalisis.setBasicVectors(nodes,elements);
    myAnalisis.simulateCircuit(Tstop,Element::timeSteps);

    vector <double> voltages = Nodes[node]->getVoltages();
    for (auto v : voltages) {
        cerr << v << endl;
        if (currentTime > Tstart && currentTime < Tstop && results.size() < Tmax) {
            results.push_back({currentTime,v});
        }
        currentTime += Element::timeSteps;
    }
    return 1;

}
int ProggramController::printTransientVoltageOfElement(string step, string stop, string start, string maxStep, string eName, vector<vector<double> > &results) {
    if (Elements.find(eName) == Elements.end()) {
        return 0;
    }
    if (!isGNDdetermined) {
        return -1;
    }
    ClearAll();
    double currentTime = convert(step);
    Element::timeSteps = convert(step);
    double Tstop = convert(stop);
    double Tstart = convert(start);
    double Tmax = convert(maxStep);
    //cerr <<  currentTime << " " << Tstop << " " << step << " " << Tstart << endl;
    this->dynamicNodeNumbering();
    myAnalisis.setBasicVectors(nodes,elements);
    myAnalisis.simulateCircuit(Tstop,Element::timeSteps);

    vector <double> voltages1 = Elements[eName]->getFirstNode()->getVoltages();
    vector<double> voltages2 = Elements[eName]->getSecondtNode()->getVoltages();
    for (int i = 0; i < voltages1.size(); i++) {
        //cerr << v << endl;
        if (currentTime > Tstart && currentTime < Tstop && results.size() < Tmax) {
            results.push_back({currentTime,voltages1[i]-voltages2[i]});
        }
        currentTime += Element::timeSteps;
    }
    return 1;
}
int ProggramController::printTransientCurrentOfElement(string step, string stop, string start, string maxStep, string eName, vector<vector<double> > &results) {
    if (Elements.find(eName) == Elements.end()) {
        return 0;
    }
    if (!isGNDdetermined) {
        return -1;
    }
    ClearAll();
    double currentTime = convert(step);
    Element::timeSteps = convert(step);
    double Tstop = convert(stop);
    double Tstart = convert(start);
    double Tmax = convert(maxStep);
    //cerr <<  currentTime << " " << Tstop << " " << step << " " << Tstart << endl;
    myAnalisis.setBasicVectors(nodes,elements);
    myAnalisis.simulateCircuit(Tstop,Element::timeSteps);

    vector <double> currents = Elements[eName]->getTRANCurrent();
    for (auto v : currents) {
        cerr << v << endl;
        if (currentTime > Tstart && currentTime < Tstop && results.size() < Tmax) {
            results.push_back({currentTime,v});
        }
        currentTime += Element::timeSteps;
    }
    return 1;
}
int ProggramController::printDCSwipeVoltage(string name, string startval, string endval, string invreament, string node, vector<vector<double> > &results) {
    if (Nodes.find(node) == Nodes.end()) {
        return 0;
    }
    if (Elements.find(name) == Elements.end()) {
        return -1;
    }
    if (!isGNDdetermined) {
        return -2;
    }
    ClearAll();
    double Sval = convert(startval);
    double Eval = convert(endval);
    double inv = convert(invreament);
    myAnalisis.setBasicVectors(nodes,elements);
    myAnalisis.DCswipe(Sval,Eval,inv,Elements[name]);
    vector<double> viltages = Nodes[node]->getVoltages();
    double currntval = Sval;
    for (auto v : viltages) {
        results.push_back({currntval,v});
        currntval += inv;
    }
    return 1;
}
int ProggramController::printDCSwipeVoltageOfElement(string name, string startval, string endval, string invreament, string eName, vector<vector<double> > &results) {
    if (Elements.find(eName) == Elements.end()) {
        return 0;
    }
    if (Elements.find(name) == Elements.end()) {
        return -1;
    }
    if (!isGNDdetermined) {
        return -2;
    }
    ClearAll();
    double Sval = convert(startval);
    double Eval = convert(endval);
    double inv = convert(invreament);
    myAnalisis.setBasicVectors(nodes,elements);
    myAnalisis.DCswipe(Sval,Eval,inv,Elements[name]);
    vector <double> voltages1 = Elements[eName]->getFirstNode()->getVoltages();
    vector<double> voltages2 = Elements[eName]->getSecondtNode()->getVoltages();
    double currntval = Sval;
    for (int i = 0; i < voltages1.size(); i++) {
        //cerr << v << endl;

        results.push_back({currntval,voltages1[i]-voltages2[i]});
        currntval += inv;
    }
    return 1;
}
int ProggramController::printDCSwipeCurrentOfElement(string name, string startval, string endval, string invreament, string eName, vector<vector<double> > &results) {
    if (Elements.find(eName) == Elements.end()) {
        return 0;
    }
    if (Elements.find(name) == Elements.end()) {
        return -1;
    }
    if (!isGNDdetermined) {
        return -2;
    }
    ClearAll();
    double Sval = convert(startval);
    double Eval = convert(endval);
    double inv = convert(invreament);
    myAnalisis.setBasicVectors(nodes,elements);
    myAnalisis.DCswipe(Sval,Eval,inv,Elements[name]);
    vector <double> currents = Elements[eName]->getTRANCurrent();
    double currntval = Sval;
    for (int i = 0; i < currents.size(); i++) {
        //cerr << v << endl;

        results.push_back({currntval,currents[i]});
        currntval += inv;
    }
    return 1;
}





