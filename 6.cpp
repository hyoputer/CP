#include<iostream>
#include<array>
#include<algorithm>
#include<vector>
using namespace std;

void get_dic();
void decipher();
array<string, 100> dic;
char table1[26];
char table2[26];
int check1[26] = {};
int check2[26] = {};
int dicsize;

struct cip
{
    cip() = default;
    cip(string _s): s(_s) {}
    string s;
    int id;
};

int main()
{
    get_dic();

    decipher();

    return 0;
}

void get_dic()
{
    cin >> dicsize;

    for(int i = 0; i < dicsize; i++)
    {
        string s;
        cin >> s;
        cin.ignore(256, '\n');
        dic[i] = s;
    }

    stable_sort(dic.begin(), dic.begin() + dicsize, [] (string s1, string s2) -> bool { return s1.size() < s2.size(); });
}

void decipher()
{
    string input;
    cip words[100];

    getline(cin, input);
    
    int b = 0;
    int count = 0;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == ' ')
        {
            words[count++] = cip(input.substr(b, i - b));
            b = i + 1;
        }
    }

    words[count++] = cip(input.substr(b));

    for(int i = 0; i < count; i++)
    {
        bool f(false);
        for(int j = 0; j < dicsize; j++)
        {
            if(dic[j].size() == words[i].s.size())
            {
                words[i].id = j;
                f = true;
                break;
            }
        }

        if(!f)
        {
            cout << "mission failure..." << endl;
            return;
        }

        do
        {
            f = false;

            //cout << words[i].s << endl << dic[words[i].id] << endl;

            for(int j = 0; j < words[i].s.size(); j++)
            {
                char text((words[i].s)[j]);
                char target(dic[words[i].id][j]);

                //cout << text << endl << target << endl;

                if((check1[text - 'a'] == 0 || table1[text - 'a'] == target) && (check2[target - 'a'] == 0 || table2[target - 'a'] == text))
                {
                    table1[text - 'a'] = target;
                    check1[text - 'a']++;
                    table2[target - 'a'] = text;
                    check2[target - 'a']++;
                }
                else
                {
                    f = true;
                    for(int k = 0; k < j; k++)
                    {
                        int sindex1((words[i].s)[k] - 'a');
                        int sindex2(dic[words[i].id][k] - 'a');
                    
                         /*   for(int l = 0; l < skip1.size(); l++)
                            {
                                if(sindex1 == skip1[l])
                                {
                                    skipf1 = true;
                                    break;
                                }
                            }

                            for(int l = 0; l < skip2.size(); l++)
                            {
                                if(sindex2 == skip2[l])
                                {
                                    skipf2 = true;
                                    break;
                                }
                            }

                            if(!skipf1)
                                check1[sindex1] = false;

                            if(!skipf2)
                                check2[sindex2] = false;*/

                        if(check1[sindex1] > 0)
                            check1[sindex1]--;

                        if(check2[sindex2] > 0)
                            check2[sindex2]--;
                    }
                    /*for(int a = 0; a < 26; a++)
                    {
                        if(check1[a] == 0)
                            cout << ' ';
                        else
                            cout << table1[a];
                    }
                    cout << endl;
                    for(int a = 0; a < 26; a++)
                        cout << (char)('a' + a);
                    cout << endl;

                    for(int b = 0; b < 26; b++)
                    {
                        if(check2[b] == 0)
                            cout << ' ';
                        else
                            cout << table2[b];
                    }
                    cout << endl;
                    for(int a = 0; a < 26; a++)
                        cout << (char)('a' + a);
                    cout << endl;*/

                    break;
                }
                
            }

            if(f)
            {
                bool sf(false);
                for(int j = i; j >= 0 ; j--)
                {
                    if(dic[(words[j].id) + 1].size() == (words[j].s).size())
                    {
                        i = j;
                        (words[j].id)++;
                        sf = true;
                        break;
                    }
                    else
                    {
                        for(int k = 0; k < words[j - 1].s.size(); k++)
                        {
                            int sindex1((words[j - 1].s)[k] - 'a');
                            int sindex2(dic[words[j - 1].id][k] - 'a');
                    
                            if(check1[sindex1] > 0)
                                check1[sindex1]--;

                            if(check2[sindex2] > 0)
                                check2[sindex2]--;
                        }
                    }
                }
                if(!sf)
                {
                    cout << "mission failure..." << endl;
                    return;
                }
            }
        }while(f);
    }

    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == ' ')
            cout << ' ';
        else
        {
            cout << table1[input[i] - 'a'];
        }
    }

    cout << endl;
}
