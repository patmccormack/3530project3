#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include "read.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <limits>
using namespace std;

 // adj list - search function and a selection function, highlight based off of relevancy.

class AdjacencyList {
public:
    unordered_map<int, vector<pair<int, double>>> adjacencyList;


// add edges
    void addEdge(int from, int to, double weight) {
        adjacencyList[from].emplace_back(to, weight);
        adjacencyList[to].emplace_back(from, weight);
    }

// edge lookup: shortest edge between data points and user preferences
    string findShortestEdge(int userNodeIndex, const vector<Estate>& estates) const{
        double minEdgeWeight = numeric_limits<double>::max();
        int minEdgeIndex = -1;
        if (adjacencyList.find(userNodeIndex) != adjacencyList.end()) {
            for (const auto& edge : adjacencyList.at(userNodeIndex)) {
                if (edge.second < minEdgeWeight) {
                    minEdgeWeight = edge.second;
                    minEdgeIndex = edge.first;
                }
            }
        }
        if (minEdgeIndex != -1) {
            return estates[minEdgeIndex].name;
        } else {
        return "No match found";
    }
}
// get neighbors by name

  vector<string> getNeighbors(int node, const vector<Estate>& estates) const {
        vector<string> neighbors;
        if (adjacencyList.find(node) != adjacencyList.end()) {
            for (const auto& edge : adjacencyList.at(node)) {
                neighbors.push_back(estates[edge.first].name);
            }
        }
        return neighbors;
    }

#endif
};