//
//  main.cpp
//  CS300HW2_v3
//
//  Created by caghank on 18.11.2018.
//  Copyright © 2018 caghank. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "BinarySearchTree.hpp"
#include <string>

using namespace std;


int main() {

    
    ifstream file; //stream object for reading
    string filename="compin.txt";
    file.open(filename);
    if(!file.is_open())
        cout<<"Error while reading"<<endl;
    string line;
    
    
    const string ITEM_NOT_FOUND = "-9999";
    BinarySearchTree<string> Dictionary( ITEM_NOT_FOUND );

    string s="";
    char ch;
    int counter=256;
    
    std::ofstream ofs ("compout.txt", std::ofstream::out);
    
    

    while (!file.eof()) {
        getline(file,line) ;
        for(int k=0;k<line.length();k++)
        {
            ch=line[k]; // ch == CURRENT
            if(Dictionary.find(s+ch)!=ITEM_NOT_FOUND)
            {
                
                s=s+ch;
            }
            else
            {
                if(counter<=4096)
                {
                    if((s+ch).length() > 2) // adding like something like aab aac
                    {
                        //encode s to output file
                        Dictionary.insert((s+ch),counter) ;
                        ofs<<Dictionary.findPosition(s)<<" " ;
                        //cout<<Dictionary.findPosition(s)<<" " ;
                        //cout<<s+ch <<" is added to dictionary"<<endl;
                        counter++;
                        //add s+ch to dictionary
                    }
                    else if((s+ch).length() == 2)  // adding something like aa bb ab ca
                    {
                        ofs<< int(s[0]) <<" ";
                        Dictionary.insert((s+ch),counter) ;
                        //cout<< int(s[0]) <<" ";
                        //cout<<s+ch <<" is added to dictionary"<<endl;
                        counter++;
                        
                    }
                }
                else
                {
                    if(Dictionary.find(s+ch)==ITEM_NOT_FOUND)
                    {
                        if(Dictionary.find(s)!=ITEM_NOT_FOUND)
                        {
                            ofs<<Dictionary.findPosition(s)<<" ";
                            //cout<<Dictionary.findPosition(s)<<" ";
                        }
                    }
                }
                    s=ch;
            }
            
        }
        //encode s to output file hmm okey ;
        if(Dictionary.findPosition(s)==-9999)
        {
            ofs<<int(s[0]);
            //cout<<int(s[0]);
        }
        else
        {
            ofs<<Dictionary.findPosition(s)<<" " ;
            //cout<<Dictionary.findPosition(s)<<" " ;
        }
    }
    
    
    ofs.close();
    return 0;
}

