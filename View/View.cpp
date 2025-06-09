//
// Created by Novin##### on 5/1/2025.
//

#include "View.h"
#include <regex>
void View::run() {
    string currentCircuit = "No Schematic has been opened yet!";
    //add|delet elements...
    regex AddResistor(R"(\s*add\s{1}Resistor\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddCapacitor(R"(\s*add\s{1}Capacitor\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddInductor(R"(\s*add\s{1}Inductor\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddDiode(R"(\s*add\s{1}Diode\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddGND(R"(\s*add\s{1}GND\s{1}(\S+)\s*)");
    regex AddVoltageSource(R"(\s*add\s{1}VoltageSource\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddVSIN(R"(\s*add\s{1}VSIN\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddVPULSE(R"(\s*add\s{1}VPULSE\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddVCVS(R"(\s*add\s{1}VCVS\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddCCVS(R"(\s*add\s{1}CCVS\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddCurrentSource(R"(\s*add\s{1}CurrentSource\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddCCCS(R"(\s*add\s{1}CCCS\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddVCCS(R"(\s*add\s{1}VCCS\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex DeletElement(R"(\s*delet\s{1}(\S+)\s*)");

    //outputs...
    regex PrintTransientVoltage (R"(\s*\.print\s{1}TRAN\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}V(\S+)\s*)");
    regex PrintTransientVoltageOfElement (R"(\s*\.print\s{1}Element\s{1}TRAN\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}V(\S+)\s*)");
    regex PrintTransientCurrentOfElement (R"(\s*\.print\s{1}Element\s{1}TRAN\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}C(\S+)\s*)");
    regex PrintDCSwipeVoltageOfElement (R"(\s*\.print\s{1}Element\s{1}DC\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}V(\S+)\s*)");
    regex PrintDCSwipeCurrentOfElement (R"(\s*\.print\s{1}Element\s{1}DC\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}C(\S+)\s*)");
    regex PrintDCSwipeVoltage (R"(\s*\.print\s{1}DC\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}V(\S+)\s*)");
    regex ShowNodeList(R"(\s*show\s*node\s*list\s*)");
    regex ShowElementList(R"(\s*show\s*element\s*list\s*)");
    regex ShowBoothList(R"(\s*show\s*booth\s*list\s*)");
    regex Open(R"(\s*open\s*(\S+)\s*)");

    //save...
    regex SaveCurrentCircuit(R"(\s*save\s*as\s*(\S+)\s*)");
    regex ShowAllCircuits(R"(\s*show\s*all\s*circuits\s*)");
    regex CurrentSchematic(R"(\s*current\s*circuit\s*)");
    regex SaveCurrentSchematic(R"(\s*save\s*)");
    regex SaveCurrentSchematicTOPath(R"(\s*external\s*save\s*(\S+)\s*)");
    regex CloseCurrentSchematic(R"(\s*close\s*)");





    smatch match;
    string entry;
    while (getline(cin, entry)) {
        if (regex_search(entry, match, AddResistor)) {
            int status = controller.addResistor(match[1], match[2], match[3], match[4]);
            if (status==0) {
                cout << "Error: Resistance can not be negative!" << endl;
            }
            else if (status==-1) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Resistor " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "Resistor " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddCapacitor)) {
            int status = controller.addCapacitor(match[1], match[2], match[3], match[4]);
            if (status==0) {
                cout << "Error: Capacitance can not be negative!" << endl;
            }
            else if (status==-1) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Capacitor " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "Capacitor " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddInductor)) {
            int status = controller.addInductor(match[1], match[2], match[3], match[4]);
            if (status==0) {
                cout << "Error: Inductance can not be negative!" << endl;
            }
            else if (status==-1) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Inductor " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "Inductor " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddDiode)) {
            int status = controller.addDiode(match[1], match[2], match[3], match[4]);
            if (status==0) {
                cout << "Error: Model " << match[4] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Diode " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "Diode " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddGND)) {
            int status = controller.addGND(match[1]);
            if (status==0) {
                cout  << match[1] << " set as GND succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddVoltageSource)) {
            int status = controller.addVoltageSource(match[1], match[2], match[3], match[4]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: VoltageSource " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "VoltageSource " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddVSIN)) {
            int status = controller.addVSIN(match[1],match[2],match[3],match[4],match[5],match[6]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: VSIN " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "VSIN " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddVPULSE)) {
            int status = controller.addVPULSE(match[1],match[2],match[3],match[4],match[5],match[6],match[7],match[8],match[9]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: VPULSE " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "VPULSE " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddVCVS)) {
            int status = controller.addVCVS(match[1], match[2], match[3], match[4],match[5],match[6]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: VCVS " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Dependent Nodes doesnt Exist!" << endl;
            }
            else if (status==1) {
                cout << "VCVS " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddCCVS)) {
            int status = controller.addVCVS(match[1], match[2], match[3], match[4],match[5],match[6]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: CCVS " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Dependent VoltageSource doesnt Exist!" << endl;
            }
            else if (status==1) {
                cout << "VCVS " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddCurrentSource)) {
            int status = controller.addCurrentSource(match[1], match[2], match[3], match[4]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: CurrentSource " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==1) {
                cout << "CurrentSource " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddCCCS)) {
            int status = controller.addCCCS(match[1], match[2], match[3], match[4],match[5]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: CCCS " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Dependent VoltageSource doesnt Exist!" << endl;
            }
            else if (status==1) {
                cout << "CCCS " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, AddVCCS)) {
            int status = controller.addCCCS(match[1], match[2], match[3], match[4],match[5]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in library!" << endl;
            }
            else if (status==-1) {
                cout << "Error: VCCS " << match[1] << " already exists in the circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: Dependent Nodes doesnt Exist!" << endl;
            }
            else if (status==1) {
                cout << "VCCS " << match[1] << " added succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, DeletElement)) {
            int status = controller.deletElement(match[1]);
            if (status==0) {
                cout << "Error: Element " << match[1] << " not found in the circuit!" << endl;
            }else if (status==1) {
                cout << "Element " << match[1] << " deleted succesfully!" << endl;
            }
        }
        else if (regex_search(entry, match, PrintTransientVoltage)) {
            vector<vector<double>> results;
            int status = controller.printTransientVoltage(match[1], match[2], match[3], match[4],match[5],results);
            if (status==0) {
                cout << "Node " << match[5] << " not found in the circuit!" << endl;
            }
            else if (status==-1) {
                cout << "Error: GND is not Determined Yet!" << endl;
            }
            else if (status==1) {
                cout << "Node " << match[5] << " voltages at time:" << endl;
                for (int i = 0; i < results.size(); i++) {
                    cout << results[i][0] << ": " << results[i][1]  << endl;
                }
            }
        }
        else if (regex_search(entry, match, PrintTransientVoltageOfElement)) {
            vector<vector<double>> results;
            int status = controller.printTransientVoltageOfElement(match[1], match[2], match[3], match[4],match[5],results);
            if (status==0) {
                cout << "Element " << match[5] << " not found in the circuit!" << endl;
            }
            else if (status==-1) {
                cout << "Error: GND is not Determined Yet!" << endl;
            }
            else if (status==1) {
                cout << "Element " << match[5] << " leg voltage at time:" << endl;
                for (int i = 0; i < results.size(); i++) {
                    cout << results[i][0] << ": " << results[i][1]  << endl;
                }
            }
        }
        else if (regex_search(entry, match, PrintTransientCurrentOfElement)) {
            vector<vector<double>> results;
            int status = controller.printTransientCurrentOfElement(match[1], match[2], match[3], match[4],match[5],results);
            if (status==0) {
                cout << "Element " << match[5] << " not found in the circuit!" << endl;
            }
            else if (status==-1) {
                cout << "Error: GND is not Determined Yet!" << endl;
            }
            else if (status==1) {
                cout << "Element " << match[5] << " current at time:" << endl;
                for (int i = 0; i < results.size(); i++) {
                    cout << results[i][0] << ": " << results[i][1]  << endl;
                }
            }
        }
        else if (regex_search(entry, match, PrintDCSwipeVoltage)) {
            vector<vector<double>> results;
            int status = controller.printDCSwipeVoltage(match[1], match[2], match[3], match[4],match[5],results);
            if (status==0) {
                cout << "Node " << match[5] << " not found in the circuit!" << endl;
            }
            else if (status==-1) {
                cout << "Component " << match[1] << " not found in circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: GND is not Determined Yet!" << endl;
            }
            else if (status==1) {
                cout << "Node " << match[5] << " voltages based on DC Swipe of " << match[1] << " values:" << endl;
                for (int i = 0; i < results.size(); i++) {
                    cout << results[i][0] << ": " << results[i][1]  << endl;
                }
            }
        }
        else if (regex_search(entry, match, PrintDCSwipeVoltageOfElement)) {
            vector<vector<double>> results;
            int status = controller.printDCSwipeVoltageOfElement(match[1], match[2], match[3], match[4],match[5],results);
            if (status==0) {
                cout << "Element " << match[5] << " not found in the circuit!" << endl;
            }
            else if (status==-1) {
                cout << "Component " << match[1] << " not found in circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: GND is not Determined Yet!" << endl;
            }
            else if (status==1) {
                cout << "Element " << match[5] << " voltages based on DC Swipe of " << match[1] << " values:" << endl;
                for (int i = 0; i < results.size(); i++) {
                    cout << results[i][0] << ": " << results[i][1]  << endl;
                }
            }
        }
        else if (regex_search(entry, match, PrintDCSwipeCurrentOfElement)) {
            vector<vector<double>> results;
            int status = controller.printDCSwipeCurrentOfElement(match[1], match[2], match[3], match[4],match[5],results);
            if (status==0) {
                cout << "Element " << match[5] << " not found in the circuit!" << endl;
            }
            else if (status==-1) {
                cout << "Component " << match[1] << " not found in circuit!" << endl;
            }
            else if (status==-2) {
                cout << "Error: GND is not Determined Yet!" << endl;
            }
            else if (status==1) {
                cout << "Element " << match[5] << " current based on DC Swipe of " << match[1] << " values:" << endl;
                for (int i = 0; i < results.size(); i++) {
                    cout << results[i][0] << ": " << results[i][1]  << endl;
                }
            }
        }
        else if (regex_search(entry, match, SaveCurrentCircuit)) {
            int status = controller.saveCurrentCircuit(match[1]);
        }
        else if (regex_search(entry, match, ShowAllCircuits)) {
            vector <string> listFiles = controller.allCircuits();
            cout << "Enter Number of Circuit You Wanna Open or Enter -1 to return:" << endl;
            for (int i = 0; i < listFiles.size(); i++) {
                cout <<"Circuit " << i+1 << ":" << listFiles[i] << endl;
            }
            int fileNumber;
            cin >> fileNumber;
            if (fileNumber == -1) {
            }else {
                currentCircuit = listFiles[fileNumber-1];
                int status = controller.openNewSchemaic(listFiles[fileNumber-1]);
            }

        }
        else if (regex_search(entry, match, ShowNodeList)) {
            map<string,Node*> nodeList = controller.getNodes();
            if (nodeList.size() == 0) {
                cout << "No node is in the circuit!" << endl;
            }else {
                for (auto i : nodeList) {
                    cout<< "Node Number " << i.second->getNodeNumber() << ": " << i.first << endl;
                }
            }

        }
        else if (regex_search(entry, match, ShowElementList)) {
            map<string,Element*> elementList = controller.getElements();
            if (elementList.size() == 0) {
                cout << "No element is in the circuit!" << endl;
            }else {
                for (auto i : elementList) {
                    cout<< i.second->getType() +": " << i.first + " " << i.second->getValue() << endl;
                }
            }
        }
        else if (regex_search(entry, match, ShowBoothList)) {
            map<string,Element*> elementList = controller.getElements();
            if (elementList.size() == 0) {
                cout << "No element is in the circuit!" << endl;
            }else {
                for (auto i : elementList) {
                    cout<< i.second->getType() +": " << i.first + " " << i.second->getValue() <<  " " << i.second->getFirstNode()->getName() +" "+ i.second->getSecondtNode()->getName() << endl;
                }
            }
        }
        else if (regex_search(entry, match, CurrentSchematic)) {
            cout << currentCircuit << endl;
        }
        else if (regex_search(entry, match, SaveCurrentSchematicTOPath)) {
            int status = controller.saveCurrentCircuitTOPath(match[1]);

        }
        else if (regex_search(entry, match, SaveCurrentSchematic)) {
            int status = controller.saveCurrentCircuit(currentCircuit);
        }
        else if (regex_search(entry, match, CloseCurrentSchematic)) {
            controller.closeFile();
            cout << "Circuit " << currentCircuit << " Closed Succesfully! Now You Are In A Floating Schematic..."<< endl;
            currentCircuit = "No Schematic has been opened yet!";
        }
        else if (regex_search(entry, match, Open)) {
            int status = controller.openNewSchemaicFromAnyPath(match[1]);
            if (status == 1) {
                currentCircuit = match[1];
            }
        }
        else {
            cout << "Invalid Input Format!" << endl;
        }
    }
}

