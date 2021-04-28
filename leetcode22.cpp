#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool valid(string str)
{
    int balance = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            return false;
        }
    }

    // std::cout << str << " " << balance << std::endl;
    return balance == 0;
}

// void genernal(string& current, int pos, int size, vector<string>& res)
// {
//     if (pos == size) {
//         std::cout << current << std::endl;
//         return ;
//     }

//     current += "(";
//     genernal(current, pos + 1, size, res);
//     current.pop_back();
//     current += ")";
//     genernal(current, pos + 1, size, res);
//     current.pop_back();
// }

void genernal1(string& current, int size, vector<string>& res)
{
    if (current.size() == size) {
        if (valid(current)) {
            res.emplace_back(current);
        }
        return ;
    }

    current += "(";
    genernal1(current, size, res);
    current.pop_back();
    current += ")";
    genernal1(current, size, res);
    current.pop_back();
}

int main()
{
    string current;
    int pos = 0;
    int size = 3;
    vector<string> res;

    std::cout << "start genernal" << std::endl;
    // genernal(current, pos, size, res);
    genernal1(current, size * 2, res);

    for (auto& it : res) {
        std::cout << it << std::endl;
    }
    system("pause");
}