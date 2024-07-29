#ifndef INC_3530PROJECT3_READ_H
#define INC_3530PROJECT3_READ_H
#endif //INC_3530PROJECT3_READ_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

struct Estate{
    string name;
    float rent;
    int bedrooms;
    int bathrooms;
    float location;

    Estate(){
        name = "ACME";
        rent = 0.00;
        bedrooms = 0;
        bathrooms = 0;
        location = 0.00;
    }
    Estate(string _name, float _rent, int _bedrooms, int _bathrooms, float _location){
        name = _name;
        rent = _rent;
        bedrooms = _bedrooms;
        bathrooms = _bathrooms;
        location = _location;
    }

    void print_test(){ //test function to see if read is implemented correctly
            cout << name << " " << rent << " " << bedrooms << " " << bathrooms << " " << location << endl;
    }

};

vector<Estate> read(){
    vector<Estate>HousingData;
    ifstream file("RandomHousingData.csv"); //this is the .csv file i'm using. each data part is separated by a semicolon.
    //the .csv file will also be added to the github.
    string singleLine;
    while (getline(file, singleLine)){
        string name1;
        string token;
        float rent1;
        int bed1;
        int bath1;
        float location1;
        istringstream stream(singleLine);
        getline(stream, name1, ';');
        getline(stream, token, ';');
        rent1 = stof(token);
        getline(stream, token, ';');
        bed1 = stoi(token);
        getline(stream, token, ';');
        bath1 = stoi(token);
        getline(stream, token, ';');
        location1 = stof(token);
        Estate data(name1, rent1, bed1, bath1, location1);
        HousingData.push_back(data);
    }
    return HousingData;
}

