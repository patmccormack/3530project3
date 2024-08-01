//
// Created by paddy on 7/28/2024.
//
#include <iostream>
#include "read.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include <cmath>
using namespace std;

// similarity between nodes
double calculateSimilarity(const Estate& estate1, const Estate& estate2) {
    double score = 0.0;
    // normalize categories to give equal weightage in similarity score
    
    // Rent: estate - preferred/  preferrred
    double rentDifference = abs(estate1.rent - estate2.rent) / ((estate1.rent + estate2.rent) / 2.0);;
    score += 1.0 - rentDifference;
    // bedrooms
    double bedroomDifference = abs(estate1.bedrooms - estate2.bedrooms) / ((estate1.bedrooms + estate2.bedrooms) / 2.0);
    score += 1.0 - bedroomDifference;
    // bathroom
    double bathroomDifference = abs(estate1.bathrooms - estate2.bathrooms) / ((estate1.bathrooms + estate2.bathrooms) / 2.0);
    score += 1.0 - bathroomDifference;
    // location
    double locationDifference = abs(estate1.location - estate2.location) / ((estate1.location + estate2.location) / 2.0);
    score += 1.0 - locationDifference;
    // similarity score, count create count instead of 4 for more preferences
    return score/4;
    // most similar has score closer to 1
}

// Test
vector<Estate> TestData() {
    return {
        Estate("Estate A", 1200, 3, 2, 5.0),
        Estate("Estate B", 1300, 2, 1, 4.0),
        Estate("Estate C", 1500, 4, 3, 10.0),
        Estate("Estate D", 1100, 3, 2, 2.0),
        Estate("Estate E", 1250, 3, 1, 6.0)
    };
}

Estate getUserTestPreferences() {
    return Estate("User Preferences", 1300, 3, 2, 5.0);
}



int main(){
/*
    // read data 
    vector<Estate>HousingData = read();
    size_t n = HousingData.size(); // Number of apartments (will be user input node index)

    // get user preferences as an estate
    Estate userEstate("User Preferences", 0.0, 0, 0, 0.0);
    cout << "Enter your maximum preferred rent price: ";
    cin >> userEstate.rent;
    cout << "Enter your preferred number of bedrooms: ";
    cin >> userEstate.bedrooms;
    cout << "Enter your preferred number of bathrooms: ";
    cin >> userEstate.bathrooms;
    cout << "Enter your preferred distance from campus (numerical representation): ";
    cin >> userEstate.location;

    */

    // Test with test data
    vector<Estate> HousingData = TestData();
    Estate userEstate = getUserTestPreferences();
    size_t n = HousingData.size();

    // set threshhold to limit edges to meaningful similarities
    double threshold = 0.7;

    // make empty adj lsit and matrix
    AdjacencyList list;
    // size of data + user input (0 to n where n is user input)
    AdjacencyMatrix matrix(n+ 1);

    const size_t userNodeIndex = n;

    // edges to user node
    for (size_t i = 0; i < n; ++i) {
        double userSimilarityScore = calculateSimilarity(HousingData[i], userEstate);
        if (userSimilarityScore > threshold) {
            list.addEdge(userNodeIndex, i, userSimilarityScore);
            matrix.addEdge(userNodeIndex, i, userSimilarityScore);
        }
    }

    // egdges between data nodes
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            double similarityScore = calculateSimilarity(HousingData[i], HousingData[j]);
            if (similarityScore > threshold) {
                list.addEdge(i, j, similarityScore);
                matrix.addEdge(i, j, similarityScore);
            }
        }
    }

// compare edge lookup: lookup shortest edge between user node
    string shortestEdgeList = list.findShortestEdge(userNodeIndex, HousingData);
    string shortestEdgeMatrix = matrix.findShortestEdge(userNodeIndex, HousingData);
    cout << "Best match to user input (Adjacency List): " << shortestEdgeList << endl;
    cout << "Best match to user input (Adjacency Matrix): " << shortestEdgeMatrix << endl;

// compare neighborhood queiries: find all neighbors of user input (above similarity threshhold)
    vector<string> neighborsList = list.getNeighbors(userNodeIndex, HousingData);
    vector<string> neighborsMatrix = matrix.getNeighbors(userNodeIndex, HousingData);
    cout << "Potential suggestions based on user input (Adjacency List): ";
    for (string neighbor : neighborsList) {
        cout << neighbor << " ";
    }
    cout << endl;

    cout << "Potential suggestions based on user input (Adjacency Matrix): ";
    for (string neighbor : neighborsMatrix) {
        cout << neighbor << " ";
    }
    cout << endl;


}

/*
 * adj list - search function and a selection function, highlight based off of relevancy.
 * adj matrix - organize into a "map", highlight based off of relevancy.
 */