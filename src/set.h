#ifndef SET_H
#define SET_H

#include <iostream>
#include "ArrayFunctions.h"
#include <vector>

using namespace std;


template <class T>
class set{
public:
    //Default Ctor
    static const int MINIMUM = 1;
    set();
    set(T copyArray[MINIMUM * 2 + 1], set<T>* copyChildren[MINIMUM * 2 + 2], int d, int c);
    //Copy Ctor
    set(const set<T>& RHS);
    //Assig Oper
    set& operator =(const set<T>& RHS);
    //Dtor
    ~set();
    //cout
    template <class U>
    friend ostream& operator <<(ostream& out, const set<U>& printMe);
    ostream& print(ostream& out, int levels = 0) const;
    T search(T entry);
    void insert(T entry);
    bool erase(T entry);
    bool isEmpty();
    T rightMost();
    vector<T> inorder();
private:
    T eraseBiggest();
    bool looseErase(T entry);
    void looseInsert(T entry);
    void fixExcess(int childNum);
    void fixDeficiency(int childNum);
    //member variables
    T array[MINIMUM * 2 + 1];
    set* children[MINIMUM*2 + 2];
    int dataCount;
    int childCount;

};

template <class T>
set<T>::set(){
    dataCount = 0;
    childCount = 0;
}

template <class T>
set<T>::set(T copyArray[], set<T>* copyChildren[], int d, int c){
    for(int i = 0; i < d; i ++){
        array[i] = copyArray[i];
    }
    for(int i = 0; i < c; i ++){
        children[i] = copyChildren[i];
    }
    dataCount = d;
    childCount = c;
}

template<class T>
set<T>::set(const set<T> &RHS)
{
    dataCount = RHS.dataCount;
    childCount = RHS.childCount;
    for(int i = 0; i < dataCount; i++){
        array[i] = RHS.array[i];
    }
    for(int i = 0; i < childCount; i++){
        children[i] = new set(*RHS.children[i]);
    }
}

template<class T>
set<T>& set<T>::operator =(const set<T> &RHS)
{
    for(int i= 0; i < childCount; i++){
        delete children[i];
    }
    dataCount = RHS.dataCount;
    childCount = RHS.childCount;
    for(int i = 0; i < dataCount; i++){
        array[i] = RHS.array[i];
    }
    for(int i = 0; i < childCount; i++){
        children[i] = new set(RHS.children[i]);
    }
}

template<class T>
set<T>::~set()
{
    for(int i= 0; i < childCount; i++){
        delete children[i];
    }
}

template <class U>
ostream& operator <<(ostream& out, const set<U>& printMe){
    return printMe.print(out);
}

template <class T>
ostream& set<T>::print(ostream &out, int levels) const{
    if (childCount == 0){
        out<<string(levels,' ');
        out<<'{';
        for(int i = 0;i < dataCount;i++){
            out<<array[i];
            if(i == dataCount - 1){
                out<<'}';
            }
            else{
                out<<',';
            }
        }
    }
    else{
        for(int i = dataCount; i >= 1; i--){
            children[i]->print(out,levels+5)<<endl;
            out<<string(levels,' ')<<array[i-1]<<endl;
        }
        children[0]->print(out,levels+5)<<endl;

    }
    return out;
}

template <class T>
T set<T>::search(T entry){
    int temp = greaterThanOrEqual(array,entry,dataCount);
    if(array[temp] == entry){
        return array[temp];
    }
    else if(childCount == 0){
        return T();
    }
    else{
        return children[temp]->search(entry);
    }
}

template <class T>
void set<T>::insert(T entry){
    looseInsert(entry);
    if(dataCount == MINIMUM*2 + 1){
        T temp[MINIMUM * 2 + 1];
        int d = 0;
        set<T>* temp2[MINIMUM * 2 + 2];
        int c = 0;
        split(array,dataCount,temp, d);
        split(children,childCount,temp2, c);
        T top = array[dataCount-1];
        dataCount--;
        set<T>* left = new set(array, children,dataCount, childCount);
        set<T>* right = new set(temp,temp2,d,c);
        dataCount = 1;
        childCount = 2;
        array[0] = top;
        children[0] = left;
        children[1] = right;
    }
}

template <class T>
bool set<T>::erase(T entry){
    bool temp = looseErase(entry);
    if(temp && dataCount == 0 && childCount == 1){
        set<T>* t = children[0];
        for(int i = 0; i < t->dataCount;i++){
            array[i] = t->array[i];
        }
        for(int i = 0; i < t->childCount;i++){
            children[i] = t->children[i];
        }
        dataCount = t->dataCount;
        childCount = t->childCount;
        t->childCount = 0;
        delete t;


    }
    return temp;
}

template <class T>
T set<T>::rightMost(){
    if(childCount == 0){
        return array[dataCount-1];
    }
    else{
        return children[childCount-1]->rightMost();
    }
}

template <class T>
bool set<T>::isEmpty(){
    return dataCount == 0;
}



template <class T>
T set<T>::eraseBiggest(){
    if(childCount == 0){
        dataCount--;
        return array[dataCount];
    }
    else{
        T temp = children[childCount - 1]->eraseBiggest();
        if(children[childCount - 1]->dataCount < MINIMUM){
            fixDeficiency(childCount - 1);
        }
        return temp;
    }
}

