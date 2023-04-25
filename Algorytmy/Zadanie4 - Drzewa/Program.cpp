#include <iostream>

using namespace std;

struct Node
{
    string name;
    int t;

    Node *left;
    Node *right;

    Node(string name)
    {
        this->left = nullptr;
        this->right = nullptr;
        this->name = name;
        this->t = 0;
    }
};

void add(Node *node, string name)
{

    if(node->name == name)
    {
        node->t++;
    }
    else if(node->name < name)
    {
        if (node->right == nullptr)
            node->right = node->right = new Node(name);
        else
        {
            add(node->right,name);
        }
    }
    else if(node->name > name)
    {
        if (node->left == nullptr)
            node->left = node->left = new Node(name);
        else
        {
            add(node->left,name);
        }
    }
}

void inorder(Node *n)
{
    if(n)
    {
        inorder(n->left);
        for (int i = 0; i <= n->t; i++)
            cout << n->name << "\n";
        inorder(n->right);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    unsigned int n = 10;
    string s;
    
    cin >> n;
    cin >> s;
    Node *root = new Node(s);

    for (int i = 1; i < n; i++)
    {
        cin >> s;
        add(root, s);
    }

    inorder(root);

    return 0;
}