#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool check_prime(int n);

int main()
{
    int num;
    vector<int> v;

    while(cin >> num)
    {
        if(num == -1)
            break;
        else
            v.push_back(num);
    }

    auto it = remove_if(v.begin(), v.end(), check_prime);

    sort(v.begin(), it);

    it = unique(v.begin(), it);

    auto begin = v.begin();

    while(begin != it)
    {
        cout << *begin << " ";
        begin++;
    }
    return 0;
}

bool check_prime(int n)
{
    int i;
    bool flag = true;
    for(i = 2; i <= n / 2 ; ++i)
    {
        if(n % i == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
