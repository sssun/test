#include <iostream>
#include <vector>

typedef struct _BSTreeNode {
    int     data;
    struct _BSTreeNode*     leftChild;
    struct _BSTreeNode*     rightChild;
} BSTreeNode;

BSTreeNode* createBSTreeNode(int key)
{
    BSTreeNode* node = new BSTreeNode();
    node->data = key;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
}

bool insertBSTree(BSTreeNode** tree, int key)
{
    BSTreeNode* cur = nullptr;
    BSTreeNode* parent = nullptr;
    if (nullptr == *tree) {
        *tree = createBSTreeNode(key);
        return true;
    }

    cur = *tree;
    while (nullptr != cur)
    {
        parent = cur;
        if (key > cur->data) {
            cur = cur->rightChild;
        } else if (key < cur->data) {
            cur = cur->leftChild;
        } else {
            return false;
        }
    }

    if (key > parent->data) {
        parent->rightChild = createBSTreeNode(key);
    } else if (key < parent->data) {
        parent->leftChild = createBSTreeNode(key);
    }

    return true;
}

BSTreeNode* createBSTree(std::vector<int>& array)
{
    BSTreeNode* tree = nullptr;
    for (auto ele : array)
    {
        if (!insertBSTree(&tree, ele)) {
            std::cout << "insert bst node " << ele << " failed." << std::endl;
        }
    }

    return tree;
}

bool searchBSTree(BSTreeNode* tree, int key)
{
    bool bExist = false;
    while (tree)
    {
        if (key > tree->data) {
            tree = tree->rightChild;
        } else if (key < tree->data) {
            tree = tree->leftChild;
        } else {
            bExist = true;
            break;
        }
    }

    return bExist;
}

BSTreeNode* getCarryOnNode(BSTreeNode* tree)
{
    if (nullptr == tree) {
        return nullptr;
    }

    BSTreeNode* parent = tree;
    BSTreeNode* carryOnNode = tree->rightChild;
    if (nullptr != carryOnNode->leftChild) {
        while (nullptr != carryOnNode->leftChild)
        {
            parent = carryOnNode;
            carryOnNode = carryOnNode->leftChild;
        }

        parent->leftChild = carryOnNode->rightChild;
    }

    return carryOnNode;
}

// 该删除函数有问题
bool deleteBSTreeNode(BSTreeNode** tree, int key)
{
    // 思路：
    // 1. 删除节点没有子节点
    // 2. 删除节点有1个子节点
    // 3. 删除节点有2个子节点
    //      3.1 左子树的最大节点 和 右子树的最小节点 来替换被删除的节点(按照中序遍历寻找后继节点)；
    //      3.2 注意：右子树的最小节点可能为非叶子节点，置换时需要把后继节点的子树链接到父节点的左子树上；

    BSTreeNode* cur = *tree;
    BSTreeNode* parent = cur;
    bool isLeft = true;
    while (nullptr != cur && cur->data != key)
    {
        parent = cur;
        if (key > cur->data) {
            cur = cur->rightChild;
            isLeft = false;
        } else if (key < cur->data) {
            cur = cur->leftChild;
            isLeft = true;
        }

        if (nullptr == cur) {
            return false;
        }
    }

    // 1. 没有子节点
    // 2. 只有1个子节点
    // 3. 有2个子节点
    if (nullptr == cur->leftChild && nullptr == cur->rightChild) {
        if (parent == cur) {
            *tree = nullptr;
            free(cur);
        } else if (isLeft) {
            parent->leftChild = nullptr;
            free(cur);
        } else {
            parent->rightChild = nullptr;
            free(cur);
        }
    } else if (nullptr == cur->leftChild) {
        if (parent == cur) {
            *tree = cur->rightChild;
            free(cur);
        } else if (isLeft) {
            parent->leftChild = cur->rightChild;
            free(cur);
        } else {
            parent->rightChild = cur->rightChild;
            free(cur);
        }
    } else if (nullptr == cur->rightChild) {
        if (parent == cur) {
            *tree = cur->leftChild;
            free(cur);
        } else if (isLeft) {
            parent->leftChild = cur->leftChild;
            free(cur);
        } else {
            parent->rightChild = cur->leftChild;
            free(cur);
        }
    } else {
        BSTreeNode* carryOnNode = getCarryOnNode(cur);

        if (parent == cur) {
            *tree = carryOnNode;
            if (carryOnNode == parent->rightChild) {
                carryOnNode->leftChild = cur->leftChild;
            } else {
                carryOnNode->leftChild = cur->leftChild;
                carryOnNode->rightChild = cur->rightChild;      
            }
            free(cur);
        } else if (isLeft) {
            parent->leftChild = carryOnNode;
            carryOnNode->leftChild = cur->leftChild;
            carryOnNode->rightChild = cur->rightChild;
            free(cur);
        } else {
            parent->rightChild = carryOnNode;
            carryOnNode->leftChild = cur->leftChild;
            carryOnNode->rightChild = cur->rightChild;
            free(cur);
        }
    }

    return true;
}

// 先序遍历
// 父节点 --> 左子节点 --> 右子节点. 即 根最先访问
void preTraversalBST(BSTreeNode* tree)
{
    if (nullptr == tree) {
        return ;
    }

    std::cout << tree->data << " ";
    preTraversalBST(tree->leftChild);
    preTraversalBST(tree->rightChild);
}

// 中序遍历
// 左子节点 --> 父节点 --> 右子节点. 即 根中间访问
void inTraversalBST(BSTreeNode* tree)
{
    if (nullptr == tree) {
        return ;
    }

    inTraversalBST(tree->leftChild);
    std::cout << tree->data << " ";
    inTraversalBST(tree->rightChild);
}

// 后续遍历
// 左子节点 --> 右子节点 --> 父节点. 即 根最后访问
void postTraversalBST(BSTreeNode* tree)
{
    if (nullptr == tree) {
        return ;
    }

    postTraversalBST(tree->leftChild);
    postTraversalBST(tree->rightChild);
    std::cout << tree->data << " ";
}

int main()
{
    std::vector<int> array = {3, 6, 4, 5, 7, 2, 1};
    BSTreeNode* tree = createBSTree(array);
    
    std::cout << "pre traversal bst:" << std::endl;
    preTraversalBST(tree);
    std::cout << std::endl;

    std::cout << "in traversal bst:" << std::endl;
    inTraversalBST(tree);
    std::cout << std::endl;

    std::cout << "post traversal bst:" << std::endl;
    postTraversalBST(tree);
    std::cout << std::endl;

    int key = 2;
    std::cout << "search bst key:" << key << " result:" 
        << searchBSTree(tree, key) << std::endl;
    key = 8;
    std::cout << "search bst key:" << key << " result:" 
        << searchBSTree(tree, key) << std::endl;

    key = 3;
    std::cout << "delete key:" << key << std::endl;
    deleteBSTreeNode(&tree, key);
    std::cout << "in traversal bst:" << std::endl;
    inTraversalBST(tree);
    std::cout << std::endl;

    return 0;
}