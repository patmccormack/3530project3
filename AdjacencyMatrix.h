#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include "read.h"
#include <vector>
#include <iostream>
using namespace std;

// organize into a "map", highlight based off of relevancy.


class AdjacencyMatrix {
public:
    vector<vector<double>> matrix; 
    int numNodes;

    // Construct matrix with numNodes nodes
    AdjacencyMatrix(int numNodes) : numNodes(numNodes) {
        matrix.resize(numNodes, vector<double>(numNodes, 0.0));
    }


    // add edge btw from adn to nodes
    void addEdge(int from, int to, double weight) {
        matrix[from][to] = weight;
        matrix[to][from] = weight; 
    }

    //edge lookup: shortest edge between data points and user preferences
    string findShortestEdge(int userNodeIndex, const vector<Estate>& estates) const {
        double minEdgeWeight = numeric_limits<double>::max();
        int minEdgeIndex = -1;
            for (size_t i = 0; i < numNodes; ++i) {
                if (i != userNodeIndex && matrix[userNodeIndex][i] > 0.0) {
                    if (matrix[userNodeIndex][i] < minEdgeWeight) {
                        minEdgeWeight = matrix[userNodeIndex][i];
                        minEdgeIndex = i;

                    }
                }
            }
        if (minEdgeIndex != -1) {
            return estates[minEdgeIndex].name;
        } else {
            return "No match found";
        }
    }
    

    vector<string> getNeighbors(int node, const vector<Estate>& estates) const {
        vector<string> neighbors;
        for (int i = 0; i < numNodes; ++i) {
            if (matrix[node][i] > 0.0) {
                neighbors.push_back(estates[i].name);

            }
        }
        return neighbors;
    }


};

#endif
