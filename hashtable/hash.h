#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include "linkedl.h" 
using namespace std;

template<typename T,typename T1>
class HashMap{
private:
    int size;
    int count;
    LinkedList<T,T1>* arr;

public:
    HashMap(int s){
        size = s;
        count = 0;
        arr = new LinkedList<T,T1>[size];
    }

    int hashValue(int key){
        return key % size;
    }

    int hashValue(char key){
        return key % size;
    }

    int hashValue(const char* key){
        int sum = 0;
        for(int i=0;key[i]!='\0';i++){
        sum+=key[i];
    }
        return sum % size;
    }

    void insert(T key,T1 value){
        int index = hashValue(key);
        Node<T, T1>* temp=arr[index].getHead();
        while(temp != NULL){
            if(temp->key==key){
                temp->value = value;
                return;
            }
            temp = temp->next;
        }
        arr[index].insertAtFirst(key,value);
        count++;
        if((float)count / size > 0.75){
            resize();
        }
    }

    void resize(){
        int oldSize = size;
        size *= 2;
        LinkedList<T, T1>* oldarr = arr;
        arr = new LinkedList<T, T1>[size];
        count = 0;
        for(int i = 0; i < oldSize;i++){
            Node<T, T1>* head = oldarr[i].getHead();
            while(head!=NULL){
                insert(head->key,head->value);
                head = head->next;
            }
        }

        delete[] oldarr;
        cout << "Resized to size " << size << endl;
    }

    void remove(T key){
        int index = hashValue(key);
        Node<T,T1>* temp = arr[index].getHead();
        Node<T,T1>* prev = NULL;

        while(temp != NULL){
            if(temp->key == key){
                if(prev == NULL){
                    arr[index].deleteAtFirst();
                }
                else{
                    Node<T,T1>* del = prev->next;
                    prev->next = temp->next;
                    delete del;
                }
                count--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    T1 get(T key){
        int index = hashValue(key);
        Node<T,T1>* temp = arr[index].getHead();
        while(temp != NULL){
            if(temp->key == key){
                return temp->value;
            }
            temp = temp->next;
        }
        return T1();
    }

    bool containsKey(T key){
        int index = hashValue(key);
        Node<T,T1>* temp = arr[index].getHead();
        while(temp != NULL){
            if(temp->key == key) return true;
            temp = temp->next;
        }
        return false;
    }

    void display() {
        for(int i = 0; i < size; ++i){
            cout << "Bucket " << i << ": ";
            arr[i].display();
        }
    }

    ~HashMap() {
    delete[] arr;
}

};

#endif
