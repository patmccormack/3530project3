#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include "read.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
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
    std::string findShortestEdge(int userNodeIndex, const vector<Estate>& estates) const {
        double minEdgeWeight = numeric_limits<double>::max();
        int minEdgeIndex = -1;
        if (adjacencyList.find(userNodeIndex) != adjacencyList.end()) {
            for (const auto &edge: adjacencyList.at(userNodeIndex)) {
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

    vector<string> getNeighbors(int node, const vector<Estate> &estates) const {
        vector<string> neighbors;
        if (adjacencyList.find(node) != adjacencyList.end()) {
            for (const auto &edge: adjacencyList.at(node)) {
                neighbors.push_back(estates[edge.first].name);
            }
        }
        return neighbors;
    }

    /*std::vector<string> getEdges(int node) const {

        std::queue<int> q;
        std::set<int> edges;
        q.push(node);
        while(!q.empty()){
            std::vector<pair<int,double>> nodes = adjacencyList.find(q.front());
            q.pop();

            for(int i = 0; i < nodes.size(); i++){
                continue;
            }
        }
    }*/

    void printMap(){
        for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it){
            std::cout << it->first << ": ";
            for(int i = 0; i < it->second.size(); i++) {
                std::cout << "( " << it->second[i].first << "," << it->second[i].second << " )";
            }
            std::cout << std::endl;
        }

    }

    void clearMap(){
        adjacencyList.clear();
    }

#endif
};