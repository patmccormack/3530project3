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

    //edge lookup: longest edge between data points and user preferences
//    std::vector<std::string> findLongestEdge(int userNodeIndex, const vector<Estate>& estates) const {
//        double maxEdgeWeight = -1.0;
//        std::vector<int> maxEdgeIndices;
//            for (size_t i = 0; i < numNodes; ++i) {
//                if (i != userNodeIndex && matrix[userNodeIndex][i] > 0.0) {
//                    if (matrix[userNodeIndex][i] > maxEdgeWeight) {
//                        maxEdgeWeight = matrix[userNodeIndex][i];
//                        maxEdgeIndices.clear();
//                        maxEdgeIndices.push_back(i);
//                        } else if (matrix[userNodeIndex][i] == maxEdgeWeight) {
//                            maxEdgeIndices.push_back(i);
//                        }
//
//                }
//            }
//        std::vector<std::string> results;
//        if (!maxEdgeIndices.empty()) {
//            for (int index : maxEdgeIndices) {
//            results.push_back(estates[index].name);
//            }
//        } else {
//            results.push_back("No match found");
//        }
//        return results;
//}

//    std::vector<string> getNeighbors(int node, const vector<Estate>& estates) const {
//        std::vector<string> neighbors;
//        for (int i = 0; i < numNodes; ++i) {
//            if (matrix[node][i] > 0.0) {
//                neighbors.push_back(estates[i].name);
//
//            }
//        }
//        return neighbors;
//    }

    void printMatrix(){
        for(int i = 0; i < numNodes; ++i) {
            for(int j = 0; j < numNodes; ++j){
                std::cout << "( " << i << ", " << j << " ): " << matrix[i][j] << std::endl;
            }
        }
    }
    void clearMatrix(){
        matrix.clear();
    }
};

#endif
