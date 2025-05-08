//
// Created by Novin##### on 5/1/2025.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Element.h"
#include "Node.h"


class Graph {
  private:
    vector<Element*> elements;
    vector<Node*> nodes;
    vector<vector<double>> matrix;
    public:
      Graph(vector<Element*> elements, vector<Node*> nodes);
      ~Graph();
      int buildMatrix();


};



#endif //GRAPH_H
