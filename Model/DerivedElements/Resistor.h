//
// Created by Novin##### on 5/1/2025.
//

#ifndef RESISTOR_H
#define RESISTOR_H
#include <map>

#include "../Element.h"


class Resistor : public Element{
    private:
    string resistorName;
    double resistor;
    map<string, double> resistor_map;
    bool isSwitched;
    public:
    Resistor(Node* firstNode,Node* secondNode,double R,string rName);
    double getResistor();
    void setResistor(double);

    virtual double getValue() {
        double equivalentConductance = 0;
        for (auto it = resistor_map.begin(); it != resistor_map.end(); it++) {
            equivalentConductance += 1.0/it->second;
        }
        resistor = 1.0/equivalentConductance;
        return resistor;
    };
    virtual string getType() {
        return "Resistor";
    };
    virtual void addValue(double value,string rName) {
        resistor_map[rName] = value;
    };
    void changeMainValue(double value) {
        resistor = value;
        resistor_map[resistorName] = value;
    }
    virtual bool isSwitch() {
        return isSwitched;
    }
    void toggleSwitched() {
        isSwitched = !isSwitched;
    }
    ~Resistor(){};
};



#endif //RESISTOR_H
