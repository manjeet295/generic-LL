#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// #include <filesystem>
int main()
{

    ofstream out("input.txt",ios::out | ios::trunc);
    out<<"this is input.txt file";

    out.close();
     ifstream in("input.txt");



     if(!in.is_open())
     {
        cerr << "Failed to open file";
        return 1;
     }
     else{
      cout<<"Open successfully " << endl;
        
        char word[100];
        int count=0;
        while(in >> word){
            count++;
        }
        cout<<"Word in this file is:"<< count;
        in.close();
    }
}