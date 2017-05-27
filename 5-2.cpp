#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Pivot
{
public:
    Pivot(string c, double d): category1(c), data(d) {}
    Pivot(string c1, string c2, double d): category1(c1), category2(c2), data(d) {}

    inline string getc() { return category1; }
    inline string getc2() { return category2; }
    inline double getd() { return data; }
private:
    string category1;
    string category2;
    double data;
};

class Movie
{
    friend void pivot1(string, string, string);
    friend void pivot2(string, string, string, string);
    friend void originaltable();
public:
    Movie(string _n, string _g, string _s, double _p, double _gr, double _r):
        name(_n), category{_g, _s}, data{_p, _gr, _r} {}
private:
    string name;
    string category[2];
    double data[3];
};

vector<Movie> db;
vector<Pivot> p1;
vector<vector<Pivot>> p2;
bool pf;
int b;

void get_table();
bool commands(string);
void pivot1(string, string, string);
void pivot2(string, string, string, string);
void originaltable();
void pivottable();
void pivotchart();
inline void pivotclear() { p1.clear(); p2.clear(); }

int main()
{
    string input;

    get_table();

    do{ cin >> input; }while(commands(input));

    return 0;
}

void get_table()
{
    int num;
    string n, g, s;
    double p, gr, r;

    cin >> num;
    for(int i = 0; i < num; i++)
    {
        cin >> n >> g >> s >> p >> gr >> r;
        db.emplace_back(n, g, s, p, gr, r);
    }
}

bool commands(string input)
{
    string ar1, ar2, ar3, ar4;
    if(input == "pivot1")
    {
        cin >> ar1 >> ar2 >> ar3;
        pivot1(ar1, ar2, ar3);
    }
    else if(input == "pivot2")
    {
        cin >> ar1 >> ar2 >> ar3 >> ar4;
        pivot2(ar1, ar2, ar3, ar4);
    }
    else if(input == "pivottable")
        pivottable();
    else if(input == "pivotchart")
        pivotchart();
    else if(input == "originaltable")
        originaltable();
    else if(input == "close")
        return false;
    else
        cout << "wrong command" << endl;

    return true;
}

void pivot1(string c, string n, string f)
{
    int a;
    vector<string> vs;
    vector<vector<double>> vd;

    pivotclear();

    if(c == "Genre")
    {
        a = 0;
        pf = false;
    }
    else
    {
        a = 1;
        pf = true;
    }
    if(n == "Production")
        b = 0;
    else if(n == "Gross")
        b = 1;
    else
        b = 2;

    for(int i = 0; i < db.size(); i++)
    {
        bool f = false;
        string mc = db[i].category[a];
        for(int j = 0; j < vs.size(); j++)
        {
            if(vs[j] == mc)
            {
                vd[j].emplace_back(db[i].data[b]);
                f = true;
                break;
            }
        }

        if(!f)
        {
            vs.push_back(mc);
            vd.push_back(vector<double>(1, db[i].data[b]));
        }
    }

    if(f == "ave")
    {
        for(int i = 0; i < vs.size(); i++)
        {
            double res = 0;

            for(int j = 0; j < vd[i].size(); j++)
            {
                res += vd[i][j];
            }
            
            res /= vd[i].size();

            p1.emplace_back(vs[i], res);
        }
    }

    else if(f == "tot")
    {
        for(int i = 0; i < vs.size(); i++)
        {
            double res = 0;

            for(int j = 0; j < vd[i].size(); j++)
            {
                res += vd[i][j];
            }

            p1.emplace_back(vs[i], res);
        }
    }

    else if(f == "max")
    {
        for(int i = 0; i < vs.size(); i++)
        {
            sort(vd[i].begin(), vd[i].end(), [] (double d1, double d2) -> bool {return d1 > d2;});
            p1.emplace_back(vs[i], vd[i][0]);
        }
    }

    else if(f == "min")
    {
        for(int i = 0; i < vs.size(); i++)
        {
            sort(vd[i].begin(), vd[i].end());
            p1.emplace_back(vs[i], vd[i][0]);
        }
    }

    else
    {
        for(int i = 0; i < vs.size(); i++)
            p1.emplace_back(vs[i], vd[i].size());
    }
}

