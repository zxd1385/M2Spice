//
// Created by Novin##### on 5/1/2025.
//

#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include <cmath>
#include <vector>

#include "../Element.h"

class VoltageSource : public Element {
      private:
      double voltage;
      string vName;
      vector<double> currents;
      string dependency;
      double Gain;
      Node* firstNodeDependent;
      Node* secondNodeDependent;
      VoltageSource* voltageSourceDependent;
      //SIN wave...
      double frequency;
      double Amplitude;
      double offset;
      //PULSE wave...
      double initialVoltage;
      double voltageON;
      double timeDelay;
      double timeRise;
      double timeFall;
      int cycle;

      //current time and cycle...
      int cycleNow;
      double time;
      public:
      VoltageSource(){};
      VoltageSource(Node* firstNode,Node* secondNode,double voltage,string vName);
      VoltageSource(Node* firstNode,Node* secondNode,double g,Node* firstNodeDepent,Node* secondNodeDependent,string vName);
      VoltageSource(Node* firstNode,Node* secondNode,double g,VoltageSource* voltageSourceDependent,string vName);
      VoltageSource(Node* firstNode,Node* secondNode,double amplitude,double offset,double frequency,string vName);
      VoltageSource(Node* firstNode,Node* secondNode,double initialVoltage,double voltageON,double timeDelay,double timeRise,double timeFall,int cycle,string vName);
      double getVoltage();
      double getFrequency() {
            return frequency;
      };
      double getAmplitude() {
            return Amplitude;
      }
      double getOffset() {
            return offset;
      }
      double getInitialVoltage() {
            return initialVoltage;
      }
      double getVoltageON() {
            return voltageON;
      }
      double getTimeDelay() {
            return timeDelay;
      }
      double getTimeRise() {
            return timeRise;
      }
      double getTimeFall() {
            return timeFall;
      }
      double getCycle() {
            return cycle;
      }
      void setVoltage(double voltage);
      virtual string getType() {
            return "VoltageSource";
      };
      virtual double getValue() {
            return voltage;
      };
      virtual void updateValue(double value) {
            currents.push_back(value);
            if (dependency == "SIN") {
                  this->voltage = offset + Amplitude*sin(2*M_PI*frequency*((time+Element::timeSteps)*M_PI/180.0));
                  time += Element::timeSteps;
            }
            if (dependency == "PULSE") {
                  if (time - cycleNow*(timeDelay+timeRise+timeFall) >= 0 && time - cycleNow*(timeDelay+timeRise+timeFall) <= timeRise) {
                        this->voltage += Element::timeSteps*(voltageON - initialVoltage)/timeRise;
                        time += Element::timeSteps;
                  }
                  else if (time - cycleNow*(timeDelay+timeRise+timeFall) >= timeRise && time - cycleNow*(timeDelay+timeRise+timeFall) <= timeRise + timeDelay) {
                        time += Element::timeSteps;
                  }
                  else if (time - cycleNow*(timeDelay+timeRise+timeFall) >= timeRise + timeDelay && time - cycleNow*(timeDelay+timeRise+timeFall) <= timeRise + timeDelay + timeFall) {
                        this->voltage += Element::timeSteps*(initialVoltage - voltageON)/timeFall;
                        time += Element::timeSteps;
                  }
                  else if (cycleNow < cycle - 1) {
                        this->voltage += Element::timeSteps*(voltageON - initialVoltage)/timeRise;
                        time += Element::timeSteps;
                        cycleNow++;
                  }
                  else {
                        time += Element::timeSteps;
                  }

            }
      };
      void DCswipeValue(double value) override {
             voltage = value;
      };
      string getValueToSerialize() override;
      string getDependency();
      string getName() {
            return vName;
      };
      double getGain();
      Node* getFirstNodeDependent();
      Node* getSecondNodeDependent();
      VoltageSource* getVoltageSourceDependent();
      vector<double> getTRANCurrent() override {
            return currents;
      }
      void ClearElement() override {
            this->currents.clear();
      }
      ~VoltageSource(){};
};



#endif //VOLTAGESOURCE_H
