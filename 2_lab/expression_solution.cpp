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
    deque<string> output;

    getline(cin, s);

    vector<string> str = split_string(s);

    for (int i = 0; i < str.size(); ++i)
    {
        // cout << (int)str[i] << " " << str[i] << "\n";

        if (str[i] == "+" || str[i] == "-")
        {
            while (!operators.empty() && !(operators.back() == "("))
            {
                output.push_back(operators.back());
                operators.pop_back();
            }

            operators.push_back(str[i]);
        }
        else if ((str[i] == "*" || str[i] == "/"))
        {
            while (!operators.empty() && (operators.back() == "*" || operators.back() == "/"))
            {
                output.push_back(operators.back());
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
                output.push_back(operators.back());
                operators.pop_back();
            }
            operators.pop_back();
        }
        else
        {
            //  number
            output.push_back(str[i]);
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
        output.push_back(operators.back());
        operators.pop_back();
    }

    stack<string> calc;

    for (auto i : output)
    {
        if ((i == "+" || i == "-" || i == "*" || i == "/") && calc.size() > 1)
        {
            int var_1 = stoi(calc.top());
            calc.pop();
            int var_2 = stoi(calc.top());
            calc.pop();

            int res;
            if (i == "+")
            {
                res = var_1 + var_2;
            }
            else if (i == "-")
            {
                res = var_2 - var_1;
            }
            else if (i == "*")
            {
                res = var_1 * var_2;
            }
            else if (i == "/")
            {
                res = var_2 / var_1;
            }

            string s = to_string(res);
            calc.push(s);

            // cout << var_1 << " " << var_2 << " " << res;
        }
        else
        {
            calc.push(i);
        }
    }

    cout << calc.top();
}
