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
    vector<double> infoMatrix;
  int DIM ;
  int G ;
  int V ;
    public:
      Graph(vector<Element*> elements, vector<Node*> nodes);
      ~Graph();
      vector<vector<double>> buildMatrix();
    vector<double> buildInfoMatrix();


};



#endif //GRAPH_H