void pivot2(string c1, string c2, string n, string f)
{
    pivotclear();

    int a1, a2;
    vector<string> vs[2];
    vector<vector<vector<double>>> vd;

    if(c1 == "Genre")
    {
        a1 = 0;
        a2 = 1;
        pf = false;
    }
    else
    {
        a1 = 1;
        a2 = 0;
        pf = true;
    }

    if(n == "Production")
        b = 0;
    else if(n == "Gross")
        b = 1;
    else
        b = 2;

    for(int i = 0; i < db.size(); i++)
    {
        bool f(false);
        int vi[2];
        string mc[2] = {db[i].category[a1], db[i].category[a2]};

        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < vs[j].size(); k++)
            {
                if(mc[j] == vs[j][k])
                {
                    f = true;
                    vi[j] = k;
                    break;
                }
            }

            if(!f)
            {
                vs[j].push_back(mc[j]);
                vi[j] = vs[j].size() - 1;
            }
            
            f = false;
        }

        vector<vector<double>> vvv;
        vector<double> vv;

        if(vi[0] + 1 > vd.size())
            vd.resize(vi[0] + 1);
        
        if(vi[1] + 1 > vd[vi[0]].size())
            vd[vi[0]].resize(vi[1] + 1, vv);

        vd[vi[0]][vi[1]].push_back(db[i].data[b]);
    }

    p2.resize(vs[0].size());

    if(f == "ave")
    {
        for(int i = 0; i < vs[0].size(); i++)
        {
            for(int j = 0; j < vs[1].size(); j++)
            {
                double res = 0;

                if(vd[i][j].empty() || vd[i].size() <= j)
                {
                    p2[i].emplace_back(vs[0][i], vs[1][j], -1);
                }
                else
                {
                    for(int k = 0; k < vd[i][j].size(); k++)
                        res += vd[i][j][k];

                    res /= vd[i][j].size();

                    p2[i].emplace_back(vs[0][i], vs[1][j], res);
                }
            }
        }
    }
    else if(f == "tot")
    {
        for(int i = 0; i < vs[0].size(); i++)
        {
            for(int j = 0; j < vs[1].size(); j++)
            {
                double res = 0;

                if(vd[i][j].empty() || vd[i].size() <= j)
                {        
                    p2[i].emplace_back(vs[0][i], vs[1][j], -1);
                }
                else
                {
                    for(int k = 0; k < vd[i][j].size(); k++)
                        res += vd[i][j][k];

                    p2[i].emplace_back(vs[0][i], vs[1][j], res);
                }
            }
        }
    }
    else if(f == "max")
    {
        for(int i = 0; i < vs[0].size(); i++)
        {
            for(int j = 0; j < vs[1].size(); j++)
            {
                double res = 0;

                if(vd[i][j].empty() || vd[i].size() <= j)
                {
                    p2[i].emplace_back(vs[0][i], vs[1][j], -1);
                }
                else
                {
                    sort(vd[i][j].begin(), vd[i][j].end(), [] (double d1, double d2) -> bool {return d1 > d2; });

                    p2[i].emplace_back(vs[0][i], vs[1][j], vd[i][j][0]);
                }
            }
        }
    }
    else if(f == "min")
    {
        for(int i = 0; i < vs[0].size(); i++)
        {
            for(int j = 0; j < vs[1].size(); j++)
            {
                double res = 0;

                if(vd[i][j].empty() || vd[i].size() <= j)
                {
                    p2[i].emplace_back(vs[0][i], vs[1][j], -1);
                }
                else
                {
                    sort(vd[i][j].begin(), vd[i][j].end());

                    p2[i].emplace_back(vs[0][i], vs[1][j], vd[i][j][0]);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < vs[0].size(); i++)
        {
            for(int j = 0; j < vs[1].size(); j++)
            {
                if(vd[i][j].empty() || vd[i].size() <= j)
                {
                    p2[i].emplace_back(vs[0][i], vs[1][j], -1);
                }
                else
                {
                    p2[i].emplace_back(vs[0][i], vs[1][j], vd[i][j].size());
                }
            }
        }
    }

        /*for(int j = 0; j < vs1.size(); j++)
        {
            if(mc1 == vs1[j])
            {
                f = true;
                 = j;
                break;
            }
        }

        if(!f)
        {
            vs1.push_back(mc1);
            i1 = vs1.size() - 1;
        }

        f = false;

        for(int j = 0; j < vs2.size(); j++)
        {
            if(mc2 == vs2[j])
            {
                f = true;
                i2 = j;
                break;
            }
        }

        if(!f)
        {
            vs2*/
}

void pivottable()
{
    cout.precision(2);
    if(!p1.empty())
    {
        if(!pf)
            cout << "Genre";
        else
            cout << "Source";
        
        if(b == 0)
            cout << "\tProduction" << endl;
        else if(b == 1)
            cout << "\tGross" << endl;
        else if(b == 2)
            cout << "\tRating" << endl;

        for(int i = 0; i < p1.size(); i++)
        {
            cout << p1[i].getc() << "\t" <<fixed<< p1[i].getd() << endl;
        }
    }
    else
    {
        if(!pf)
            cout << "Genre\tSource";
        else
            cout << "Source\tGenre";

        if(b == 0)
            cout << "\tProduction" << endl;
        else if(b == 1)
            cout << "\tGross" << endl;
        else if(b == 2)
            cout << "\tRating" << endl;

        for(int i = 0; i < p2.size(); i++)
        {
            for(int j = 0; j < p2[i].size(); j++)
            {
                if(p2[i][j].getd() != -1)
                    cout << p2[i][j].getc() << "\t" << p2[i][j].getc2() << "\t" <<fixed<< p2[i][j].getd() << endl;
            }
        }
    }
}

void pivotchart()
{
    cout.precision(2);
    if(!p1.empty())
    {
        double max = p1[0].getd();
        double min = max;
        for(int i = 1; i < p1.size(); i++)
        {
            double n = p1[i].getd();
            if(n > max)
                max = n;
            if(n < min)
                min = n;
        }

        double p = (max - min) / 20;
        char c = 'A';

        for(int i = 0; i < p1.size(); i++)
        {
            if(!pf)
                cout << (char)(c + i) << "|";
            else
                cout << i + 1 << "|";
            double n = p1[i].getd();
            if(n == max)
            {
                for(int j = 0; j < 20; j++)
                    cout << "=";
            }
            else
            {
                for(int j = 0; j < 20; j++)
                {
                    if(n > min + p * j)
                        cout << "=";
                    else
                        break;
                }
            }
            cout <<fixed<< n << endl;
        }

        for(int i = 0; i < 25; i++)
            cout << "-";

        cout << endl;
        if(!pf)
            for(int i = 0; i < p1.size(); i++)
                cout << (char)(c + i) << ": " << p1[i].getc() << endl;
        else
            for(int i = 0; i < p1.size(); i++)
                cout << i + 1 << ": " << p1[i].getc() << endl;
    }
    else
    {
        double max = p2[0][0].getd();
        double min = max;

        for(int i = 0; i < p2.size(); i++)
        {
            for(int j = 0; j < p2[i].size(); j++)
            {
                double n = p2[i][j].getd();
                if(n == -1)
                    continue;
                if(n > max)
                    max = n;
                else if(n < min)
                    min = n;
            }
        }

        double p = (max - min) / 20;
        char c = 'A';

        for(int i = 0; i < p2.size(); i++)
        {
            if(i > 0)
                cout << "  |" << endl;
            for(int j = 0; j < p2[i].size(); j++)
            {
                double n = p2[i][j].getd();
                if(n == -1)
                    continue;
                if(!pf)
                    cout << (char)(c + i) << j + 1 << "|";
                else
                    cout << i + 1 << (char)(c + j) << "|";

                if(n == max)
                {
                    for(int k = 0; k < 20; k++)
                        cout << "=";
                }
                else
                {
                    for(int k = 0; k < 20; k++)
                    {
                        if(n > min + p * k)
                            cout << "=";
                        else 
                            break;
                    }
                }
                cout <<fixed<< n << endl;
            }
        }

        for(int i = 0; i < 25; i++)
            cout << "-";
        cout << endl;

        if(!pf)
        {
            for(int i = 0; i < p2.size(); i++)
                cout << (char)(c + i) << ": " << p2[i][0].getc() << endl;

            for(int i = 0; i < p2[0].size(); i++)
                cout << i + 1 << ": " << p2[0][i].getc2() << endl;
        }

        else
        {
            for(int i = 0; i < p2.size(); i++)
                cout << i + 1 << ": " << p2[i][0].getc() << endl;

            for(int i = 0; i < p2[0].size(); i++)
                cout << (char)(c + i) << ": " << p2[0][i].getc2() << endl;
        }
    }
}

void originaltable()
{
    cout << "Name\tGenre\tSource\tProduction\tGross\tRating" << endl;
    for(int i = 0; i < db.size(); i++)
    {
        cout << db[i].name << "\t" << db[i].category[0] << "\t" << db[i].category[1] << "\t"
            << db[i].data[0] << "\t" << db[i].data[1] << "\t" << db[i].data[2] << endl;
    }
}
