#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    vector<vector<string>> db;
    vector<string> temp;
    string command;
    string genre;
    string movie;
    
    while(true)
    {
        cin >> command;
        if(command == "add_genre")
        {
            cin >> genre;
            temp.clear();
            temp.push_back(genre);
            db.push_back(temp);
        }
        else if(command == "add_movie")
        {
            cin >> genre >> movie;
            for(auto &v: db)
            {
                if(v[0] == genre)
                {
                    v.push_back(movie);
                    break;
                }   
            }
        }
        else if(command == "remove_genre")
        {
            cin >> genre;
            int t;
            for(int i = 0; i < db.size(); i++)
            {
                if(db[i][0] == genre)
                {
                    t = i;
                    break;
                }
            }
            db.erase(db.begin()+t);
        }
        else if(command == "remove_movie")
        {
            cin >> genre >> movie;
            int t;
            for(auto &v: db)
            {
                if(v[0] == genre)
                {
                    for(int i = 0; i < v.size(); i++)
                    {
                        if(v[i] == movie)
                        {
                            t = i;
                            break;
                        }   
                    }
                    v.erase(v.begin()+t);
                    break;
                }
            }
        }
        else if(command == "print_genre")
        {
            cin >> genre;
            for(auto v: db)
            {
                if(v[0] == genre)
                {
                    cout << "--" << genre << "--" << endl;
                    for(int i = 1; i < v.size(); i++)
                        cout << v[i] << endl;
                }
            }
        }
        else if(command == "print_all")
        {
            for(auto v: db)
            {
                cout << "--" << v[0] << "--" << endl;
                for(int i = 1; i < v.size(); i++)
                    cout << v[i] << endl;
            }
        }
        else if(command == "exit")
            return 0;
    }

    return -1;
}

