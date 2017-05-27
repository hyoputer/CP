#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
using namespace std;

class player {
public:
    string name;
    string code;
    string position;
    double winning_rate;
    /*write player class initizlier here*/
    player() {
        name = "";
        code = "";
        position = "";
        winning_rate = -1;
    }
};

class team {
private:
    double teamwork = 0; //DO NOT MODIFY!
public:
    string name;
    string code;
    player *p1 = new player;
    player *p2 = new player;
    player *p3 = new player;
    player *p4 = new player;
    player *p5 = new player;
    player *p6 = new player;
    /*write team class initializer here*/
    team() {
        name = "";
        code = "";
    }
    /*define friend function herer*/
    friend ostream &operator<<(ostream &os, const team &t);
    friend void operator*(team t1, team t2);
    friend void calc_teamwork(team &t);
};

vector<player> player_list;
team t1, t2;

bool check_duplicate(player p) { //DO NOT MODIFY!
    for (auto it2 = player_list.begin(); it2 != player_list.end(); it2++) {
        if (!(*it2).code.compare(p.code)) {
            cout << "duplicate code exists! code should be unique!" << '\n';
            return true;
        }
    }
    return false;
}

ostream &operator<<(ostream &os, const player &p) { //DO NOT MODIFY!
    os << "player code : " << p.code;
    os << '\n';
    os << "player name : " << p.name;
    os << '\n';
    os << "player position : " << p.position;
    os << '\n';
    os << "player winning rate : " << p.winning_rate;
    os << '\n';
    return os;
}

ostream &operator<<(ostream &os, const team &t) { //DO NOT MODIFY!
    os << "team code : " << t.code;
    os << '\n';
    os << "team name : " << t.name;
    os << '\n';
    os << "teamwork : " << t.teamwork;
    os << '\n';
    os << "first team member : " << t.p1->name << " " << t.p1->code;
    os << '\n';
    os << "second team member : " << t.p2->name << " " << t.p2->code;
    os << '\n';
    os << "third team member : " << t.p3->name << " " << t.p3->code;
    os << '\n';
    os << "fourth team member : " << t.p4->name << " " << t.p4->code;
    os << '\n';
    os << "fifth team member : " << t.p5->name << " " << t.p5->code;
    os << '\n';
    os << "sixth team member : " << t.p6->name << " " << t.p6->code;
    os << '\n';
    return os;
}

istream &operator >> (istream &is, player &p) {
    /* write code below */
    string code, name, position;
    double winr;
    do
    {
        cout << "input code : ";
        cin >> code;
        cin.ignore(256, '\n');
        p.code = code;
    }while(check_duplicate(p));

    cout << "input name : ";
    getline(cin, name);
    p.name = name;

    cout << "input position : ";
    getline(cin, position);
    p.position = position;

    while(true)
    {
        cout << "input winning rate : ";
        cin >> winr;
        cin.ignore(256, '\n');
        if(winr < 0 || winr > 100)
            cout << "winning rate should be between 0 and 100" << '\n';
        else
            break;
    }
    p.winning_rate = winr;
    return is;
}

void operator*(team t1, team t2) {
    /*write code below*/
    if(t1.teamwork > t2.teamwork)
        cout << t1.name << " win!" << '\n';
    else if(t1.teamwork < t2.teamwork)
        cout << t2.name << " win!" << '\n';
    else
        cout << "Unpredictable!" << '\n';
}

void calc_teamwork(team &t) { //DO NOT MODIFY!
    t.teamwork = t.p1->winning_rate + t.p2->winning_rate + t.p3->winning_rate + t.p4->winning_rate + t.p5->winning_rate + t.p6->winning_rate;
}

void print_line() { //DO NOT MODIFY!
    cout << "======================================================================" << '\n';
}

void search_position(string position) {
    /*write code below*/
    bool f = false;
    for(const auto &p: player_list)
    {
        if(p.position == position)
        {
            cout << p;
            print_line();
            f = true;
        }
    }
    if(!f)
        cout << "No position exists!" << '\n';

    return;
}

void search_player_name(string name) {
    /*write code below*/
    bool f = false;
    for(const auto &p: player_list)
    {
        if(p.name == name)
        {
            cout << p;
            print_line();
            f = true;
        }
    }
    if(!f)
        cout << "No player exists!" << '\n';

    return;
}

void search_player_code(string code) {
    /*write code below*/
    for(const auto &p: player_list)
    {
        if(p.code == code)
        {
            cout << p;
            print_line();
            return;
        }
    }

    cout << "No player exists!" << '\n';
}

