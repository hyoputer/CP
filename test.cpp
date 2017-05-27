#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

int& foo(int& a)
{ return a;}

int main(int argc, char*argv[])
{
    /*int a(200);

    string s;
    char cstr[s.length()];

    char * ptr;

    ifstream ifs(argv[1]);
    getline(ifs, s);
    strcpy(cstr, s.c_str());
    ptr = strtok(cstr, ",");
    cout << ptr;*/
    
    string s1, s2;

    cin >> s1 >> s2;
    cout << (stod(s1) < stod(s2));
}
