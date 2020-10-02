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

/////////////////////////// 문장을 입력해주세요. /////////////////////////////
string input_all[] = {"hangug woigukweo", "parkgunho",
                      "hangukwoigukweodaehakgyo keompyuteogowhakbu",
                      "keompawilreoneun jaemiwitneun goamokwida.",
                      "wyulsimhi gowbuhaewyagetda."};
////////////////////////////////////////////////////////////////////////////

vector<char> J = {'g', 'n', 'd', 'r', 'm', 'b', 's', 'w', 'j', 'z', 'k', 't', 'p', 'h', 'l', 'q', 'f', 'c', 'v'};
vector<char> M = {'a', 'e', 'i', 'o', 'u', 'y'};
vector<char> O = {' ', 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, '+', '-', '*', '/', '[', ']', '.', ',', '!', '?'};

char JMO_Converter(char ch)
{
    for (int j = 0; j < J.size(); j++)
        if (ch == J[j])
            return 'J';
    for (int m = 0; m < M.size(); m++)
        if (ch == M[m])
            return 'M';
    // for (int o = 0; o < O.size(); o++)
    //     if(ch==O[o]) return 'O';
    return 'O';
}

int main()
{

    for (int i = 0; i < sizeof(input_all) / sizeof(input_all[0]); i++)
    {
        cout << input_all[i] << endl;
        string input_str = input_all[i];
        //cout << input_str.length() << endl;

        string temp = "";
        string state = "0"; // Inital state
        string output = "";

        for (int j = 0; j < input_str.length(); j++)
        {
            char ch = input_str[j];
            char conv_ch = JMO_Converter(ch);
            if (state.compare("0") == 0)
            {
                switch (conv_ch)
                {
                case 'O':
                    output = output + ch + "|";
                    state = "0";
                    break;
                case 'J':
                    state += "J";
                    temp += ch;
                    break;
                case 'M': // error
                    state = "0";
                    temp = "";
                    break;
                }
            }
            else if (state.compare("0J") == 0)
            {
                switch (conv_ch)
                {
                case 'O': // error
                    state = "0";
                    temp = "";
                    break;
                case 'J': // error
                    state = "0";
                    temp = "";
                    break;
                case 'M':
                    state += "M";
                    temp += ch;
                    break;
                }
            }
            else if (state.compare("0JM") == 0)
            {
                switch (conv_ch)
                {
                case 'O':
                    output = output + temp + "|" + ch + "|";
                    state = "0";
                    temp = "";
                    break;
                case 'J':
                    state += "J";
                    temp += ch;
                    break;
                case 'M':
                    state += "M";
                    temp += ch;
                    break;
                }
            }
            else if (state.compare("0JMM") == 0)
            {
                switch (conv_ch)
                {
                case 'O':
                    output = output + temp + "|" + ch + "|";
                    state = "0";
                    temp = "";
                    break;
                case 'J':
                    state += "J";
                    temp += ch;
                    break;
                case 'M': // error
                    output = output + temp + "|";
                    state = "0";
                    temp = "";
                    break;
                }
            }
            else if (state.compare("0JMJ") == 0)
            {
                switch (conv_ch)
                {
                case 'O':
                    output = output + temp + "|" + ch + "|";
                    state = "0";
                    temp = "";
                    break;
                case 'J':
                    state += "J";
                    temp += ch;
                    break;
                case 'M':
                    output = output + temp[0] + temp[1] + "|";
                    state = "0JM";
                    temp = temp[2];
                    temp += ch;
                    break;
                }
            }
            else if ((state.compare("0JMMJ") == 0) || (state.compare("0JMJJ") == 0))
            {
                switch (conv_ch)
                {
                case 'O':
                    output = output + temp + "|" + ch + "|";
                    state = "0";
                    temp = "";
                    break;
                case 'J':
                    output = output + temp + "|";
                    state = "0J";
                    temp = ch;
                    break;
                case 'M':
                    output = output + temp[0] + temp[1] + temp[2] + "|";
                    state = "0JM";
                    temp = temp[3];
                    temp += ch;
                    break;
                }
            }
            // cout << temp << endl;    // for debuging
        }
        if (temp != "")
            output = output + temp + '|';
        cout << output;
        cout << endl;
    }

    return 0;
}
