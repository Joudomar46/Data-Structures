#include <string>
#include <iostream>
using namespace std;
class Tester;
typedef int Elem;//comment out or uncomment as required
//typedef char Elem;//comment out or uncomment as required
//typedef string Elem;//comment out or uncomment as required
class Node {
    Elem    m_value;
    Node*   m_left;
    Node*   m_right;
    int     m_height;
    Node(const Elem& v) : m_value(v),
                          m_left(nullptr), m_right(nullptr), m_height(0) { }
    friend class TreeLinked;
    friend class Tester;
public:
    void printValue(){
        if (this != nullptr) cout << m_value << endl;
        else cout << "NULL" << endl;
    }
};
class TreeLinked{
public:
    friend class Tester;
    TreeLinked():m_root(nullptr){};
    ~TreeLinked();
    void insert(const Elem& element);//with rebalance for AVL tree
    Node* find(const Elem& element);
    void remove(const Elem& element);
    void preOrder();
    void postOrder();
    void inOrder();
    void clearTree(Node* aNode);
    bool testBalanceOfTree(Node* aNode);
    void helper();
private:
    Node* m_root;

    //All private helper functions
    Node* insert(const Elem& element, Node*& aNode);//with rebalance for AVL tree
    void inOrder(Node* aNode);
    void preOrder(Node* aNode);
    void postOrder(Node* aNode);
    Node* find(Node* aNode, const Elem& element);
    Node* remove(Node* aNode, const Elem& element);//no rebalance
    Node* findMin(Node* aNode);
    Node* findMax(Node* aNode);
    int max(int a, int b);
    void updateHeight(Node *aNode);
    Node* leftRotation(Node* aNode);
    Node* rightRotation(Node* aNode);
    int checkBalance(Node* aNode);
    Node* reBalance(Node* aNode);
};