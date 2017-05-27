#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

typedef struct asdf
{
    string id;
    map<string, string> m;
} Data;

class tag
{
public:
    tag() = default;
    tag(string _n): name(_n) {sel = true;}
    tag(string _n, tag* tptr): name(_n), par(tptr) { sel = true; }
    string name;
    map<string, string> at;
    vector<tag*> child;
    bool sel = false;
    string seln;
    Data bind;
    tag* par;

    tag* selfind();
};

/*bool operator==(const tag &t1, const tag &t2) {
    if(t1.name == t2.name && t1.at == t2.at && t1.child == t2.child)
        return true;
    else
        return false;
}*/
    
tag root;

tag* tag::selfind()
{
    for(auto& tag: child)
    {
        if(tag->sel == true)
            return tag;
    }

    return &root;
}

ostream &operator<<(ostream &os, const tag &t) {
    os << "<" << t.name;
    for(const auto& mv: t.at)
        os << " " << mv.first << "=\"" << mv.second << "\"";
    os << ">" << endl;
    for(const auto& ct: t.child)
        os << *ct;
    os << "</" << t.name << ">" << endl;

    return os;
}

vector<Data> getcsv(char *);
//tag* find(tag*, const string&);
tag* append(tag*, string&);
tag* select(tag*, string&);
tag* remove(tag*);
tag* endt(tag*);
void enter(tag*, char*);
void update(tag*, char*);
void exit(tag*, char*);
void cattr(tag*);
void tattr(tag*);
void dattr(tag*);
inline void print(const string&);

int main(int argc, char *argv[])
{
    root.name = "html";
    root.sel = true;
    root.par = &root;
    
    tag* stag = &root;
    
    while(true)
    {
        string command;
        cin >> command;
       
        if(cin.fail())
            break;
        if(command == "append" || command == "select" || command == "selectAll" || command == "print")
        {
            string n;
            cin >> n;
            if(command == "append")
                stag = append(stag, n);
            else if(command == "select" || command == "selectAll")
                stag = select(stag, n);
            else if(command == "print")
                print(n);
        }
        else if(command == "remove")
            stag = remove(stag);
        else if(command == "end")
        {
            if(stag->selfind()->name == "html" && stag->seln == "")
                break;
            stag = endt(stag);
        }
        else if(command == "enter" || command == "update" || command == "exit")
        {
            int i;
            cin >> i;
            if(command == "enter")
                enter(stag, argv[i]);
            else if(command == "update")
                update(stag, argv[i]);
            else if(command == "exit")
                exit(stag, argv[i]);
        }
        else if(command == "cattr")
            cattr(stag);
        else if(command == "tattr")
            tattr(stag);
        else if(command == "dattr")
            dattr(stag);

        //cout << *stag << endl;
    }

    return 0;
}

tag* append(tag* t, string &n)
{
    tag* ctag(t->selfind());
    tag* newtag = new tag(n, ctag);
    ctag->child.push_back(newtag);
    t->seln = "";
    return ctag;
}

tag* select(tag* t, string &n)
{
    tag* ctag(t->selfind());
    for(auto& ct: ctag->child)
    {
        if(ct->name == n)
            ct->sel = true;
    }
    ctag->seln = n;
    return ctag;
}

tag* remove(tag* t)
{
    for(auto it = t->child.begin(); it != t->child.end();)
    {
        if((*it)->sel == true)
            it = t->child.erase(it);
        else
            it++;
    }
    t->seln = "";

   return t->par;
}

tag* endt(tag* t)
{
    for(auto& tptr: t->child)
        tptr->sel = false;

    t->seln = "";
    return t->par;
}

void enter(tag* t, char* csv)
{
    vector<Data> data(getcsv(csv));

    /*for(auto &ct: t->child)
        ct->sel = false;*/

    tag* par = t->par;

    int cnt(0);

    for(int j = 1; j < data.size(); j++)
    {
        bool f(false);
        for(auto &ct: t->child)
        {
            if(ct->sel == true && data[j].id == ct->bind.id)
            {
                f = true;
                break;
            }
        }
        if(!f)
        {
            if(par->selfind()->name == "html" && par->seln != "")
            {
                tag* newtag = new tag(t->seln);
                par->child.push_back(newtag);
            }
            else
                append(par, t->seln);

            t->child.back()->bind.id = data[j].id;
            t->child.back()->bind.m = data[j].m;
            cnt++;
        }
        //cout << ((t->child).back())->bind["value"] << endl;
    }

    //cout << data[1].m["radius"] << endl;

    for(int i = 0; i < (t->child).size() - cnt; i++)
        t->child[i]->sel = false;
}

