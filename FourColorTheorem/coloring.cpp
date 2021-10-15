#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cstring>
void print(std::map<char,int>);
//checks whether a certain color would be valid for a given letter, goes through the set of neighbors to check if the colors conflict
bool isValid(std::map<char,int> countries, std::map<char,std::set<char>>::iterator it,int c){
    for(std::set<char>::iterator f = it->second.begin(); f != it->second.end(); ++f){
        if(countries.at(*f) == c){
            return false;    
        }
    }
    return true;
}

//the function that gets called recursively, its parameters are the countries map, the neighbor map, the iterator to the neighbor and an int s to check if its reached the end
bool backtrace(std::map<char,int> countries, std::map<char,std::set<char>> n ,std::map<char,std::set<char>>::iterator it,unsigned int s){
    //end case
    if(it == n.end() || s == countries.size()){
        print(countries);
        return true;
    }
    //main backtrace algorithm that calls isValid for each of the 4 possible colors
    for(int i = 1; i <= 4; i++){      
        if(isValid(countries,it,i)){  
            countries.at(it->first) = i;
            std::map<char,std::set<char>>::iterator temp = it;
            ++temp;
            if(backtrace(countries,n,temp, s + 1)){
                return true;
            }  
            countries.at(it->first) = 0;
        } 
    }
    return false;
}

//prints the countries map/solution
void print(std::map<char,int> countries){
    for(std::map<char,int>::iterator it = countries.begin(); it != countries.end(); ++it){
        std::cout<< it->first << " " << it->second << std::endl;
    }
}

int main(int argc,char* argv[]){
    int c;
    int y;
    int x;
    std::ifstream file;
    file.open(argv[1]);
    file >> c >> y >> x;
    //since ifstream is being weird i getline once before iterating through the map of letters to catch the empty line after using >>
    std::string temp;
    std::getline(file,temp);
    //dynamically allocate 2d char array to store the letters 
    char** arr = new char*[y];
    for(int i = 0; i < y; i++){
        arr[i] = new char[x];
    }
    //map that stores which color each letter has been assigned
    std::map<char,int> countries;
    //map that stores a given letters bordering letters
    std::map<char,std::set<char>> neighbors;
    for(int i = 0; i < c; i++){
        countries.insert({65+i,0});
        std::set<char> temp;
        neighbors.insert({65+i,temp});
    }
    //loop that goes through the file and fills the 2d array
    std::string line;
    int i = 0;
    while(std::getline(file,line)){
        for(int j = 0; j < x; j++){
            arr[i][j] = line.at(j);
        }
        i++;
    }
    //nested for loops that populate the neighbor map 
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            //checks vertical and horizontal neighbors
            for(int k = i-1; k <= i+1; k++){
                if(k < 0 || k >= y){
                    continue;
                }
                if(arr[k][j] != arr[i][j]){
                    (neighbors.at(arr[i][j])).insert(arr[k][j]);
                }
            }
            for(int k = j-1; k <= j+1; k++){
                if(k < 0 || k >= x){
                    continue;
                }
                if(arr[i][k] != arr[i][j]){
                    (neighbors.at(arr[i][j])).insert(arr[i][k]);
                }
            }
        }
    }
    //iterator used to step through the neighbor map
    std::map<char,std::set<char>>::iterator it = neighbors.begin();
    unsigned int s = 0;
    backtrace(countries,neighbors,it,s);
    file.close();
    //deallocate dynamically allocated array
    for(int i = 0; i < y; i++){
        delete [] arr[i];
    }
    delete [] arr;
    return 0;
}