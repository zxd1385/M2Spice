//
// Created by Novin##### on 5/1/2025.
//

#ifndef CURRENTSOURCE_H
#define CURRENTSOURCE_H
#include "../Element.h"


class CurrentSource : public Element {
  private:
    double current;
    public:
      CurrentSource(Node* firstNode,Node* secondNode,double current);
      double getCurrent();
      void setCurrent(double current);
    virtual string getType() {
        return "CurrentSource";
    };
    virtual double getValue() {
        return current;
    };

};



#endif //CURRENTSOURCE_H
