#include<iostream>
#include "cusstring.h"
using namespace std;

int main(){
    int res;
     char arr1[100];
     char arr2[100];
     while(1){
        cout << "\n\n1. Length of a string";
        cout << "\n2. Copy a string into another";
        cout << "\n3. Concatenation of two strings";
        cout << "\n4. Comparison of two strings";
        cout << "\n5. find a character in string";
        cout << "\n6. Reverse the string";
        cout << "\n7. String is palindrome or not";
        cout << "\n8. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> res;
        switch (res) {
            case 1:{
                cout << "Enter the string: ";
                cin >> arr1;
                cout << "Length: " << strlength(arr1);
                break;
            }

            case 2:{
                cout << "Enter first string: ";
                cin >> arr1;
                cout << "Enter second string: ";
                cin >> arr2;
                strcopy(arr1, arr2);
                cout << "Copied string in arr1: " << arr1;
                break;
            }

            case 3: {

            
                cout << "Enter first string: ";
                cin >> arr1;
                cout << "Enter second string: ";
                cin >> arr2;
                strconcat(arr1, arr2);
                cout << "Concatenated string: " << arr1;
                break;
            }

            case 4:{
                cout << "Enter first string: ";
                cin >> arr1;
                cout << "Enter second string: ";
                cin >> arr2;
                int cmp = strcmp(arr1,arr2);
                if(cmp>0){
                    cout << arr1 << " is greater than " << arr2;
                }
                else if(cmp<0){
                    cout << arr2 << " is greater than " << arr1;
                }
                else{
                    cout << "Both are same";
                }
                break;
            }
            case 5:{
                char ch;
                cout << "Enter string: ";
                cin >> arr1;
                cout << "Enter character: ";
                cin >> ch;
                int result = strchr(arr1,ch);
                if(result==-1){
                    cout << "character not found in string.";
                }
                else{
                    cout << "Found at: " << result;
                }
                break;

            }
            case 6:{
                cout << "Enter string: ";
                cin >> arr1;
                my_strrev(arr1);
                cout << "After Reverse: " << arr1;
                break;
            }
            case 7:{
                cout << "Enter string: ";
                cin >> arr1;
                if(is_palindrome(arr1)){
                    cout << "String is palidrome.";
                }
                else{
                    cout << "Not palindrome.";
                }
                break;
            }

            case 8: {
                return 0;
            }
            default:{
                cout << "Invalid Choice!";
            }
        }
     }
}