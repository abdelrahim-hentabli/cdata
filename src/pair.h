#ifndef PAIR_H
#define PAIR_H

#include <iostream>

using namespace std;


template <class T, class U>
class Pair{
public:
    Pair();
    Pair(T k, U v);

    //cout
    template <class T2, class U2>
    friend ostream& operator << (ostream& out, const Pair<T2,U2>& printMe);


    //equality/inequality operators
    template <class T2, class U2>
    friend bool operator <(const Pair<T2,U2>& LHS, const Pair<T2,U2>& RHS);


    template <class T2, class U2>
    friend bool operator <=(const Pair<T2,U2>& LHS, const Pair<T2,U2>& RHS);


    template <class T2, class U2>
    friend bool operator >(const Pair<T2,U2>& LHS, const Pair<T2,U2>& RHS);


    template <class T2, class U2>
    friend bool operator >=(const Pair<T2,U2>& LHS, const Pair<T2,U2>& RHS);

    template <class T2, class U2>
    friend bool operator ==(const Pair<T2,U2>& LHS, const Pair<T2,U2>& RHS);

    template <class T2, class U2>
    friend bool operator !=(const Pair<T2,U2>& LHS, const Pair<T2,U2>& RHS);


    T key;
    U value;

};

template<class T, class U>
Pair<T,U>::Pair()
{
   key =  T();
   value = U();
}

template <class T, class U>
Pair<T,U>::Pair(T k, U v){
    key = k;
    value = v;
}

template <class T2, class U2>
ostream& operator <<(ostream& out, const Pair<T2,U2>& printMe){
    return out<<'['<<printMe.key<<','<<printMe.value<<']';
}

template<class T2, class U2>
bool operator <(const Pair<T2, U2> &LHS, const Pair<T2, U2> &RHS)
{
    return LHS.key < RHS.key;
}

template<class T2, class U2>
bool operator <=(const Pair<T2, U2> &LHS, const Pair<T2, U2> &RHS)
{
    return LHS.key <= RHS.key;
}

template<class T2, class U2>
bool operator >(const Pair<T2, U2> &LHS, const Pair<T2, U2> &RHS)
{
    return LHS.key > RHS.key;
}

template<class T2, class U2>
bool operator >=(const Pair<T2, U2> &LHS, const Pair<T2, U2> &RHS)
{
    return LHS.key >= RHS.key;
}

template<class T2, class U2>
bool operator ==(const Pair<T2, U2> &LHS, const Pair<T2, U2> &RHS)
{
    return LHS.key == RHS.key;
}

template<class T2, class U2>
bool operator !=(const Pair<T2, U2> &LHS, const Pair<T2, U2> &RHS)
{
    return LHS.key != RHS.key;
}


#endif // PAIR_H



