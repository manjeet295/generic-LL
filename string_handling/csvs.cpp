#include<iostream>
using namespace std;
void tokenizer(char *arr){
    int i=0;
    int start=0;
    while(1){
        if(arr[i]==','||arr[i]=='\0'){
        cout<<"[";
        for(int j=start;j<i;j++){
            cout<<arr[j];
        }
        cout<<"]"<<endl;
        if(arr[i]=='\0') break;
        start=i+1;

    }
   
    i++;
}
}
int main(){
    char arr[100];
    cout<<"enter the string: ";
    cin>> arr;
    tokenizer(arr);
    return 0;
}
