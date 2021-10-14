#include "treeLinked.h"

TreeLinked::~TreeLinked(){
    //start from root to delete pointers
    clearTree(m_root);
}
void TreeLinked::helper() {
    cout << testBalanceOfTree(m_root);
}
bool TreeLinked::testBalanceOfTree(Node* aNode){
    //take height of both children, check if balanced
    //if not balanced return false
    //m_height
    int balance = -1;
    if (aNode != nullptr){
        int leftHeight = -1;
        int rightHeight = -1;
        if (aNode->m_left != nullptr)
            leftHeight= aNode->m_left->m_height ;
        if (aNode->m_right != nullptr)
            rightHeight = aNode->m_right->m_height ;
        balance = (leftHeight - rightHeight);
        if(balance < -1 || balance > 1){
            return false;
        }
        testBalanceOfTree(aNode->m_left);//first visit the left child
        testBalanceOfTree(aNode->m_right);//second visit the right child
    }

}


void TreeLinked::updateHeight(Node *aNode) {
    if ( aNode == nullptr ) return ;
    int leftHeight = ( aNode->m_left == nullptr ? -1 : aNode->m_left->m_height );
    int rightHeight = ( aNode->m_right == nullptr ? -1 : aNode->m_right->m_height );
    aNode->m_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
}

void TreeLinked::clearTree(Node* aNode){
    //This works on any subtree
    if(aNode == nullptr){//there is no pointer to delete
        return;
    }
    else{
        clearTree(aNode->m_left);//first delete the left child
        clearTree(aNode->m_right);//then delete the right child
        delete aNode;//then delete the node itself
    }
}

void TreeLinked::inOrder(Node* aNode){
    if (aNode != nullptr){
        cout << "(";
        inOrder(aNode->m_left);//first visit the left child
        cout << aNode->m_value << ":" << aNode->m_height;//second visit the node itself
        inOrder(aNode->m_right);//third visit the right child
        cout << ")";
    }
}
void TreeLinked::inOrder(){inOrder(m_root);}
void TreeLinked::postOrder(Node* aNode){
    if (aNode != nullptr){
        postOrder(aNode->m_left);//first visit the left child
        postOrder(aNode->m_right);//second visit the right child
        cout << aNode->m_value << " ";//third visit the node itself
    }
}
void TreeLinked::postOrder(){postOrder(m_root);}
void TreeLinked::preOrder(Node* aNode){
    if (aNode != nullptr){
        cout << aNode->m_value << " ";//first visit the node itself
        preOrder(aNode->m_left);//second visit the left child
        preOrder(aNode->m_right);//third visit the right child
    }
}
void TreeLinked::preOrder(){preOrder(m_root);}
Node* TreeLinked::findMin(Node* aNode){
    if (aNode == nullptr || aNode->m_left == nullptr)
        return aNode;
    else//to find min we only need to move to left
        return findMin(aNode->m_left);
}
Node* TreeLinked::findMax(Node* aNode){
    if (aNode == nullptr || aNode->m_right == nullptr)
        return aNode;
    else//to find max we only need to move to right
        return findMax(aNode->m_right);
}
Node* TreeLinked::find(Node* aNode, const Elem& element){
    if (aNode == nullptr || aNode->m_value == element)
        return aNode;
    else if (aNode->m_value > element)// move to left
        return find(aNode->m_left, element);
    else  // the case of (aNode->m_value < element)
        return find(aNode->m_right, element);// move to right
}
Node* TreeLinked::find(const Elem& element){
    // start searching from root
    return find(m_root, element);
}
void TreeLinked::remove(const Elem& element){
    // start searching from root
    remove(m_root, element);
}
Node* TreeLinked::remove(Node* aNode, const Elem& element){
    Node* temp;
    if(aNode == nullptr)// item not found; do nothing
        return nullptr;
        // continue to traverse until we find the element
    else if(element < aNode->m_value)//traverse to left
        aNode->m_left = remove(aNode->m_left, element);
    else if(element > aNode->m_value)//traverse to right
        aNode->m_right = remove(aNode->m_right, element);
        // the case of the node with two children
    else if(aNode->m_left && aNode->m_right){
        // find right’s lowest value
        temp = findMin(aNode->m_right);
        // copy its value to the node that we want to delete
        aNode->m_value = temp->m_value;
        // now delete the found node
        aNode->m_right = remove(aNode->m_right, aNode->m_value);
    }
    else{// the case of zero or one child
        // also, in the case of two children, after finding right’s lowest
        // value we end up here by calling remove function recursively
        temp = aNode;
        if(aNode->m_left == nullptr)
            aNode = aNode->m_right;
        else if(aNode->m_right == nullptr)
            aNode = aNode->m_left;
        delete temp;
    }
    updateHeight(aNode);
    aNode = reBalance(aNode);
    return aNode;
}

int TreeLinked::max(int a, int b) {
    return (a > b) ? a : b;
}

Node* TreeLinked::leftRotation(Node* aNode){
    Node* z = aNode;
    Node* y = z->m_right;
    z->m_right = y->m_left;
    y->m_left = z;
    updateHeight(z);
    updateHeight(y);
    return y;
}

Node* TreeLinked::rightRotation(Node* aNode){
    Node* y = aNode;
    Node* x = y->m_left;
    y->m_left = x->m_right;
    x->m_right = y;
    updateHeight(x);
    updateHeight(y);
    return y;
}


int TreeLinked::checkBalance(Node* aNode){
    if (aNode == nullptr)
        return -1;
    else{
        int leftHeight = -1;
        int rightHeight = -1;
        if (aNode->m_left != nullptr)
            leftHeight = aNode->m_left->m_height;
        if (aNode->m_right != nullptr)
            rightHeight = aNode->m_right->m_height;
        return (leftHeight - rightHeight);
    }
}

Node* TreeLinked::reBalance(Node* aNode){
    if ((checkBalance(aNode) < -1) && (checkBalance(aNode->m_right) <= 0))
        return leftRotation(aNode);//do left rotation at z
    else if ((checkBalance(aNode) > 1) && (checkBalance(aNode->m_left) >= 0))
        return rightRotation(aNode);//do right rotation at z
    else if ((checkBalance(aNode) < -1) && (checkBalance(aNode->m_right) >=0)){
        //double rotation, right rotation at aNode->m_right, left rotation at aNode
        aNode->m_right = rightRotation(aNode->m_right);//right rotation at aNode->m_right, i.e. y
        return leftRotation(aNode);//left rotation at aNode, i.e. z
    }
    else if ((checkBalance(aNode) > 1) && (checkBalance(aNode->m_left) <= 0)){
        ;//double rotation, left rotation at aNode->m_left, right rotation at aNode
        aNode->m_left = leftRotation(aNode->m_left);//left rotation at aNode->m_left, i.e. y
        return rightRotation(aNode);//right rotation at aNode, i.e. z
    }
    else
        return aNode;
}

void TreeLinked::insert(const Elem& element){
    m_root = insert(element, m_root);
}

Node* TreeLinked::insert(const Elem& element, Node*& aNode){
    if (aNode == nullptr){
        Node* aNode = new Node(element);
        return aNode;
    }
    else if ( aNode->m_value > element ){
        aNode->m_left = insert(element, aNode->m_left);
        updateHeight(aNode);
        return reBalance(aNode);
    }
    else if ( aNode->m_value < element ){
        aNode->m_right = insert(element, aNode->m_right);
        updateHeight(aNode);
        return reBalance(aNode);
    }
    else //the element exists in the tree, we do not allow duplicates
        return aNode;
}