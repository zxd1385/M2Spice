//
// Created by Novin##### on 5/1/2025.
//

#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include <vector>

#include "../Element.h"

class VoltageSource : public Element {
      private:
      double voltage;
      string vName;
      vector<double> currents;
      public:
      VoltageSource(Node* firstNode,Node* secondNode,double voltage,string vName);
      double getVoltage();
      void setVoltage(double voltage);
      virtual string getType() {
            return "VoltageSource";
      };
      virtual double getValue() {
            return voltage;
      };
      virtual void updateValue(double value) {
            currents.push_back(value);
      };
      ~VoltageSource(){};
};



#endif //VOLTAGESOURCE_H
