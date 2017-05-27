#include <iostream>
using namespace std;

class Bingo {
public:
    Bingo(int t, int m, int n): num(t), hieght(m), width(n)
    {
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                cin >> arr[i][j];
        for(int i = 0; i < t; i++)
            cin >> words[i];
    }

    void check();

private:
    int num, hieght, width;
    char arr[30][30];
    string words[10];
    bool checkword(int a, int b, int w);
    bool checkdir(int a, int b, int w, int d); 
    bool checkchar(int a, int b, int w, int i);
};

int main()
{
    int t, m, n;

    cin >> t >> m >> n;
    Bingo b(t, m, n);
    b.check();
}

void Bingo::check()
{
    bool f;
    for(int k = 0; k < num; k++)
    {
        f = false;
        for(int i = 0; i < hieght; i++)
            for(int j = 0; j < width; j++)
            {
                if(checkchar(i, j, k, 0))
                {
                    if(checkword(i, j, k))
                    {
                        cout << i + 1 << " " << j + 1 << endl;
                        i = hieght;
                        j = width;
                        f = true;
                        continue;
                    }
                }
            }
        if(!f)
            cout << "false" << endl;
    }
}

bool Bingo::checkchar(int a, int b, int w, int i)
{
    return (tolower(arr[a][b]) == tolower(words[w][i]));
}

bool Bingo::checkword(int a, int b, int w)
{
    for(int i = 0; i < 8; i++)
    {
        if(checkdir(a, b, w, i))
            return true;
    }
    return false;
}

bool Bingo::checkdir(int a, int b, int w, int d)
{
    bool f = true;
    for(int i = 0; i < words[w].size(); i++)
    {
        switch(d)
        {
            case 0:
                if(!checkchar(a - i, b - i, w, i))
                    f =  false;
                break;
            case 1:
                if(!checkchar(a, b - i, w, i))
                    f =  false;
                break;
            case 2:
                if(!checkchar(a + i, b - i, w, i))
                    f = false;
                break;
            case 3:
                if(!checkchar(a + i, b, w, i))
                    f = false;
                break;
            case 4:
                if(!checkchar(a + i, b + i, w, i))
                    f = false;
                break;
            case 5:
                if(!checkchar(a, b + i, w, i))
                    f = false;
                break;
            case 6:
                if(!checkchar(a - i, b + i, w, i))
                    f = false;
                break;
            case 7:
                if(!checkchar(a - i, b, w, i))
                    f = false;
                break;
        }
        if(!f)
            return f;
    }

    return f;
}