void update(tag* t, char* csv)
{
    vector<Data> data(getcsv(csv));

    for(auto& ct: t->child)
    {
        bool f(false);
        if(ct->sel == true)
        {
            for(int i = 1; i < data.size(); i++)
            {
                if(data[i].id == ct->bind.id)
                {
                    f = true;
                    //cout << (ct->bind)[(*((*it).begin())).first] << endl;
                    ct->bind = data[i];
                    break;
                }
            }
            if(!f)
                ct->sel = false;
        }
    }
}

void exit(tag* t, char* csv)
{
    vector<Data> data(getcsv(csv));

    for(auto& ct: t->child)
    {
        bool f(false);
        if(ct->sel == true)
        {
            for(int i = 1; i < data.size(); i++)
            {
                if(data[i].id == ct->bind.id)
                {
                    f = true;
                    break;
                }
            }
            if(f)
                ct->sel = false;
        }
    }
}
    /*vector<map<string, string>> data(getcsv(csv));

    for(auto& ct: t->child)
    {
        bool f(false);
        if(ct->sel == true)
        {
            for(auto it = data.begin() + 1; it != data.end(); it++)
            {
                if((*((*it).begin())).second == (ct->bind)[(*((*it).begin())).first])
                {
                    f = true;
                    break;
                }
            }
            if(f)
                ct->sel = false;
        }
    }
}*/

void cattr(tag* t)
{
    string n, v;
    cin >> n >> v;
    
    if(t->selfind()->name == "html")
        t->at[n] = v;
    else
    {
        for(auto& tptr: t->child)
        {
            if(tptr->sel == true)
                tptr->at[n] = v;
        }
    }
}

void tattr(tag* t)
{
    double x, y;
    cin >> x >> y;

    if(t->selfind()->name == "html")
        t->at["transform"] = "translate(0,0)";
    else
    {
        int cnt(0);
        for(auto& tptr: t->child)
        {
            if(tptr->sel == true)
            {
                tptr->at["transform"] = "translate(" + to_string(cnt * x) +","+ to_string(cnt * y) +")";
                cnt++;
            }
        }
    }
}

void dattr(tag* t)
{
    char *ptr;
    string input;
    getline(cin, input);
    char cinput[input.length()];
    strcpy(cinput, input.c_str());

    ptr = strtok(cinput, " ");
    string attr(ptr);
    
    ptr = strtok(NULL, " ");
    string field(ptr);

    string mul, add;
    int cnt(0);
    while(ptr = strtok(NULL, " "))
    {
        if(ptr != NULL)
        {
            if(cnt == 0)
                mul = ptr;
            else
                add = ptr;
        }
        cnt++;
    }

    for(auto& ct: t->child)
    {
        if(ct->sel == true)
        {
            if(mul == "")
                ct->at[attr] = (ct->bind).m[field];
            else if(add == "")
                ct->at[attr] = to_string(stod((ct->bind).m[field]) * stod(mul));
            else
                ct->at[attr] = to_string(stod((ct->bind).m[field]) * stod(mul) + stod(add));
        }
    }
}

inline void print(const string& n){ ofstream ofs(n, ofstream::out); ofs << root;  ofs.close(); }

vector<Data> getcsv(char* csv)
{
    ifstream ifs(csv);
    int cnt(0);
    vector<Data> table;
    vector<string> field;
    while(!ifs.eof())
    {
        string s;
        getline(ifs, s);
        if(cnt > 0)
            table.emplace_back();
        char cstr[s.length()];
        strcpy(cstr, s.c_str());

        int i(0);
        string id;
        char *ptr = strtok(cstr, ",");

        do
        {
            if(ptr != NULL)
            {
                if(cnt == 0)
                {
                    field.emplace_back(ptr);
                    //cout << ptr << endl;
                }
                else
                {
                    if(i == 0)
                        table[cnt - 1].id = string(ptr); 
                    table[cnt - 1].m[field[i]] =  string(ptr);
                }
            }
            i++;
        }while(ptr = strtok(NULL, ","));

        cnt++;
    }

    //cout << (field[field.size() - 1] == "radius") << endl;

    table.pop_back();
    ifs.close();
    if(table[0].id == "string")
        sort(table.begin() + 1, table.end(), [](Data v1, Data v2) -> bool{return v1.id < v2.id;});
    else
        sort(table.begin() + 1, table.end(), [](Data v1, Data v2) -> bool{return stod(v1.id) < stod(v2.id);});
    return table;
}

/*tag* find(tag* t, const string& n)
{
    if(n == "html")
        return &root;
    bool f(false);
    for(auto& ct: t->child)
    {
        if(ct->name == n)
        {
            return t;
        }
        else
        {
            tag* tptr = find(ct, n);
            if(tptr != nullptr)
                return tptr;
        }
    }
        return nullptr;
}*/
