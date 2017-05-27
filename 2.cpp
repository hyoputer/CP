//============================================================================
// Name        : 1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

double cal(string);
double oper(char, double, double);
int pre(char);

vector<char> wchar;
vector<string> wop;

int main() {

    int w;
    cin >> w;

    string input;

    for(int i = 0; i < w; i++)
    {
        char wildch;
        string wildop;
        cin >> wildch >> wildop;
        wchar.push_back(wildch);
        wop.push_back(wildop);
    }

    cin >> input;

    cout.precision(3);
    cout << fixed << cal(input) << endl;

    return 0;
}

double cal(string input)
{
    input += "+0";
    bool opf = true;
    vector<string> post;
    vector<char> stack;
    vector<double> s;
    int b = 0;

    for(int i = 0; i < input.size(); i++)
    {
        if((input[i] < '0' || input[i] > '9') && input[i] != '.')
        {
            if(b != i)
                post.push_back(input.substr(b, i - b));
            b = i + 1;

            if(input[i] == '(')
            {
                stack.push_back(input[i]);
                opf = true;
            }
            else if(input[i] == ')')
            {
                while(true)
                {
                    post.push_back(string(1, stack.back()));
                    stack.pop_back();
                    if(stack.back() == '(')
                    {
                        stack.pop_back();
                        break;
                    }
                }
                opf = false;
            }
            else if(opf == true && input[i] == '-')
                stack.push_back('~');
            else
            {
                while(!stack.empty())
                {
                    if(pre(input[i]) <= pre(stack.back()))
                    {
                        post.push_back(string(1, stack.back()));
                        stack.pop_back();
                    }
                    else
                        break;
                }
                stack.push_back(input[i]);
                opf = true;
            }
        }
        else
        {
            opf = false;
        }
    }

    while(stack.size() > 1)
    {
        post.push_back(string(1, stack.back()));
        stack.pop_back();
    }

 /*   for(int i = 0; i < post.size(); i++)
        cout << post[i] << endl;*/

    for(int i = 0; i < post.size(); i++)
    {
        if(post[i][0] > '9' || post[i][0] < '0')
        {
            if(post[i][0] == '~')
            {
                double n = s.back();
                n *= (-1);
                s.pop_back();
                s.push_back(n);
            }
            else
            {
                double a = s.back();
                s.pop_back();
                double b = s.back();
                s.pop_back();
                s.push_back(oper(post[i][0], a, b));
            }
        }
        else
        {
            s.push_back(stod(post[i]));
        }
    }

    return s.back();
}

double oper(char op, double a, double b)
{
    int idx;
    if(op == '+')
        return a + b;
    else if(op == '*')
        return a * b;
    else if(op == '-')
        return b - a;
    else if(op == '/')
        return b / a;
    else
    {
        for(int i = 0; i < wchar.size(); i++)
        {
            if(op == wchar[i])
            {
                idx = i;
                break;
            }
        }

        string wild = wop[idx];
        for(int i = 0; i < wild.size(); i++)
        {
            if(wild[i] == 'A' || wild[i] == 'B')
            {
                if(wild[i] == 'A')
                {
                    wild.erase(wild.begin()+i);
                    wild.insert(i, to_string(b));
                }
                else
                {
                    wild.erase(wild.begin()+i);
                    wild.insert(i, to_string(a));
                }
            }
        }


        return cal(wild);
    }
}

int pre(char op)
{
    if(op == '+' || op == '-')
        return 1;
    else if(op == '(')
        return 0;
    else if(op == '~')
        return 3;
    else
        return 2;
}
