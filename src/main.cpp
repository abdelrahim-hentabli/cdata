#include <iostream>
#include "Table.h"

using namespace std;

int main()
{
    int types[4] = {Table::STRING,Table::STRING,Table::INT,Table::BOOL};
    string fieldnames[4] = {"FirstName","LastName","Age","Passing"};
    Table mytable(types,fieldnames,4);
    Table::Token token[4] = {Table::Token(string("Rahim")),Table::Token(string("Hentabli")),Table::Token(22),Table::Token(true)};
    mytable.insert(token,4);
    for(int i = 0; i < 4; i++){
        token[0] = Table::Token(string("Flo"));
        token[1] = Table::Token(string("Yao"));
        token[2] = Table::Token(24);
        token[3] = Table::Token(false);
    }
    mytable.insert(token,4);
    for(int i = 0; i < 4; i++){
        token[0] = Table::Token(string("Celine"));
        token[1] = Table::Token(string("Seghbossian"));
        token[2] = Table::Token(18);
        token[3] = Table::Token(true);
    }
    mytable.insert(token,4);
    for(int i = 0; i < 4; i++){
        token[0] = Table::Token(string("Sassan"));
        token[1] = Table::Token(string("Barkeshli"));
        token[2] = Table::Token(33);
        token[3] = Table::Token(true);
    }
    mytable.insert(token,4);
    for(int i = 0; i < 4; i++){
        token[0] = Table::Token(string("Youcef"));
        token[1] = Table::Token(string("ElCoolio"));
        token[2] = Table::Token(19);
        token[3] = Table::Token(true);
    }
    mytable.insert(token,4);
    cout<<mytable<<endl;
    return 1;
}
