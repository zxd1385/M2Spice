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
#include"fstream"
#include "regex"

class ProggramController {
private:
    vector<string> txtFiles;
    map<string,Node*> Nodes;
    map<string,Element*> Elements;
    vector<Element*> elements;
    vector<Node*> nodes;
    bool isGNDdetermined;
    MNAanalisis myAnalisis;
public:
    ProggramController() {
        isGNDdetermined = false;
    };
    ~ProggramController(){};

    map<string,Node*> getNodes() {
        return Nodes;
    };
    map<string,Element*> getElements() {
        return Elements;
    };

    void makeFolder(string name) {
        system(("if not exist " + name + " mkdir " + name).c_str());
    }
    void listAlltxtFiles() {
        std::string folder = "MousapourFolder";

        // 1. Run system command to list .txt files into a temp file
        std::string cmd = "dir /b \"" + folder + "\\*.txt\" > temp_output.txt";
        system(cmd.c_str());

        // 2. Read the temp file into a vector
        std::ifstream infile("temp_output.txt");
        std::string line;

        while (std::getline(infile, line)) {
            txtFiles.push_back(line);
        }

        infile.close();
    }
    int saveCurrentCircuit(string fileName) {
        std::string folderName = "MousapourFolder";

        // Construct the full path
        std::string filePath = folderName + "/" + fileName;

        // Open file in write mode (overwrite if exists)
        std::ofstream out(filePath);

        if (!out) {
            std::cerr << "Failed to open file for writing: " << filePath << std::endl;
            return 1;
        }

        // Write some lines
        for (auto x : Elements) {
            //cerr << x.first << endl;
            cout << x.second->getValueToSerialize() << endl;
            out << x.second->getValueToSerialize() << endl;
        }

        out.close();
    }
    int saveCurrentCircuitTOPath(string filePath) {
        //std::string folderName = "MousapourFolder";

        // Construct the full path
        //std::string filePath = folderName + "/" + fileName;

        // Open file in write mode (overwrite if exists)
        std::ofstream out(filePath);

        if (!out) {
            std::cerr << "Failed to open file for writing: " << filePath << std::endl;
            return 1;
        }

        // Write some lines
        for (auto x : Elements) {
            //cerr << x.first << endl;
            cout << x.second->getValueToSerialize() << endl;
            out << x.second->getValueToSerialize() << endl;
        }

        out.close();
    }
    int addResistor(string name, string node1, string node2, string value);
    int addCapacitor(string name, string node1, string node2, string value);
    int addInductor(string name, string node1, string node2, string value);
    int addDiode(string name, string node1, string node2, string type);
    int addGND(string node);
    int addVoltageSource(string name, string node1, string node2, string value);
    int addVSIN(string name, string node1, string node2, string amplitude, string offset, string frequency);
    int addVPULSE(string name, string node1, string node2, string initialVoltage, string voltageON, string timeDelay, string timeRise,string timeFall,string cycle);
    int addVCVS(string name, string node1, string node2, string gain, string firstNodeDependent, string secondNodeDependent);
    int addCCVS(string name, string node1, string node2, string gain, string voltageSourceDependent);
    int addCurrentSource(string name, string node1, string node2, string value);
    int addCCCS(string name, string node1, string node2, string gain,string dependentVoltageSource);
    int adVCCS(string name, string node1, string node2, string gain,string firstNodeDependent, string secondNodeDependent);
    int deletElement(string name);
    int printTransientVoltage(string step,string stop,string start,string maxStep, string node,vector<vector<double>>& results);
    int printTransientVoltageOfElement(string step,string stop,string start,string maxStep, string eName,vector<vector<double>>& results);
    int printTransientCurrentOfElement(string step,string stop,string start,string maxStep, string eName,vector<vector<double>>& results);
    int printDCSwipeVoltage(string name,string startval,string endval,string invreament, string node,vector<vector<double>>& results);
    int printDCSwipeVoltageOfElement(string name,string startval,string endval,string invreament, string eName,vector<vector<double>>& results);
    int printDCSwipeCurrentOfElement(string name,string startval,string endval,string invreament, string eName,vector<vector<double>>& results);
    vector<string> allCircuits() {
        txtFiles.clear();
        listAlltxtFiles();
        return txtFiles;
    }
    int closeFile() {
        isGNDdetermined = false;
        for (auto n: nodes) {
            delete n;
        }
        for (auto e: elements) {
            delete e;
        }
        nodes.clear();
        elements.clear();
        Nodes.clear();
        Elements.clear();
    }
    int renameNode(string node,string nodename) {
        if (Nodes.find(node) == Nodes.end()) {
            return 0;
        }
        Nodes[nodename] = Nodes[node];
        Nodes[nodename]->setName(nodename);
        Nodes.erase(node);
        return 1;
    }
    int renameElement(string element,string elementName) {
        if (Elements.find(element) == Elements.end()) {
            return 0;
        }
        Elements[elementName] = Elements[element];
        //Elements[elementName]->set
        Elements.erase(element);
        return 1;
    }
    int openNewSchemaic(string fileName) {
        std::string folder = "MousapourFolder";
        std::string filePath =  folder + "/" + fileName;
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return 1;
        }

