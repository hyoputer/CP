#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<regex>
#include<math.h>
#include<algorithm>
#include<ctype.h>
using namespace std;

int main()
{
    int a = 0, num = 0;
    stack<string> s;
    bool f = false;

    string input;
    getline(cin, input);

  /* for(int i = 0; i < input.size(); i++)
    {
        if(isspace(input[i]))
        {
            space.push_back(i);
        }
    }

    for(int i = 0; i < space.size(); i++)
        input.erase(input.begin() + space[i] - i);*/

    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end() );

  /*  cin >> a;
    q.push(a);

    while(cin >> op)
    {
        cout << op << endl;
        while(!s.empty())
        {
            if(op == '*' && s.top() == '+')
                break;
            q.push(s.top());
            s.pop();
        }
        s.push(op);
        cin >> a;
        q.push(a);
    }*/

    int b = 0;

    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == '+' || input[i] == '*')
        {
          /*  a = 0;
            num = 0;
            for(int j = i - 1; j >= b; j--)
            {
                a += ((input[j] - '0') * pow(10, num));
                num++;
            }
            q.push(a);*/
            if(b < i)
            {
                s.push(input.substr(b, i - b));
                b = i + 1;
            }

            if(input[i] == '*')
            {
                for(i = b;i < input.size(); i++)
                {
                    if(input[i] == '+' || input[i] == '*')
                    {
                        s.push(input.substr(b, i - b));
                        b = i + 1;
                        break;
                    }
                }
                if(i == input.size())
                {
                    s.push(input.substr(b));
                    f = true;
                }

                int num1 = stoi(s.top());
                s.pop();
                int num2 = stoi(s.top());
                s.pop();
                s.push(to_string(num1 * num2));
                if(i == input.size())
                    break;
                i--;
                continue;
            }

            s.push(string(1,'+'));
        }
    }

    if(f == false)
        s.push(input.substr(b));

    while(s.size() != 1)
    {
        int num1 = stoi(s.top());
        s.pop();
        s.pop();
        int num2 = stoi(s.top());
        s.pop();
        s.push(to_string(num1 + num2));
        
    }


  /*  a = 0;
    num = 0;

    for(int i = input.size() - 1; i >= b; i--)
    {
        a += ((input[i] - '0') * pow(10, num));
        num++;
    }

    q.push(a);

    q.push(stoi(input.substr(b)));

    while(!s.empty())
    {
        q.push(s.top());
        s.pop();
    }

    while(!q.empty())
    {
        if(q.front() == '+' || q.front() == '*')
        {
            int num1 = s.top();
            s.pop();
            int num2 = s.top();
            s.pop();
            if(q.front() == '+')
                s.push(num1 + num2);
            else
                s.push(num1 * num2);
        }
        else
        {
            s.push(q.front());
        }
        q.pop();

    }*/

    cout << s.top() << endl;

    return 0;
}
