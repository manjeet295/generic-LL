#include<iostream>
using namespace std;
int strlength(char *arr){
    int i = 0;
    while(arr[i]!='\0'){
        i++;
    }
    return i;
}
void strcopy(char *arr1 , char *arr2){
    int i = 0;
    while(arr2[i]!='\0'){
        arr1[i]=arr2[i];
        i++;
    }
    arr1[i]='\0';
}
void strconcat(char *arr1,char *arr2){
    int i = 0;
    while(arr1[i]!='\0'){
        i++;
    }
    arr1[i++] = ' ';
    int j = 0;
    while(arr2[j]!='\0'){
        arr1[i++]=arr2[j++];
    }
    arr1[i]='\0';
}
int strcmp(char *arr1,char *arr2){
    int i = 0,j = 0;
    while(arr1[i]!='\0'||arr2[j]!='\0'){
        if(arr1[i]!=arr2[j]){
            return arr1[i]-arr2[j];
        }
        if(arr1[i]!='\0') i++;
        if(arr2[j]!='\0') j++;
    }
    return 0;
}
int strchr(char *arr1,char ch){
    int i = 0;
    while(arr1[i]!='\0'){
        if(arr1[i]==ch){
            return i;
        }
        i++;
    }
    return -1;
}
void strrev(char *arr1){
    int n = strlength(arr1);
    for(int i = 0 ; i < n/2  ; i++){
        int temp = arr1[i];
        arr1[i] = arr1[n-i-1];
        arr1[n-i-1] = temp;
    }
}
int is_palindrome(char *arr1){
    char rev[100];
    strcopy(rev,arr1);
    strrev(rev);
    if(strcmp(rev,arr1)==0){
        return 1;
    }
    return 0;
}
