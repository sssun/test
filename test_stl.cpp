#include <iostream>
#include <algorithm>
#include <forward_list>
#include <deque>
#include <stack>

void test_forward_list()
{
    std::forward_list<int> flist = {1, 2, 3};
    int key = 3;
    auto it = std::find(flist.begin(), flist.end(), key);
    if (it != flist.end()) {
        std::cout << "find key:" << key << " " << *it << std::endl;
    } else {
        std::cout << "can not find key:" << key << std::endl;
    }

    key = 4;
    auto it1 = std::find(flist.begin(), flist.end(), key);
    if (it1 != flist.end()) {
        std::cout << "find key:" << key << " " << *it1 << std::endl;
    } else {
        std::cout << "can not find key:" << key << std::endl;
    }
}

void test_deque()
{
    std::deque<int> dei = {2, 3, 1};
    std::cout << "before sort deque" << std::endl;
    for (auto& it : dei)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    std::sort(dei.begin(), dei.end());
    std::cout << "after sort deque" << std::endl;
    for (auto& it : dei)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

}

void test_stack()
{
    // std::stack<int> tmp = {1, 2, 3};
    std::stack<int> tmp;
    tmp.emplace(1);
    tmp.emplace(3);
    tmp.emplace(2);
    
    // 和priority_queue一样，没有begin和end迭代器。不能使用find
    // auto it = std::find(tmp.begin(), tmp.end(), 3);
    // if (it != tmp.end()) {
    //     std::cout << "find key:" << key << " " << *it << std::endl;
    // } else {
    //     std::cout << "can not find key:" << key << std::endl;
    // }
}

int main()
{
    test_forward_list();
    test_deque();

    return 0;
}