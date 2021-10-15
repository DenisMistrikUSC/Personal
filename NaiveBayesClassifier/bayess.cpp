#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

//convtolower function
string convToLower(string src)
{
    transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}
//helper function that prints the final solution
void printSolution(vector<string> items, ostream& os){
    for(int i = 0; i < int(items.size()); i++){
        os << items[i] << endl;
    }
}
//classify algorithm that loops through the classify input and calculates all of the probability using bayes and laplacian smoothing
void classify(vector<set<string>> classData, map<string,int> occ, map<string,map<string,int>> occ2, map<string,int> traitOcc, int size, ostream& os){
    //vector that stores the most likely items
    vector<string> solutions;
    //main loop
    for(int i = 0; i < int(classData.size()); i++){
        double bestProb = 0;
        string bestItem;
        
        for(map<string,int>::iterator it1 = occ.begin(); it1 != occ.end(); ++it1){
            double totalPXC = 1;
            double totalPXnotC = 1;
            for(set<string>::iterator it = classData[i].begin(); it != classData[i].end(); ++it){  
                //the bayes theorem calculations including laplacian
                double pXC;
                double pXnotC;
                if(occ2.at(it1->first).find(*it) != occ2.at(it1->first).end()){
                    pXC = double(1 + occ2.at(it1->first).at(*it))/double(1 + it1->second);
                    pXnotC = double(1+ traitOcc.at(*it)- occ2.at(it1->first).at(*it))/double(1 + size - it1->second);
                }
                else{
                    pXC = double(1/double(1+it1->second));
                    double occXnotC = 0;
                    if(traitOcc.find(*it) != traitOcc.end()) occXnotC = traitOcc.at(*it);
                    pXnotC = (1+occXnotC)/double(1+size-it1->second);
                }
                totalPXC *= pXC;
                totalPXnotC *= pXnotC;
            }
            double pC = double(it1->second)/double(size);
            double pnotC = double(size - it1->second)/double(size);
            double prob = (totalPXC * pC)/(totalPXC * pC + totalPXnotC * pnotC);
            //method for determining the most likely item
            if(bestProb < prob){
                bestProb = prob;
                bestItem = it1->first;
            }
        }
        solutions.push_back(bestItem);
    }
    printSolution(solutions, os);
}

int main(int argc, char *argv[]){
    if (argc < 4) {
        cout << "please specify a training, classify and output file" << endl;
        return 0;
    }
    ifstream trainFile(argv[1]);
    ifstream classFile(argv[2]);
    ofstream ofile(argv[3]);
    vector<pair<string,set<string>>> trainData;
    vector<set<string>> classData;

    string line;
    string temp;
    int x;
    trainFile >> x;
    getline(trainFile,temp);
    map<string,int> occ;
    //for the number of occurences for a given trait and item
    map<string,map<string,int>> occ2;
    //the number of total occurences for a given trait 
    map<string,int> traitOcc;
    //for loop the extracts the data from the training file
    for(int i = 0; i < x; i++){
        getline(trainFile, line);
        stringstream ss(line);
        string item;
        set<string> s;
        ss >> item;
        item = convToLower(item);
        pair<string,set<string>> p = make_pair(item,s);
        trainData.push_back(p);
        string trait;
        while(ss >> trait){
            trait = convToLower(trait);
            trainData[i].second.insert(convToLower(trait));
        }     
    }
    //exctracts data from classify file
    classFile >> x;
    getline(classFile,temp);
    for(int i = 0; i < x; i++){
        getline(classFile, line);
        string trait;
        set<string> s;
        classData.push_back(s);
        stringstream ss(line);
        while(ss >> trait) classData[i].insert(convToLower(trait));
    }
    //fills up the occurence maps from the training data 
    for(int i = 0; i < int(trainData.size()); i++){
        string item = trainData[i].first;
        if(occ.find(item) != occ.end()) occ.at(item) += 1;
        else occ.insert({item,1});
        if(occ2.find(item) == occ2.end()){
            map<string,int> m;
            occ2.insert({item , m});
        } 
        for(set<string>::iterator it = trainData[i].second.begin(); it !=  trainData[i].second.end(); ++it){
            string trait = *it;
            if(occ2.at(item).find(trait) != occ2.at(item).end()) occ2.at(item).at(trait) += 1;
            else occ2.at(item).insert({trait,1}); 
            if(traitOcc.find(trait) != traitOcc.end()) traitOcc.at(trait) += 1;
            else traitOcc.insert({trait,1});
        }
    }
    classify(classData,occ,occ2, traitOcc,trainData.size(), ofile);
    trainFile.close();
    classFile.close();

    ofile.close();
    return 0;
}