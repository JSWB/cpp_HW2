#include<iostream>
#include <QCoreApplication>

using namespace std;

class Tree;

class TreeNode{
    friend class Tree;
private:
    char data;
    TreeNode *LL;
    TreeNode *RR;

public:
    TreeNode(char val = 0) : data(val)    {    data = val;    }
    void Visit() {    cout << data;    }
};

class Tree{
private:
    TreeNode* root;
    TreeNode* set[26];
    int rootCount;
public :
    Tree() {    rootCount = 0;    }

    void Create(char PPdata, char LLdata, char RRdata) {
        TreeNode* parent = new TreeNode();
        TreeNode* LL = new TreeNode();
        TreeNode* RR = new TreeNode();

        parent->data = PPdata;
        if (parent->data == 'A') root = parent;
        if (LLdata != '.') {
            LL->data = LLdata;
            parent->LL = LL;
        }

        if (RRdata != '.') {
            RR->data = RRdata;
            parent->RR = RR;
        }
        set[rootCount++] = parent;
    }

    void Sum() {
        for (int i = 0; i < rootCount; i++) {
            TreeNode* parent = set[i];
            bool leftFull = parent->LL ? false : true;
            bool rightFull = parent->RR ? false : true;
            for (int j = 0; j < rootCount; j++) {
                if (!leftFull && parent->LL && parent->LL->data == set[j]->data) {
                    parent->LL = set[j];
                    leftFull = true;
                }
                if (!rightFull && parent->RR && parent->RR->data == set[j]->data) {
                    parent->RR = set[j];
                    rightFull = true;
                }
                if (leftFull&&rightFull) break;
            }
        }
    }

    void Pre()const { Pre(root);}

    void Pre(TreeNode* node)const {
        TreeNode* currNode = node;
        if (currNode) {
            currNode->Visit();
            Pre(currNode->LL);
            Pre(currNode->RR);
        }
    }

    void In()const { In(root); }

    void In(TreeNode* node)const {
        TreeNode* currNode = node;
        if (currNode) {
            In(currNode->LL);
            currNode->Visit();
            In(currNode->RR);
        }
    }

    void Post() { Post(root); } const

    void Post(TreeNode* node)const {
        TreeNode* currNode = node;
        if (currNode) {
            Post(currNode->LL);
            Post(currNode->RR);
            currNode->Visit();
        }
    }
};

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    Tree tree;

    for (int i = 0; i < n; i++) {
        char data, left, right;
        cin >> data >> left >> right;
        tree.Create(data, left, right);
    }

    tree.Sum();
    tree.Pre();
    cout << '\n';
    tree.Post();

    QCoreApplication a(argc, argv);

    return a.exec();
    cout << '\n';
    tree.In();
}
