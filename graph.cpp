#include <iostream>
#include <stack>
#include <queue>


class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(): val(0), left(nullptr), right(nullptr){}
    Node(int _val): val(_val), left(nullptr), right(nullptr){}
    Node(int _val, Node* _left, Node* _right): val(_val), left(_left), right(_right){}
};

// 总结：
// 1. DFS 一般用来解决连通性问题
// 2. BFS 一般用来解决最短路径问题
// 注意：dfs / bfs 注意为图的时候(非二叉树)，可能需要做是否遍历过标志检查，防止重复遍历
void dfs(Node* node)
{
    if (nullptr == node) {
        return ;
    }

    // 总结：
    // 1. 用栈遍历；
    // 2. 先右后左；
    std::stack<Node*> stack;
    stack.emplace(node);
    std::cout << "=====dfs begin:" << std::endl;
    while (!stack.empty())
    {
        Node* node1 = stack.top();
        stack.pop();

        std::cout << node1->val << " ";
        if (nullptr != node1->right) {
            stack.emplace(node1->right);
        }

        if (nullptr != node1->left) {
            stack.emplace(node1->left);
        }
    }
    std::cout << "=====dfs end:" << std::endl;
}

void bfs(Node* node)
{
    if (nullptr == node) {
        return ;
    }

    // 总结：
    // 1. 用队列遍历
    // 2. 先左后右
    std::queue<Node*> queue;
    queue.emplace(node);
    std::cout << "=====bfs begin:" << std::endl;
    while (!queue.empty())
    {
        Node* node1 = queue.front();
        queue.pop();

        std::cout << node1->val << " ";
        if (nullptr != node1->left) {
            queue.emplace(node1->left);
        }

        if (nullptr != node1->right) {
            queue.emplace(node1->right);
        }
    }
    std::cout << "=====bfs end:" << std::endl;
}

void preTraversalBTree(Node* node)
{
    if (nullptr == node) {
        return ;
    }

    std::cout << node->val << std::endl;
    preTraversalBTree(node->left);
    preTraversalBTree(node->right);
}

void createBTree(Node** tree)
{
    *tree = new Node(1);
    Node* root = *tree;

    Node* node1 = new Node(2);
    Node* node2 = new Node(5);
    Node* node3 = new Node(6);
    Node* node4 = new Node(4);

    root->left = node1;
    root->right = node4;

    node1->left = node2;
    node1->right = node3;
}

int main()
{
    Node* root = nullptr;
    createBTree(&root);

    preTraversalBTree(root);
    dfs(root);
    bfs(root);
    return 0;
}