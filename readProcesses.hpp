#include <fstream> 
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

using namespace std; 

vector<Process> readProcesses(){
    cout << "reading" << endl;
    vector<Process> processes;
    vector<vector<string> > allLines; 
    string currentLine;
    fstream inputFile; 
    inputFile.open("input.txt");

    while(getline(inputFile, currentLine)){
        vector<string> lineProcess; 
        string temp = "";
        for (char x: currentLine){
            if(x == ' '){
                lineProcess.push_back(temp);
                temp = "";
            }else{
                temp += x;
            }
        };
        lineProcess.push_back(temp);
        allLines.push_back(lineProcess);
    }

    for(vector<string> p: allLines){
        Process temp(stoi(p[0]), stoi(p[1]), stoi(p[2]), stoi(p[3]));
        processes.push_back(temp); 
    };
    cout << "read" << endl;
    return processes;
}