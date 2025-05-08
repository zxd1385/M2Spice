//
// Created by Novin##### on 5/1/2025.
//

#ifndef RESISTOR_H
#define RESISTOR_H
#include "../Element.h"


class Resistor : public Element{
    private:
    double resistor;
    public:
    Resistor(Node* firstNode,Node* secondNode,double R);
    double getResistor();
    void setResistor(double);
    virtual double getValue() {
        return resistor;
    };
    virtual string getType() {
        return "Resistor";
    };
    ~Resistor(){};
};



#endif //RESISTOR_H
