//
//  main.cpp
//  CS300_HW2decompound
//
//  Created by caghank on 19.11.2018.
//  Copyright © 2018 caghank. All rights reserved.
//

#include <iostream>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;


int main(int argc, const char * argv[]) {
    
    string MainDict[4096] ;
    for(int j=0 ; j < 256 ; j++)
    {
        char temp= j;
        MainDict[j].push_back(temp);
    }
    
    ifstream file; //stream object for reading
    string filename="compout.txt";
    file.open(filename);
    if(!file.is_open())
        cout<<"Error while reading"<<endl;
    
    string line;
    string readword;
    
    string entry;
    //char ch;
    int prevcode, currcode;
    int counter=256;
    ofstream ofs ("decompout.txt", std::ofstream::out);
    string old;
    
    bool ForFirstInput=true;
    
    
    while (!file.eof())
    {
        getline(file,line); //reads  as a line
        istringstream iss(line); //parse the line
        if (ForFirstInput == true) {
            iss>> old;
            ofs<< MainDict[stoi(old)]<<" ";
            ForFirstInput = false;
            prevcode = stoi(old);
        }
        while (iss>>readword) {
            currcode = stoi(readword);
            if(MainDict[stoi(readword)] != "") // IF Currcode in the dictionary
            {
                ofs << MainDict[stoi(readword)]<<" ";
                //Add to dictionary
                MainDict[counter] = MainDict[prevcode] + MainDict[currcode][0];
                counter = counter + 1;

            }
            else
            {
                MainDict[counter] = MainDict[prevcode] + MainDict[prevcode][0] ;
                ofs<<MainDict[prevcode] + MainDict[prevcode][0]<<" ";
                counter=counter+1;
                
            }
            prevcode=currcode;
        }
        
    }
   
    return 0;
}
