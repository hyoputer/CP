#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

long long int fib(long long int);

long long int mod;

bool findfib(vector<long long int>, long long int);

int main()
{
    long long int num1, num2;
    vector<long long int> n1;

    cin >> mod;
    cin >> num1;

    for(int i = 0; i < num1; i++)
    {
        long long int input;
        cin >> input;
        n1.push_back(fib(input) % mod);
    }

    sort(n1.begin(), n1.end());

    cin >> num2;
    for(int i = 0; i < num2; i++)
    {
        long long int input, n2;
        bool f;
        cin >> input;
        n2 = fib(input) % mod;
        f = findfib(n1, n2);
        cout << n2 << " : " << f << endl;
    }

    return 0;
}


void multiply(long long int F[2][2], long long int M[2][2]);

void power(long long int F[2][2], long long int n);

/* function that returns nth Fibonacci number */
long long int fib(long long int n)
{
    long long int F[2][2] = {{1,1},{1,0}};
    if(n == 0)
      return 0;
    power(F, n-1);
    return F[0][0];
}

  /* Optimized version of power() in method 4 */
void power(long long int F[2][2], long long int n)
{
    if( n == 0 || n == 1)
        return;
    long long int M[2][2] = {{1,1},{1,0}};

    power(F, n/2);
    multiply(F, F);

    if( n%2 != 0 )
        multiply(F, M);
}

void multiply(long long int F[2][2], long long int M[2][2])
{
    long long int x =  (F[0][0]*M[0][0] + F[0][1]*M[1][0]) % mod;
    long long int y =  (F[0][0]*M[0][1] + F[0][1]*M[1][1]) % mod;
    long long int z =  (F[1][0]*M[0][0] + F[1][1]*M[1][0]) % mod;
    long long int w =  (F[1][0]*M[0][1] + F[1][1]*M[1][1]) % mod;

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

bool findfib(vector<long long int> v, long long int n)
{
    int h = v.size() / 2;
    if(v[h] == n)
        return true;
    else
    {
        if(h == 0)
            return false;
        auto it = v.begin() + v.size() / 2;
        if(v[h] > n)
            return findfib(vector<long long int>(v.begin(), it), n);
        else
            return findfib(vector<long long int>(it, v.end()), n);
    }
}
