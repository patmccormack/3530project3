//
// Created by paddy on 7/28/2024.
//

#include <matplot/matplot.h>
#include <iostream>
#include "read.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include <cmath>
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <fstream>

double calculateSimilarity(const Estate& estate1, const Estate& estate2) {
    double score = 0.0;
    // normalize categories to give equal weightage in similarity score
    // Rent: estate - preferred/  average
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

Estate getUserTestPreferences() {
    return Estate("User Preferences", 1300, 3, 2, 5.0);
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Estate> TestData(int limit) {
    std::cout << "Loading File..." << endl;
    std::string filename = "RandomHousingData.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::vector<Estate> estates;
    std::string line;

    // Read and discard the header line
    std::getline(file, line);
    int index = 0;
    while (std::getline(file, line) && index <  limit) {
        std::vector<std::string> row = split(line, ';');
        if (row.size() >= 5) {
            double rent = std::stod(row[1]);
            int bedrooms = std::stoi(row[2]);
            int bathrooms = std::stoi(row[3]);
            double location = std::stod(row[4]);
            std::string realEstate = row[0];
            estates.emplace_back(Estate(realEstate,float(rent), bedrooms, bathrooms,float(location)));
        }
        index++;

    }

    file.close();
    std::cout << " File Loaded " << endl;
    return estates;
}


int main(){

    bool end = false;
    int size = 40;
    std::vector<Estate> HousingData = TestData(size);
    AdjacencyList HouseList;
    AdjacencyMatrix HouseMatrix(size);

    double threshold = 0.8;
    int results_found = 0;
    //Forms connections around the housing data
    for (size_t i = 0; i < HousingData.size(); ++i) { // O(n^2) (n is number of datapoints)
        for (size_t j = i + 1; j < HousingData.size(); ++j) {
            double similarityScore = calculateSimilarity(HousingData[i], HousingData[j]);
            if (similarityScore > threshold) {
                HouseList.addEdge(i, j, similarityScore);
                HouseMatrix.addEdge(i, j, similarityScore);
                results_found++;
            }
        }
    }
    std::cout << "Found " << results_found << " from " << HousingData.size() << std::endl;
    while(!end){
        std::string input;
        std::cout << "Menu \n 0. Exit \n 1. Display Houses in Text \n 2. Display Houses in Graph \n 3. Search House \n 4. Print Reference" << std::endl;
        std::cin >> input;

        if(input == "1"){
            std::cout << " 1. Adjacency Map \n 2. Matrix?" << endl;
            string option;
            std::cin >> option;
            if(option == "1"){
                HouseList.printMap();
            }
            else if(option == "2"){
                HouseMatrix.printMatrix();
            }
        }
        if(input == "2"){
            std::cout << " 1. Adjacency Map \n 2. Matrix?" << endl;
            string option;
            std::cin >> option;
            std::vector<std::pair<size_t, size_t>> graph;
            std::vector<double> weights;

            if(option == "1"){
                unordered_map<int, vector<pair<int, double>>> list = HouseList.adjacencyList;

                for(auto it = list.begin();it != list.end() ;++it){//
                    vector<pair<int,double>> edges = it->second;
                    for(int i = 0; i < edges.size(); i++){
                        graph.push_back({it->first,edges[i].first});
                        weights.push_back(edges[i].second);
                        std::cout << it->first << "," << edges[i].first << endl;
                    }
                }
                std::cout << "Done" << std::endl;
                auto f = matplot::figure(false);

                auto g = matplot::graph(graph);
                double m_weight = matplot::max(weights);

                std::vector<double> line_widths =  matplot::transform(weights, [&](double w) { return 5. * w / m_weight; });
                g->line_widths(line_widths);

                matplot::show();
            }
            if(option == "2"){
                std::vector<double> x;
                std::vector<double> y;
                std::vector<double> c;

                std::vector<vector<double>> m = HouseMatrix.matrix;
                std::unordered_map<std::string, pair<int,int>> labels;
                for(int i = 0; i < m.size(); ++i) { // O(n^2) (n is number of data points)
                    for(int j = 0; j < m[i].size() ; ++j){
                        x.push_back(i);
                        y.push_back(j);
                        c.push_back(m[i][j]);

                        std::cout << "( " << i << ", " << j << " ): " << m[i][j] << std::endl;
                    }
                }
                auto f = matplot::figure(false);


                /*for(auto it = labels.begin(); it != labels.end(); ++it){
                    matplot::labels()
                }*/
                auto l = matplot::scatter(x,y,6,c);
                l->marker_face(true);
                matplot::show();
            }
        }
        if(input == "3"){
            HouseList.clearMap();
            HouseMatrix.clearMatrix();

            Estate userEstate("User Preferences", 0.0, 0, 0, 0.0);
            cout << "Enter your preferred rent price: ";
            cin >> userEstate.rent;
            cout << "Enter your preferred number of bedrooms: ";
            cin >> userEstate.bedrooms;
            cout << "Enter your preferred number of bathrooms: ";
            cin >> userEstate.bathrooms;
            cout << "Enter your preferred distance from campus (numerical representation): ";
            cin >> userEstate.location;

            for(size_t i = 0; i < HousingData.size(); ++i) {
                double userSimilarityScore = calculateSimilarity(HousingData[i], userEstate);
                if (userSimilarityScore > threshold) {
                    HouseList.addEdge(0, i, userSimilarityScore);
                    std::cout << std::to_string(i) + ": " + HousingData[i].name + " \nBedrooms: " +
                                 std::to_string(HousingData[i].bedrooms) + " \nBathrooms: " +
                                 std::to_string(HousingData[i].bathrooms) + " \n Distance from campus: " +
                                 std::to_string(HousingData[i].location) + " \nRent: " +
                                 std::to_string(HousingData[i].rent) + " \n \n";
                }
            }
        }
        if(input == "4"){
            std::cout << "Printing Data to File" << std::endl;
            std::ofstream data("Houses.txt");
            if (data.is_open())
            {
                std::cout << "File opened" << std::endl;
                for(int i = 0; i < HousingData.size(); i++){
                    std::string estate = std::to_string(i) + ": " + HousingData[i].name + " \nBedrooms: " +
                                         std::to_string(HousingData[i].bedrooms) + " \nBathrooms: " +
                                         std::to_string(HousingData[i].bathrooms) + " \n Distance from campus: " +
                                         std::to_string(HousingData[i].location) + " \nRent: " +
                                         std::to_string(HousingData[i].rent) + " \n";

                    data << estate;
                    std::cout << estate << std::endl;

                }
                data.flush();
                data.close();
            }
            using namespace matplot;

        }
        if(input == "0"){
            end = true;
        }
    }



    return 0;
}

/*
 * adj list - search function and a selection function, highlight based off of relevancy.
 * adj matrix - organize into a "map", highlight based off of relevancy.
 */
