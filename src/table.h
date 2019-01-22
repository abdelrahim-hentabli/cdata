#ifndef TABLE_H
#define TABLE_H

#include "Set.h"
#include "Pair.h"
#include <vector>

class Table{
public:
    struct Token{
        Token();

        Token(string s);
        Token(bool b);
        Token(int i);
        Token(char c);
        Token(double d);

        friend ostream& operator <<(const ostream& out, const Token& printMe);

        friend bool operator ==(const Token& RHS, const Token& LHS);

        friend bool operator !=(const Token& RHS, const Token& LHS);

        friend bool operator <(const Token& RHS, const Token& LHS);

        friend bool operator <=(const Token& RHS, const Token& LHS);

        friend bool operator >(const Token& RHS, const Token& LHS);

        friend bool operator >=(const Token& RHS, const Token& LHS);

        int type;

        bool boolean;
        int integer;
        char chr;
        double dub;
        string str;
    };
    static const int BOOL = 1;
    static const int INT = 2;
    static const int CHAR = 3;
    static const int DOUBLE = 4;
    static const int STRING = 5;
    Table();
    Table(int types[], string colnames[], int s);

    void insert(Token input[], int s);

    friend ostream& operator <<(ostream& out, const Table& printMe);


private:
    int size;
    Pair<string, int>* fieldnames;
    set<Pair<Token, vector<int> > >* Btree;
    vector<Token*> tableArray;
    int position;


};

Table::Token::Token(){
    type = 1;
    boolean = false;
    integer = 0;
    chr = char();
    dub = 0.0;
    str = "";
}

Table::Token::Token(bool b){
    type = 1;
    boolean = b;
    integer = 0;
    chr = char();
    dub = 0.0;
    str = "";
}

Table::Token::Token(int i){
    type = 2;
    boolean = false;
    integer = i;
    chr = char();
    dub = 0.0;
    str = "";
}

Table::Token::Token(char c){
    type = 3;
    boolean = false;
    integer = 0;
    chr = c;
    dub = 0.0;
    str = "";
}

Table::Token::Token(double d){
    type = 4;
    boolean = false;
    integer = 0;
    chr = char();
    dub = d;
    str = "";
}

Table::Token::Token(string s){
    type = 5;
    boolean = false;
    integer = 0;
    chr = char();
    dub = 0.0;
    str = s;
}

ostream& operator <<(ostream& out, const Table::Token& printMe){
    if(printMe.type == Table::BOOL){
        return out<<printMe.boolean;
    }
    else if(printMe.type == Table::INT){
        return out<<printMe.integer;
    }
    else if(printMe.type == Table::CHAR){
        out<<printMe.chr;
    }
    else if(printMe.type == Table::DOUBLE){
        return out<<printMe.dub;
    }
    else if(printMe.type == Table::STRING){
        return out<<printMe.str;
    }
    else{
        return out;
    }
}

bool operator ==(const Table::Token& RHS, const Table::Token& LHS){
    if(RHS.type != LHS.type){
        return false;
    }
    if(RHS.type == Table::BOOL){
        return RHS.boolean == LHS.boolean;
    }
    else if(RHS.type == Table::CHAR){
        return RHS.chr == LHS.chr;
    }
    else if(RHS.type == Table::DOUBLE){
        return RHS.dub == LHS.dub;
    }
    else if(RHS.type == Table::INT){
        return RHS.integer == LHS.integer;
    }
    else if(RHS.type == Table::STRING){
        return RHS.str == LHS.str;
    }
    else{
        return false;
    }
}

bool operator !=(const Table::Token& RHS, const Table::Token& LHS){
    if(RHS.type != LHS.type){
        return true;
    }
    if(RHS.type == Table::BOOL){
        return RHS.boolean != LHS.boolean;
    }
    else if(RHS.type == Table::CHAR){
        return RHS.chr != LHS.chr;
    }
    else if(RHS.type == Table::DOUBLE){
        return RHS.dub != LHS.dub;
    }
    else if(RHS.type == Table::INT){
        return RHS.integer != LHS.integer;
    }
    else if(RHS.type == Table::STRING){
        return RHS.str != LHS.str;
    }
}

bool operator >(const Table::Token& RHS, const Table::Token& LHS){
    if(RHS.type != LHS.type){
        cout<<RHS.type<<"|"<<LHS.type<<endl;
        //cout<<RHS.str<<"|"<<LHS.boolean<<endl;
        throw 1;
    }
    if(RHS.type == Table::BOOL){
        return RHS.boolean > LHS.boolean;
    }
    else if(RHS.type == Table::CHAR){
        return RHS.chr > LHS.chr;
    }
    else if(RHS.type == Table::DOUBLE){
        return RHS.dub > LHS.dub;
    }
    else if(RHS.type == Table::INT){
        return RHS.integer > LHS.integer;
    }
    else if(RHS.type == Table::STRING){
        return RHS.str > LHS.str;
    }
}


Table::Table(int types[], string colnames[], int s){
    position = 0;
    size = s;
    fieldnames = new Pair<string, int>[size];
    for(int i = 0; i < size; i ++){
        fieldnames[i] = Pair<string, int>(colnames[i], types[i]);
    }
    Btree = new set<Pair<Token, vector<int> > >[size];

}

void Table::insert(Table::Token input[], int s)
{
    vector <int> pos;
    pos.push_back(position);

    if(s != size){
        throw 's';
    }
    for(int i = 0; i < size; i++){
        if(input[i].type != fieldnames[i].value){
            cout<<i<<" "<<input[i].type<<" "<<fieldnames[i].value<<endl;
            throw 1;
        }
        else{
            if(Btree[i].search(Pair<Token, vector<int> >(input[i],vector<int>())) != Pair<Token, vector<int> >()){
                Btree[i].search(Pair<Token, vector<int> >(input[i],vector<int>())).value.push_back(position);
            }
            else{
                Btree[i].insert(Pair<Token, vector<int> >(input[i],vector<int>(pos)));
            }
        }
    }
    Token t[s];
    for(int i = 0; i < s; i++){
        t[i] = input[i];
    }
    tableArray.push_back(t);
    position++;

}


ostream& operator <<(ostream& out, const Table& printMe){
    int size = printMe.Btree->inorder().size();
    for(int i = 0; i < size; i ++){
        int size2 = printMe.Btree->inorder()[i].value.size();
        for(int j = 0; j < size2; j++){
            //out<<printMe.Btree->inorder()[i].key.str<<endl;
            for(int k = 0; k < printMe.size; k++){
                out<<printMe.tableArray[printMe.Btree->inorder()[i].value[j]][k].str;
            }
        }
    }

    return out;
}


#endif // TABLE_H
