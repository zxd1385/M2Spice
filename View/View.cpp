//
// Created by Novin##### on 5/1/2025.
//

#include "View.h"
#include <regex>
void View::run() {
    //regexes...
    regex AddResistor(R"(\s*add\s{1}Resistor\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddCapacitor(R"(\s*add\s{1}Capacitor\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddInductor(R"(\s*add\s{1}Inductor\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddDiode(R"(\s*add\s{1}Diode\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddGND(R"(\s*add\s{1}GND\s{1}(\S+)\s*)");
    regex AddVoltageSource(R"(\s*add\s{1}VoltageSource\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex AddCurrentSource(R"(\s*add\s{1}CurrentSource\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s{1}(\S+)\s*)");
    regex DeletResisror(R"(\s*add\s{1}(\S+)\s*)");





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
    }
}