        isGNDdetermined = false;
        for (auto n: nodes) {
            delete n;
        }
        for (auto e: elements) {
            delete e;
        }
        nodes.clear();
        elements.clear();
        Nodes.clear();
        Elements.clear();


        std::cout << "Reading file: " << filePath << std::endl;
        //regexes...
        regex ResistorAdd(R"(Resistor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex CapacitorAdd(R"(Capacitor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex InductorAdd(R"(Inductor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex DiodeDAdd(R"(Diode\s*D\s*(\S+)\s*(\S+)\s*)");
        regex DiodeZAdd(R"(Diode\s*Z\s*(\S+)\s*(\S+)\s*)");
        regex VoltageSourceAdd(R"(VoltageSource\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex VSINAdd(R"(VSIN\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex VPULSEAdd(R"(VPULSE\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex VCVSAdd(R"(VCVS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex CCVSAdd(R"(CCVS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex CCCSAdd(R"(CCCS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex VCCSAdd(R"(VCCS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex CurrentSourceAdd(R"(CurrentSource\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        // regex ResistorAdd(R"(Resistor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");

        std::string line;
        smatch match;
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
            if (regex_search(line,match, ResistorAdd)) {
                int status = this->addResistor(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, CapacitorAdd)) {
                int status = this->addCapacitor(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, InductorAdd)) {
                int status = this->addInductor(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, DiodeDAdd)) {
                int status = this->addDiode(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, DiodeZAdd)) {
                int status = this->addDiode(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, VoltageSourceAdd)) {
                int status = this->addVoltageSource(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, VSINAdd)) {
                int status = this->addVSIN(match[1],match[2],match[3],match[4],match[5],match[6]);
            }
            else if (regex_search(line,match, VPULSEAdd)) {
                int status = this->addVPULSE(match[1],match[2],match[3],match[4],match[5],match[6],match[7],match[8],match[9]);
            }
            else if (regex_search(line,match, VCVSAdd)) {
                int status = this->addVCVS(match[1], match[2], match[3], match[4],match[5],match[6]);
            }
            else if (regex_search(line,match, CCVSAdd)) {
                int status = this->addCCVS(match[1], match[2], match[3], match[4],match[5]);

            }
            else if (regex_search(line,match, CCCSAdd)) {
                int status = this->addCCCS(match[1], match[2], match[3], match[4],match[5]);
            }
            else if (regex_search(line,match, VCCSAdd)) {
                int status = this->adVCCS(match[1], match[2], match[3], match[4],match[5],match[6]);
            }
            else if (regex_search(line,match, CurrentSourceAdd)) {
                int status = this->addCurrentSource(match[1], match[3], match[4], match[2]);
            }
        }

        file.close();
        cout << " file: " << filePath << " opened succesfully" << std::endl;
        return 1;
    }
    int openNewSchemaicFromAnyPath(string filePath) {
        //std::string folder = "MousapourFolder";
        //std::string filePath =  folder + "/" + fileName;
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return 0;
        }

        isGNDdetermined = false;
        for (auto n: nodes) {
            delete n;
        }
        for (auto e: elements) {
            delete e;
        }
        nodes.clear();
        elements.clear();
        Nodes.clear();
        Elements.clear();


        std::cout << "Reading file: " << filePath << std::endl;
        //regexes...
        regex ResistorAdd(R"(Resistor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex CapacitorAdd(R"(Capacitor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex InductorAdd(R"(Inductor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex DiodeDAdd(R"(Diode\s*D\s*(\S+)\s*(\S+)\s*)");
        regex DiodeZAdd(R"(Diode\s*Z\s*(\S+)\s*(\S+)\s*)");
        regex VoltageSourceAdd(R"(VoltageSource\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        regex VSINAdd(R"(VSIN\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex VPULSEAdd(R"(VPULSE\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex VCVSAdd(R"(VCVS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex CCVSAdd(R"(CCVS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex CCCSAdd(R"(CCCS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex VCCSAdd(R"(VCCS\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*)");
        regex CurrentSourceAdd(R"(CurrentSource\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");
        // regex ResistorAdd(R"(Resistor\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+))");

        std::string line;
        smatch match;
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
            if (regex_search(line,match, ResistorAdd)) {
                int status = this->addResistor(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, CapacitorAdd)) {
                int status = this->addCapacitor(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, InductorAdd)) {
                int status = this->addInductor(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, DiodeDAdd)) {
                int status = this->addDiode(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, DiodeZAdd)) {
                int status = this->addDiode(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, VoltageSourceAdd)) {
                int status = this->addVoltageSource(match[1], match[3], match[4], match[2]);
            }
            else if (regex_search(line,match, VSINAdd)) {
                int status = this->addVSIN(match[1],match[2],match[3],match[4],match[5],match[6]);
            }
            else if (regex_search(line,match, VPULSEAdd)) {
                int status = this->addVPULSE(match[1],match[2],match[3],match[4],match[5],match[6],match[7],match[8],match[9]);
            }
            else if (regex_search(line,match, VCVSAdd)) {
                int status = this->addVCVS(match[1], match[2], match[3], match[4],match[5],match[6]);
            }
            else if (regex_search(line,match, CCVSAdd)) {
                int status = this->addCCVS(match[1], match[2], match[3], match[4],match[5]);

            }
            else if (regex_search(line,match, CCCSAdd)) {
                int status = this->addCCCS(match[1], match[2], match[3], match[4],match[5]);
            }
            else if (regex_search(line,match, VCCSAdd)) {
                int status = this->adVCCS(match[1], match[2], match[3], match[4],match[5],match[6]);
            }
            else if (regex_search(line,match, CurrentSourceAdd)) {
                int status = this->addCurrentSource(match[1], match[3], match[4], match[2]);
            }
        }

        file.close();
        cout << " file: " << filePath << " opened succesfully" << std::endl;
        return 1;
    }
    void ClearAll() {
        for (auto n: nodes) {
            n->ClearElement();
        }
        for (auto e: elements) {
            e->ClearElement();
        }
    }
    void clearFloatingNodesAfterClearElement() {
        map<string,int> nodeCounter;
        for (auto e: Elements) {
            //cerr << e.second->getFirstNode()->getName() << " " << e.second->getSecondtNode()->getName() << endl;
            nodeCounter[e.second->getFirstNode()->getName()]++;
            nodeCounter[e.second->getSecondtNode()->getName()]++;
        }
        vector<string> shouldBeDeletedNodes;
        for (auto n:Nodes) {
            //cout << "node " << n.second->getName() << endl;
            if (nodeCounter.find(n.first) == nodeCounter.end()) {
                shouldBeDeletedNodes.push_back(n.first);
            }
        }
        for (auto e:shouldBeDeletedNodes) {
            delete Nodes[e];
            Nodes.erase(e);
        }
    }
    void dynamicNodeNumbering() {
        int nodeNumber = 0;
        for (auto& n: Nodes) {
            if (n.second->getNodeNumber() != 0 ) {
                n.second->setNodeNumber(++nodeNumber);
            }
        }

    }
};



#endif //PROGGRAMCONTROLLER_H
