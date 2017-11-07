#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include<algorithm>
#include<iterator>
#include<array>
using namespace std;
int main(){
    fstream file;
    string filename;
    cout<<"What file do you want to compile? (.cmm)"<<endl;
    cin>>filename;
    cout<<"Preprocessing code to c++"<<endl;
    file.open(filename+".cmm");
    string line;
    fstream fileexe;
    string create = "touch "+filename+".cpp";
    system(create.c_str());
    fileexe.open(filename+".cpp");
    fileexe<<"#include <iostream>"<<endl<<"using namespace std;"<<endl<<"int main(){"<<endl;
    float lines_count=std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    file.seekg(0, ios::beg);
    //WARNING! ANY LARGER THAN THE ACTUAL NUMBER OF ELEMENTS WILL BREAK THE CODE! UPDATE WITH THIS IN MIND!
    string reserved [14] {"int","string","say","float","bool","char","double","void","long","short","newline","if","}","ask"};
    float j=1;
    float progress = 0;
    while(getline(file,line)){
        int i=0;
        string name;
        size_t p = line.find_first_not_of(" ");
        line.erase(0, p);
        p = line.find_last_not_of(" ");
        if (string::npos != p){
            line.erase(p+1);
        }
        while(i<(sizeof((reserved))/sizeof((reserved[0])))){
            size_t found = line.find(reserved[i]);
            
            if (found==0){
                name = reserved [i];
            }
            i++;
        }
        stringstream split (line);
        string one;
        string two;
        string three;
        getline(split,one,' ');
        std::string line(std::istreambuf_iterator<char>(split), {});
        p = line.find_first_not_of(" {");
        line.erase(0, p);
        p = line.find_last_not_of(" {");
        if (string::npos != p){
            line.erase(p+1);
        }
        stringstream split2 (line);
        getline(split2,two,' ');
        if (name=="if"){
            fileexe<<"if ("<<two<<"){"<<endl;
        }
        if (name=="}"){
            fileexe<<"}"<<endl;
        }
        if (name=="ask"){
            fileexe<<"cin>>"<<two<<";"<<endl;
        }
        if (name=="int"|name=="string"|name=="float"|name=="bool"|name=="char"|name=="double"|name=="void"|name=="long"|name=="short"){ //im smart
            fileexe<<name<<" "<<two; //really smart
            //cout<<one<<":"<<two<<":"<<endl; //saved 72 lines of code
            getline(split2,three); //im proud of myself for thinking of that
            if (three!=""){
                fileexe<<" "<<three;
            }
            fileexe<<";"<<endl;
        }
        getline(split2,three,' ');
        if (name=="say"){
            fileexe<<"cout<<"<<two;
            if (three=="end"){
                fileexe<<"<<endl";
            }
            fileexe<<";"<<endl;
        }
        if (name=="newline"){
            fileexe<<"cout<<endl;";
        }
                progress = (j/lines_count);
                int barWidth = 70;
                
                cout << "[";
                int pos = barWidth * progress;
                for (int i = 0; i < barWidth; ++i) {
                    if (i < pos) cout << "=";
                    else if (i == pos) cout << ">";
                    else cout << " ";
                }
                cout << "] " << int(progress * 100.0) << " %\r";
                cout.flush();
        j++;
    }
    cout<<endl;
    fileexe<<"}"<<endl;
    cout<<"Preprocessed!"<<endl<<"Compiling c++ file"<<endl;
    string comp = "make "+filename;
    system(comp.c_str());
    cout<<"Compiled!"<<endl<<"Deleting c++ file"<<endl;
    string clean = "rm "+filename+".cpp";
    //system(clean.c_str());
    cout<<"Deleted!"<<endl<<"Making a nice terminal interface"<<endl;
    string term = "chmod +x "+filename;
    system(term.c_str());
    cout<<"Nice terminal interface created!"<<endl<<"Would you like to run your program? (Y or N)"<<endl;
    string yes;
    cin>>yes;
    if (yes=="y"|yes=="Y"){
        cout<<"Program output:"<<endl;
        string run = "./"+filename;
        system(run.c_str());
    }
}
