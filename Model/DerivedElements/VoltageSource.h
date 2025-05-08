//
// Created by Novin##### on 5/1/2025.
//

#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include "../Element.h"

class VoltageSource : public Element {
      private:
      double voltage;
      public:
      VoltageSource(Node* firstNode,Node* secondNode,double voltage);
      double getVoltage();
      void setVoltage(double voltage);
      virtual string getType() {
            return "VoltageSource";
      };
      virtual double getValue() {
            return voltage;
      };
      ~VoltageSource(){};
};



#endif //VOLTAGESOURCE_H
