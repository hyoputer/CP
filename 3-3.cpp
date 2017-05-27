#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class BigInteger {
public:
    BigInteger(string _value)
    {
        for(int i = 0; i < _value.size(); i++)
            value[i] = _value[_value.size() - 1 - i] - '0';
        size = _value.size();
    }

    BigInteger &operator+(const BigInteger &bi) 
    {
        int s1 = 0;
        int s2 = 0;
        int sum[300] = {};
        int sr = 0;
        
        while(true)
        {
            if(s1 >= size && s2 >= bi.size)
                break;
            else if(s1 >= size)
                sum[sr++] += bi.value[s2++];
            else if(s2 >= bi.size)
                sum[sr++] += value[s1++];

            else
            {
                sum[sr] += (value[s1++] + bi.value[s2++]);
                if(sum[sr] > 9)
                {
                    sum[sr] %= 10;
                    sum[sr + 1] = 1;
                    if(s1 == 0 && s2 == 0)
                        sr++;
                }
                sr++;
            }
        }

        for(int i = 0; i < sr; i++)
            value[i] = sum[i];
        size = sr;
        return *this;
        
    }

    BigInteger &operator*(const BigInteger &bi)
    {
        int s1 = size;
        int s2 = bi.size;
        int sum[300] = {};
        int sr;
        for(int i = 0; i < s1; i++)
            for(int j = 0; j < s2; j++)
            {
                int k  = i + j;
                sum[k] += value[i] * bi.value[j];
                if(sum[k] >= 10)
                {
                    sum[k + 1] += sum[k] / 10;
                    sum[k] %= 10;
                }
            }

        if(sum[s1 + s2 - 1] != 0)
            sr = s1 + s2;
        else
            sr = s1 + s2 - 1;

        for(int i = 0; i < sr; i++)
            value[i] = sum[i];
        size = sr;
        return *this;
    }

    void print();

private:
    int value[300];
    int size;
};

int main()
{
    string input;
    getline(cin, input);
    vector<BigInteger> v;
    bool mf = false;

    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end() );
    input += "+0";

    int b = 0;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == '+' || input[i] == '*')
        {
            v.push_back(BigInteger(input.substr(b, i - b)));
            b = i + 1;

            if(mf)
            {
                BigInteger temp = v.back();
                v.pop_back();
                temp = temp * v.back();
                v.pop_back();

                v.push_back(temp);
                mf = false;
            }
            
            if(input[i] == '*')
                mf = true;
        }
    }

    while(v.size() > 1)
    {
        BigInteger temp = v.back();
        v.pop_back();
        temp = temp + v.back();
        v.pop_back();
        v.push_back(temp);
    }

    v.back().print();

    return 0;
}

void BigInteger::print()
{
    for(int i = size - 1; i >= 0; i--)
        printf("%d", value[i]);
}