void modify_player(string code) {
    /* write code below */
    for(auto &p: player_list)
    {
        if(p.code == code)
        {
            string name, position;
            double winr;
            cout << "input name : ";
            getline(cin, name);
            p.name = name;

            cout << "input position : ";
            getline(cin, position);
            p.position = position;

            cout << "input winning rate : ";
            cin >> winr;
            cin.ignore(256, '\n');
            p.winning_rate = winr;
            return;
        }
    }

    cout << "No player exists!" << '\n';
}

void print_player() {
    /* write code here */
    for(const auto &p: player_list)
    {
        cout << p;
        print_line();
    }
}

void delete_player(string code) {
    /* write code below */
    auto it = player_list.begin();
    auto e = player_list.end();
    while(it != e)
    {
        if(it -> code == code)
        {
            player_list.erase(it);
            return;
        }
        it++;
    }
    cout << "No such player exists in player list" << '\n';
}

bool check_team_condition() { //DO NOT MODIFY!
    if (player_list.size() > 5) return true;
    else return false;
}

void build_team(team &t) {
    /* write code below */
    string code, name;
    bool f = false;

    cout << "Input team code : ";
    cin >> code;
    cin.ignore(256, '\n');
    t.code = code;

    cout << "Input team name : ";
    getline(cin, name);
    t.name = name;

    while(true)
    {
        cout << "Input first team member's code : ";
        cin >> code;
        cin.ignore(256, '\n');
        for(auto &p: player_list)
        {
            if(p.code == code)
            {
                t.p1 = &p;
                f = true;
                break;
            }
        }
        if(!f)
            cout << "No player exists!" << '\n';
        else
            break;
    }
    f = false;

    while(true)
    {
        cout << "Input second team member's code : ";
        cin >> code;
        cin.ignore(256, '\n');
        for(auto &p: player_list)
        {
            if(p.code == code)
            {
                t.p2 = &p;
                f = true;
                break;
            }
        }
        if(!f)
            cout << "No player exists!" << '\n';
        else
            break;
    }
    f = false;

    while(true)
    {
        cout << "Input third team member's code : ";
        cin >> code;
        cin.ignore(256, '\n');
        for(auto &p: player_list)
        {
            if(p.code == code)
            {
                t.p3 = &p;
                f = true;
                break;
            }
        }
        if(!f)
            cout << "No player exists!" << '\n';
        else
            break;
    }
    f = false;

    while(true)
    {
        cout << "Input fourth team member's code : ";
        cin >> code;
        cin.ignore(256, '\n');
        for(auto &p: player_list)
        {
            if(p.code == code)
            {
                t.p4 = &p;
                f = true;
                break;
            }
        }
        if(!f)
            cout << "No player exists!" << '\n';
        else
            break;
    }
    f = false;

    while(true)
    {
        cout << "Input fifth team member's code : ";
        cin >> code;
        cin.ignore(256, '\n');
        for(auto &p: player_list)
        {
            if(p.code == code)
            {
                t.p5 = &p;
                f = true;
                break;
            }
        }
        if(!f)
            cout << "No player exists!" << '\n';
        else
            break;
    }
    f = false;

    while(true)
    {
        cout << "Input sixth team member's code : ";
        cin >> code;
        cin.ignore(256, '\n');
        for(auto &p: player_list)
        {
            if(p.code == code)
            {
                t.p6 = &p;
                f = true;
                break;
            }
        }
        if(!f)
            cout << "No player exists!" << '\n';
        else
            break;
    }
    calc_teamwork(t);
}

void build_best_team() {
    /* write code here */
    t1.code = "001";
    t1.name = "best team";
    stable_sort(player_list.begin(), player_list.end(), [](const player &p1, const player &p2) -> bool{return p1.winning_rate > p2.winning_rate;} );
    t1.p1 = &player_list[0];
    t1.p2 = &player_list[1];
    t1.p3 = &player_list[2];
    t1.p4 = &player_list[3];
    t1.p5 = &player_list[4];
    t1.p6 = &player_list[5];
    calc_teamwork(t1);
}

void print_logo() { // DO NOT MODIFY!
    print_line();
    cout << ",--.   ,--.        ,--.            ,--.   ,--.                        " << '\n';
    cout << "|   `.'   | ,--,--.`--',--,--,     |   `.'   | ,---. ,--,--, ,--.,--. " << '\n';
    cout << "|  |'.'|  |' ,-.  |,--.|      |    |  |'.'|  || .-. :|      ||  ||  | " << '\n';
    cout << "|  |   |  |` '-'  ||  ||  ||  |    |  |   |  |`   --.|  ||  |'  ''  ' " << '\n';
    cout << "`--'   `--' `--`--'`--'`--''--'    `--'   `--' `----'`--''--' `----'  " << '\n';
    print_line();
}

