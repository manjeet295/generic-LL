#ifndef HashMap_H
#define HashMap_H
#include<iostream>


using namespace std;
template<typename T,typename T1>

class Node{
public:
    T key;
    T1 value;
    Node<T,T1>* next;
        
    Node(){
        next = NULL;
    }
    Node(T key, T1 value){
        this->key=key;
        this->value=value;
        next = NULL;
    }
};
template<typename T,typename T1>
class Hash{

    int size;
    Node<T,T1>** arr;
    int count;
        public:
    Hash(int s){
        size = s;
        count = 0;
        arr = new Node<T,T1>*[size];
        
    }
    int hashValue(int key){
    return key % size;
    }

    int hashValue(char key){
    return key % size;
    }

    int hashValue(string key){
    int sum = 0;
    for(char ch : key){
        sum += ch;
    }
    return sum % size;
    }

    void insert(T key, T1 value){
        int index = hashValue(key);
        Node<T,T1>* newNode = arr[index];
        if(newNode==NULL){
            arr[index] = new Node<T,T1>(key,value);
            count++;
        if((float)count/size>0.75){
            resize();
        }
            return;
        }
        
        while(newNode->next != NULL){
            if(newNode->key==key){
                newNode->value = value;
                return;
            }
            newNode = newNode->next;
        }
        Node<T,T1>* temp = new Node<T,T1>(key,value);
        newNode->next = temp;
        // count++;
        // if((float)count/size>0.75){
        //     resize();
        // }

    }
    void resize(){
        int s = size;
        size *= 2;
        Node<T,T1>** sarr = arr;
        arr = new Node<T,T1>*[size];
        for(int i = 0; i < size; i++){
        arr[i] = NULL;
    }
        int oldc = count;
        count=0;
        for(int i = 0 ; i < s ; i++){
            Node<T,T1>* temp = sarr[i];
            while(temp!=NULL){
                insert(temp->key,temp->value);
                temp=temp->next;
            }

        }
        count = oldc;
        printf("resized\n");
    }
    void remove(T key){
        int index = hashValue(key);
        Node<T,T1>* current = arr[index];
        Node<T,T1>* prev = NULL;
        while(current != NULL){
            if(current->key==key){
                if(prev!=NULL){
                    prev->next = current->next;

                }
                else{
                    arr[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }

    }
    T1 get(T key){
        int index = hashValue(key);
        Node<T,T1>* newNode = arr[index];
        while(newNode!=NULL){
            if(newNode->key == key){
                return newNode->value;
            }
            newNode = newNode->next;
        }
        return T1();
    }

};


#endif