/*
* 2020.10.02 DevGun
* 
* 자음(J), 모음(M)의 다음 형식으로 구성된 한글 Automata를 만든다.
* 한글 text = (JM+JMJ+JMM+JMMJ+JMJJ+O)  // O는 기타 char.
*           eg.) 가+각+과+곽+값+!
* J = {g,n,d,r,m,b,s,w,j,z,k,t,p,h,q,f ...}
* M = {a,e,i,o,u,y ...}
* O = {" ", 1,2,3,4,5,6,7,8,9,0,+,-,*,/,[,],....}
*
* g++ -o output hangulAutomata.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string input_all[] = {"hangug woigukweo",
                      "hangukwoigukweodaehakgyo keompyuteogowhakbu",
                      "keompawilreoneun jaemiwitneun goamokwida.",
                      "wyulsimhi gowbuhaewyagetda."};
string temp;
string state = "0"; // Inital state
string output;

vector<char> J = {'g', 'n', 'd', 'r', 'm', 'b', 's', 'w', 'j', 'z', 'k', 't', 'p', 'h', 'l', 'q', 'f', 'c', 'v'};
vector<char> M = {'a', 'e', 'i', 'o', 'u', 'y'};
vector<char> O = {' ', 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, '+', '-', '*', '/', '[', ']', '.', ',', '!', '?'};

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter))
    {
        internal.push_back(temp);
    }

    return internal;
}

char JMO_Converter(char ch)
{
    for (int j = 0; j < J.size(); j++)
        if(ch==J[j]) return 'J';
    for (int m = 0; m < M.size(); m++)
        if(ch==M[m]) return 'M';
    // for (int o = 0; o < O.size(); o++)
    //     if(ch==O[o]) return 'O';
    return 'O';
}

int main()
{

    for (int i = 0; i < sizeof(input_all) / sizeof(input_all[0]); i++)
    {
        //cout << input_all[i] << endl;
        vector<string> input_str = split(input_all[i], ' ');
        //cout << input_str.size() << endl;

        for (int j = 0; j < input_str.size(); j++)
        {
            for (int k = 0; k < input_str[j].length(); k++)
            {
                char ch = input_str[j][k];
                char conv_ch = JMO_Converter(ch);
                cout << conv_ch;
            }
            cout << " ";
        }
        cout << endl;
    }
    return 0;
}
