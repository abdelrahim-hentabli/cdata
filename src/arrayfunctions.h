#ifndef ARRAYFUNCTIONS_H
#define ARRAYFUNCTIONS_H

#include <iostream>

template <class T>
int greaterThanOrEqual(T theList[], T whereIGo, int size);

template <class T>
void insertItem(T theList[], T insertMe, int where, int& size);

template <class T>
void insert_sorted(T theList[], T insertMe, int& size);

template <class T>
void split(T theList[], int& size, T newList[], int& newSize);

template <class T>
void remove(T theList[], int& size, int where);

template <class T>
void mergeLeft(T left[], int& size, T right[], int size2);

template <class T>
void mergeRight(T left[], int size, T right[], int& size2);


template <class T>
int greaterThanOrEqual(T theList[], T whereIGo, int size){
    int i = 0;
    while(i < size && whereIGo > theList[i]){
        i++;
    }
    return i;
}

template <class T>
void insertItem(T theList[], T insertMe, int where, int& size){
    int walker = size-1;
    while( walker >= where){
        theList[walker + 1] = theList[walker];
        walker--;
    }
    walker++;
    theList[walker] = insertMe;
    size++;
}

template <class T>
void insertSorted(T theList[], T insertMe, int& size){
    int whereIGo = greaterThanOrEqual(theList,insertMe,size);
    insertItem(theList, insertMe, whereIGo, size);
}

template <class T>
void split(T theList[], int& size, T newList[], int& newSize){
    if(size == 0){
        newSize = 0;
        return;
    }
    int temp = size;
    size = (size + 1 )/2;
    newSize = 0;
    for(int i = size; i < temp; i++){
        newList[newSize] = theList[i];
        newSize++;
        theList[i] = T();
    }
}

template <class T>
void remove(T theList[], int& size, int where){
    int walker = where;
    while(walker < size-1){
        theList[walker] = theList[walker + 1];
        walker++;
    }
    size--;
}

template <class T>
void mergeLeft(T left[], int& size, T right[], int size2){
    for(int i = 0; i < size2; i++){
        left[size] = right[i];
        size++;
    }
}

template <class T>
void mergeRight(T left[], int size, T right[], int& size2){
    for(int i = 0; i < size; i ++){
        insertItem(right,left[i],i,size2);
    }
}

#endif // ARRAYFUNCTIONS_H
