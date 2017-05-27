#include<iostream>
#include<deque>
using namespace std;

class Pixel
{
public:
    void hi(short, short);
    void clear();
    void mark(short, short, char);
    void vertical(short, short, short, char);
    void horizon(short, short, short, char);
    void fill(short, short, short, short, char);
    void rect(short, short, short, short, char);
    void change(short, short, char);
    void bye();
private:
    char arr[30][30];
    short height;
    short width;
};

int main()
{
    string input;

    Pixel p;
    char c;

    while(true)
    {
        cin >> input;
        if(input == "hi")
        {
            short m, n;
            cin >> m >> n;
            p.hi(m, n);
        }
        else if(input == "clean" || input == "clear")
            p.clear();
        else if(input == "mark")
        {
            short x, y;
            cin >> x >> y >> c;
            p.mark(x, y, c);
        }
        else if(input == "vertical")
        {
            short x, y1, y2;
            cin >> x >> y1 >> y2 >> c;
            p.vertical(x, y1, y2, c);
        }
        else if(input == "horizon")
        {
            short x1, x2, y;
            cin >> x1 >> x2 >> y >> c;
            p.horizon(x1, x2, y, c);
        }
        else if(input == "fill")
        {
            short x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2 >> c;
            p.fill(x1, y1, x2, y2, c);
        }
        else if(input == "rect")
        {
            short x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2 >> c;
            p.rect(x1, y1, x2, y2, c);
        }
        else if(input == "change")
        {
            short x, y;
            cin >> x >> y >> c;
            p.change(x, y, c);
        }
        else if(input == "bye")
        {
            p.bye();
            return 0;
        }
    }
}

void Pixel::hi(short m, short n)
{
    width = n;
    height = m;
    clear();
}
void Pixel::clear()
{
    for(short i = 0; i < height; i++)
        for(short j = 0; j < width; j++)
            arr[i][j] = 'O';
}
void Pixel::mark(short x, short y, char c)
{
    arr[y - 1][x - 1] = c;
}
void Pixel::vertical(short x, short y1, short y2, char c)
{
    for(short i = y1 - 1; i <= y2 - 1; i++)
        arr[i][x - 1] = c;
}
void Pixel::horizon(short x1, short x2, short y, char c)
{
    for(short i = x1 - 1; i <= x2 - 1; i++)
        arr[y - 1][i] = c;
}
void Pixel::fill(short x1, short y1, short x2, short y2, char c)
{
    for(short i = y1 - 1; i <= y2 - 1; i++)
        for(short j = x1 - 1; j <= x2 - 1; j++)
            arr[i][j] = c;
}
void Pixel::rect(short x1, short y1, short x2, short y2, char c)
{
    for(short i = x1 - 1; i <= x2 - 1; i++)
    {
        arr[y1 - 1][i] = c;
        arr[y2 - 1][i] = c;
    }
    for(short i = y1 - 1; i <= y2 - 1; i++)
    {
        arr[i][x1 - 1] = c;
        arr[i][x2 - 1] = c;
    }
}
void Pixel::change(short x, short y, char c)
{
    deque<pair<short, short>> q;
    char area = arr[y - 1][x - 1];
    arr[y - 1][x - 1] = c;
    q.push_back({y - 1, x - 1});
    while(!q.empty())
    {
        pair<short, short> p = q.front();
        q.pop_front();
        char a = p.first;
        char b = p.second;
        if(arr[a - 1][b] == area)
        {
            arr[a - 1][b] = c;
            q.push_back({a - 1, b});
        }
        if(arr[a][b - 1] == area)
        {
            arr[a][b - 1] = c;
            q.push_back({a, b - 1});
        }
        if(arr[a + 1][b] == area)
        {
            arr[a + 1][b] = c;
            q.push_back({a + 1, b});
        }
        if(arr[a][b + 1] == area)
        {
            arr[a][b + 1] = c;
            q.push_back({a, b + 1});
        }
    }

    return;
}
void Pixel::bye()
{
    for(short i = 0; i < height; i++)
    {
        for(short j = 0; j < width; j++)
            cout << arr[i][j];
        cout << endl;
    }
}
