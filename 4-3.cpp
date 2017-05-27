#include<iostream>
#include<algorithm>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int main()
{
    int num;

    cin >> num;

    short *a = (short*)malloc(sizeof(short)*num);

    short n;
    for(int i = 0; i < num; i++)
    {
        cin >> n;
        a[i] = n;
    }

    sort(a, a + num);

    for(int i = 0; i < num; i++)
    {
        cout << a[i];
        cout.put('\n');
    }

    return 0;
}
