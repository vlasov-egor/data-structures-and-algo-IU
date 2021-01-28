#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string str)
{
    vector<string> tokens;
    string token = "";
    for (auto element : str)
    {
        if (element == ' ')
        {
            tokens.push_back(token);
            token = "";
        }
        else
        {
            token += element;
        }
    }
    if (token != "")
        tokens.push_back(token);
    return tokens;
}

int main(int argc, char const *argv[])
{

    string s;
    deque<string> operators;

    getline(cin, s);

    vector<string> str = split_string(s);

    for (int i = 0; i < str.size(); ++i)
    {
        // cout << (int)str[i] << " " << str[i] << "\n";

        if (str[i] == "+" || str[i] == "-")
        {
            while (!operators.empty() && !(operators.back() == "("))
            {
                cout << (operators.back()) << " ";
                operators.pop_back();
            }

            operators.push_back(str[i]);
        }
        else if ((str[i] == "*" || str[i] == "/"))
        {
            while (!operators.empty() && (operators.back() == "*" || operators.back() == "/"))
            {
                cout << (operators.back()) << " ";
                operators.pop_back();
            }
            operators.push_back(str[i]);
        }
        else if (str[i] == "(")
        {
            operators.push_back(str[i]);
        }
        else if (str[i] == ")")
        {
            while (operators.back() != "(")
            {
                cout << (operators.back()) << " ";
                operators.pop_back();
            }
            operators.pop_back();
        }
        else
        {
            //  number
            cout << str[i] << " ";
        }

        // cout << "output:" << "\n";
        // for (auto j : output)
        // {
        //     cout << j << "\n";
        // }

        // cout << "operators:" << "\n";
        // for (auto j : operators)
        // {
        //     cout << j << "\n";
        // }
    }

    while (!operators.empty())
    {
        cout << (operators.back()) << " ";
        operators.pop_back();
    }

    return 0;
}