template <class T>
bool set<T>::looseErase(T entry){
    int temp = greaterThanOrEqual(array,entry,dataCount);
    if(temp == dataCount && childCount == 0){
        return false;
    }
    else if(array[temp] == entry){
        if(childCount == 0){
            remove(array,dataCount,temp);
        }
        else{
            array[temp] = children[temp]->eraseBiggest();
            if(children[temp]->dataCount < MINIMUM){
                fixDeficiency(temp);
            }
        }
        return true;
    }
    else if(childCount == 0){
        return false;
    }
    else{
        bool t =  children[temp]->looseErase(entry);
        if(children[temp]->dataCount < MINIMUM){
            fixDeficiency(temp);
        }
        return t;
    }
}

template <class T>
void set<T>::looseInsert(T entry){
    if(childCount == 0){
        insertSorted(array,entry,dataCount);
    }
    else{
        int temp = greaterThanOrEqual(array,entry,dataCount);
        children[temp]->looseInsert(entry);
        if(children[temp]->dataCount == MINIMUM * 2 + 1){
            fixExcess(temp);
        }
    }
}

template <class T>
void set<T>::fixExcess(int childNum){

    T temp[MINIMUM * 2 + 1];
    int d = 0;
    set<T>* temp2[MINIMUM * 2 + 2];
    int c = 0;
    split(children[childNum]->array,children[childNum]->dataCount,temp, d);
    split(children[childNum]->children,children[childNum]->childCount,temp2, c);
    insertItem(array,children[childNum]->array[children[childNum]->dataCount - 1],childNum,dataCount);
    children[childNum]->dataCount--;
    insertItem(children,new set<T>(temp,temp2,d,c),childNum+1,childCount);

}

template <class T>
void set<T>::fixDeficiency(int childNum){
    //borrowing
    if(childNum < childCount - 1 && children[childNum + 1]->dataCount > MINIMUM){
        insertItem(children[childNum]->array,array[childNum],0,children[childNum]->dataCount);
        array[childNum] = children[childNum + 1]->array[0];
        remove(children[childNum + 1]->array,children[childNum + 1]->dataCount,0);
        if(children[childNum + 1]->childCount > 0){
            //Not Tested
            insertItem(children[childNum]->children,children[childNum + 1]->children[0],children[childNum]->childCount,children[childNum]->childCount);
            remove(children[childNum + 1]->children,children[childNum + 1]->childCount, 0);
        }

    }
    else if(childNum > 0 && children[childNum - 1]->dataCount > MINIMUM){
        insertItem(children[childNum]->array,array[childNum - 1],0,children[childNum]->dataCount);
        array[childNum-1] = children[childNum - 1]->array[children[childNum - 1]->dataCount - 1];
        children[childNum - 1]->dataCount--;
        if(children[childNum-1]->childCount > 0){
            //Not Tested
            insertItem(children[childNum]->children,children[childNum - 1]->children[children[childNum-1]->childCount - 1],0,children[childNum]->childCount);
            children[childNum - 1]->childCount--;
        }
    }
    //merging
    else if(childNum < childCount - 1){
        insertItem(children[childNum]->array,array[childNum],children[childNum]->dataCount,children[childNum]->dataCount);
        remove(array,dataCount,childNum);
        mergeLeft(children[childNum]->array,children[childNum]->dataCount,children[childNum + 1]->array, children[childNum + 1]-> dataCount);
        //Not Tested
        mergeLeft(children[childNum]->children,children[childNum]->childCount,children[childNum + 1]->children, children[childNum + 1]->childCount);
        children[childNum + 1]->childCount = 0;
        delete children[childNum + 1];
        remove(children,childCount,childNum + 1);
    }
    else if(childNum > 0){
        insertItem(children[childNum]->array, array[childNum -1],0,children[childNum]->dataCount);
        remove(array,dataCount,childNum-1);
        mergeRight(children[childNum - 1]->array, children[childNum - 1]->dataCount, children[childNum]->array, children[childNum]->dataCount);
        //Not Tested
        mergeRight(children[childNum-1]->children,children[childNum - 1]->childCount,children[childNum]->children,children[childNum]->childCount);
        children[childNum - 1]->childCount = 0;
        delete children[childNum - 1];
        remove(children,childCount,childNum-1);
    }
    else{
        cout<<"You Fucked Up"<<endl;
        throw 10;
    }

}

template <class T>
vector<T> set<T>::inorder(){
    vector<T> temp;
    vector<T> temp2;
    if(childCount == 0){
        for(int i = 0; i < dataCount; i++){
            temp.push_back(array[i]);
        }
    }
    else{
        for(int i = 0; i < dataCount; i++){
            temp2 = children[i]->inorder();
            temp.insert(temp.end(),temp2.begin(),temp2.end());
            temp.push_back(array[i]);
        }
        temp2 = children[dataCount]->inorder();
        temp.insert(temp.end(),temp2.begin(),temp2.end());
    }
    return temp;
}

#endif // SET_H
