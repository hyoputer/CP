#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Team
{
    friend bool comp(const Team &t1, const Team &t2);
    friend bool draw(const Team &t1, const Team &t2);
public:
    Team(string _name): name(_name) {}
    inline string check();
    void res(int wl, int s, int ls);
    inline int getrank();
    inline void setrank(int r);
    inline void print();
private:
    int rank;
    string name;
    int games = 0;
    int point = 0;
    int win = 0;
    int lose = 0;
    int draw = 0;
    int score = 0;
    int lscore = 0;
};

bool comp(const Team &t1, const Team &t2)
{
    if(t1.point > t2.point)
        return true;
    else if(t1.point < t2.point)
        return false;
    else
    {
        if(t1.win > t2.win)
            return true;
        else if(t1.win < t2.win)
            return false;
        else
        {
            if(t1.score - t1.lscore > t2.score - t2.lscore)
                return true;
            else if(t1.score - t1.lscore < t2.score - t2.lscore)
                return false;
            else
            {
                if(t1.score > t2.score)
                    return true;
                else if(t1.score < t2.score)
                    return false;
                else
                {
                    if(t1.games < t2.games)
                        return true;
                    else if(t1.games > t2.games)
                        return false;
                    else
                    {
                        if(t1.name < t2.name)
                            return true;
                        else
                            return false;
                    }
                }
            }
        }
    }
}

vector<Team> standing;

void game(string team1, int score1, string team2, int score2);

int main()
{
    while(true)
    {
        string t1, t2;
        int s1, s2;
        cin >> t1;

        if(t1 == "end")
            break;

        cin >> s1 >> s2 >> t2;

        game(t1, s1, t2, s2);
    }

    sort(standing.begin(), standing.end(), comp);

    for(int i = 0; i < standing.size(); i++)
    {
        if(i > 0)
        {
            if(draw(standing[i - 1], standing[i]))
                standing[i].setrank(standing[i - 1].getrank());
            else
                standing[i].setrank(standing[i - 1].getrank() + 1);
        }
        else
            standing[0].setrank(1);
        

        standing[i].print();

        if(i < standing.size() - 1)
            cout << endl;
    }

    return 0;
}

string Team::check()
{ return name; }

void Team::res(int wl, int s, int ls)
{
    games++;
    if(wl == 1)
    {
        win++;
        point += 3;
    }
    else if(wl == 0)
    {
        draw++;
        point++;
    }
    else
        lose++;

    score += s;
    lscore += ls;
} 

int Team::getrank()
{ return rank; }

void Team::setrank(int r)
{ rank = r; }

void Team::print()
{ cout << rank << ") " << name << " " << games << "G " << point << "P " << win << "-" << draw << "-" << lose << " " << score << "/" << lscore << "/" << score - lscore; }

void game(string team1, int score1, string team2, int score2)
{
    Team t1(team1);
    Team t2(team2);
    bool f1(false), f2(false);
    int i1, i2;
    for(int i = 0; i < standing.size(); i++)
    {
        string check = standing[i].check();
        if(check == team1)
        {
            i1 = i;
            f1 = true;
        }
        else if(check == team2)
        {
            i2 = i;
            f2 = true;
        }

        if(f1 && f2)
            break;
    }

    if(!f1)
    {
        i1 = standing.size();
        standing.push_back(t1);
    }
    
    if(!f2)
    {
        i2 = standing.size();
        standing.push_back(t2);
    }

    int wl;
    if(score1 > score2)
        wl = 1;
    else if(score1 == score2)
        wl = 0;
    else
        wl = -1;

    standing[i1].res(wl, score1, score2);
    standing[i2].res((-1) * wl, score2, score1);
}


bool draw(const Team &t1, const Team &t2)
{
    if(t1.point == t2.point && t1.win == t2.win && t1.score == t2.score && t1.lscore == t2.lscore
            && t1.games == t2.games)
        return true;
    return false;
}
