#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ofstream wr("output.txt",ios::out|ios::trunc);

    if(!wr.is_open()){
        cout << "wr not opened";
        return 1;
    }

        wr<<"this is output txt";

        wr.close();
        ifstream in("output.txt");
        if(!in.is_open()){
            cout << "file not opened for read";
        }
        char arr[100];
        int c = 0;
        while(in >> arr){
            c++;
            cout << c << " ";
            
        }

        in.close();

        return 0;

}               