void show_help() { //DO NOT MODIFY!
    cout << "Command list" << '\n';
    cout << "help - print commands" << '\n';
    cout << "new player - Insert new player" << '\n';
    cout << "search player - Search player from list" << '\n';
    cout << "delete player - Remove player from player list" << '\n';
    cout << "modify player - Modify player from player list" << '\n';
    cout << "print player - Print all player" << '\n';
    cout << "build team - Build a new team" << '\n';
    cout << "build best team - Build a best team" << '\n';
    cout << "print team - Print all team" << '\n';
    cout << "simulate - Simulate teams" << '\n';
    cout << "exit - To terminate program" << '\n';
    print_line();
}

int check_command(string command) { //DO NOT MODIFY!
    if (!command.compare("new player")) {
        player p;
        cin >> p;
        player_list.emplace_back(p);
        print_line();
    }
    else if (!command.compare("print player")) {
        if (player_list.empty()) {
            cout << "player list is empty" << '\n';
            print_line();
        }
        else print_player();
    }
    else if (!command.compare("search player")) {
        int select = -1;
        string keyword;
        if (player_list.empty()) {
            cout << "player list is empty" << '\n';
            print_line();
        }
        else {
            do {
                cout << "Select keyword to search" << '\n';
                cout << "0 : Search with player code" << '\n';
                cout << "1 : Search with player name" << '\n';
                cout << "2 : Search with player position" << '\n';
                print_line();
                cin >> select;
                cin.ignore(256, '\n');
                switch (select) {
                case 0:
                    cout << "Input player code : ";
                    cin >> keyword;
                    cin.ignore(256, '\n');
                    print_line();
                    search_player_code(keyword);
                    break;
                case 1:
                    cout << "Input player name : ";
                    getline(cin, keyword);
                    print_line();
                    search_player_name(keyword);
                    break;
                case 2:
                    cout << "Input position : ";
                    getline(cin, keyword);
                    print_line();
                    search_position(keyword);
                    break;
                default:
                    cout << "Invalid keyword!" << '\n';
                    print_line();
                    break;
                }
            } while (select < 0 || select>2);
        }
    }
    else if (!command.compare("delete player")) {
        string name;
        if (player_list.empty()) {
            cout << "player list is empty" << '\n';
            print_line();
        }
        else {
            cout << "Input player code : ";
            cin >> name;
            cin.ignore(256, '\n');
            delete_player(name);
            print_line();
        }
    }

    else if (!command.compare("build team")) {
        int cond;
        if (check_team_condition()) {
            cout << "select team to build" << '\n';
            cout << "0 : Team 1" << '\n';
            cout << "1 : Team 2" << '\n';
            cin >> cond;
            cin.ignore(256, '\n');
            if (cond == 0) build_team(t1);
            else if (cond == 1) build_team(t2);
            print_line();
        }
        else cout << "Not enough players to a build team" << '\n';
    }
    else if (!command.compare("build best team")) {
        if (check_team_condition()) build_best_team();
        else cout << "Not enough players to build a team" << '\n';
        print_line();
    }
    else if (!command.compare("simulate")) {
        if (!t1.name.compare("")) cout << "Team 1 is empty!" << '\n';
        else if (!t2.name.compare("")) cout << "Team 2 is empty!" << '\n';
        else t1*t2;
        print_line();
    }
    else if (!command.compare("print team")) {
        if (!t1.name.compare("")) cout << "Team 1 is empty!" << '\n';
        else cout << t1;
        print_line();
        if (!t2.name.compare("")) cout << "Team 2 is empty!" << '\n';
        else cout << t2;
        print_line();
    }
    else if (!command.compare("modify player")) {
        string code;
        if (player_list.empty()) {
            cout << "player list is empty" << '\n';
            print_line();
        }
        else {
            cout << "Input player code to modify : ";
            cin >> code;
            cin.ignore(256, '\n');
            modify_player(code);
            print_line();
        }
    }
    else if (!command.compare("help")) {
        print_logo();
        show_help();
    }
    else if (!command.compare("exit")) return 0;
    else {
        cout << command << '\n';
        cout << "Invalid command!" << '\n';
    }
    return 1;
}

int main() {
    print_logo();
    show_help();
    string command;
    do {
        getline(cin, command);
    } while (check_command(command));

    return 0;
}
