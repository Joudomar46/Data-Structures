/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {
    clear();
}

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */
void UTree::loadData(string infile, bool append) {
    std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];

    /* Check to make sure the file was opened */
    if(!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
    if(!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
    while(std::getline(instream, line)) {
        std::stringstream buffer(line);

        /* Quick check to make sure each line is formatted correctly */
        int delimCount = 0;
        for(unsigned int c = 0; c < buffer.str().length(); c++) if(buffer.str()[c] == delim) delimCount++;
        if(delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes -
         * Each line always has 5 sections of data */
        for(int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
}

/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree.
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 *
 */


bool UTree::insert(Account newAcct) {
    return insert(newAcct, this->_root);
}
bool UTree::insert(Account newAcct, UNode*& node) {

    if (node != nullptr &&
        (node->getUsername() == newAcct.getUsername())) { //if there exists an account w same user name
        node->getDTree()->insert(
                newAcct);                 //inserts an Account object into the UNode with a matching username
        return false;                                      //If the Account already existed, the insertion should fail and return false
    }
    if (node == nullptr) {
        node = new UNode();                         //no UNode is found, one must be created.
        node->getDTree()->insert(
                newAcct);          //the UNode should pass the Account object into its DTree’s insertion function.
        return true;                                //return true if the account was successfully inserted into the DTree.
    }   //The username should be used as the key to traverse the UTree and abide by BST traversal rules
    else if (node->getUsername() > newAcct.getUsername()) {
        insert(newAcct, node->_left);
        updateHeight(node);
        if(checkImbalance(node)){
            *&node = rebalance(node);
        }
    } else if (node->getUsername() < newAcct.getUsername()) {
        insert(newAcct, node->_right);
        updateHeight(node);
        if(checkImbalance(node)){
            *&node = rebalance(node);
        }
    }
    return true;

}



/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 *
For deleting a UNode you can write a helper function which its job is to remove a node in an AVL tree.
 The following presents a sample algorithm to delete a node:
If the node to delete has a left subtree, locate the largest node in the left subtree. This node will
 be referenced as node X moving forward. Node X can be found by traversing down to the left once
 and then as far right as possible. Copy node X’s value (DTree) into the node with the empty DTree.
 (Hint: you overloaded an operator to perform to help here).
If node X has a left child, the child will take node X’s place.
Delete node X and, if it exists, shift the left child into its spot. This can also be done by
 copying node X’s child’s value into node X and deleting the child instead.
On the way back up the path taken to find node X, check for imbalances.
If the node with an empty DTree does not have a left subtree, shift its right child into its spot.
After removing the UNode we should continue updating the heights and checking for imbalances as traversing back up the tree.
 */

//helper function to delete a specific UNode
UNode* UTree::removeUNode(UNode* removed, string username) {
    UNode *temp;
    if (removed == nullptr)// item not found; do nothing
        return nullptr;

    else if (username < removed->getDTree()->getUsername()) {    //traverse to left
        removed->_left = removeUNode(removed->_left, username);
    } else if (username > removed->getDTree()->getUsername()) {//traverse to right
        removed->_right = removeUNode(removed->_right, username);

    }
        // the case of the node with two children
    else if (removed->_left != nullptr && removed->_right != nullptr) { //If the node to delete has a left subtree
        temp = findRightMost(removed->_right); //traverse all the way to the right
        *removed->_dtree = *(temp->_dtree);  //copy Dtree into vacant Dtree
        removed->_right = removeUNode(removed->_right, removed->getDTree()->getUsername());
    } else {// the case of zero or one child
        // also, in the case of two children, after finding right’s lowest
        // value we end up here by calling remove function recursively
        temp = removed;
        if (removed->_left == nullptr)   //no left subtree
            removed = removed->_right;
        else if (removed->_right == nullptr) //rightmost has left child
            removed = removed->_left;
        delete temp;
    }
    updateHeight(removed);
    if (checkImbalance(removed)) {
        removed = rebalance(removed);
    }
    return removed;

}
UNode* UTree::findRightMost(UNode* aNode) {
    if (aNode == nullptr || aNode->_right == nullptr)
        return aNode;
    else//to find max we only need to move to right
        return findRightMost(aNode->_right);
}

bool UTree::removeUser(string username, int disc, DNode*& removed) {
    //This function removes the user specified by the username and discriminator.
    // with the matching discriminator from the DTree.
    if (removed == nullptr){
        return false;
    }
    removed = retrieveUser(username,disc);  //returns the DNode or null if not found
    //returns the Unode or null if not found, vacant node is not returned
    if ((removed != nullptr) && (retrieve(username) != nullptr)) {
        // take the UNode with that user name, get its dtree remove its disc
        this->retrieve(username)->getDTree()->remove(disc,removed);
        //The UNode should only be deleted if the DTree no longer contains any non-vacant nodes.
        if (retrieve(username)->getDTree()->getNumUsers() == 0){
            removeUNode(_root, username);
        }
        return true;  //account removed
    }else
        return false; //false otherwise

}

bool UTree::removeMain(string username, int disc){
    DNode* removed;
    removed = retrieveUser(username,disc);
    return removeUser(username,disc, removed);

}


/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username) {
    return retrieve(username, this->_root);
}

UNode* UTree::retrieve(string username, UNode* node) {
    if (node == nullptr){
        return nullptr;
    }
    if (node != nullptr) {
        //if found return node, cant return a vacant
        if ((node->getDTree()->getUsername() == username)) {
            return node;
        }
        //greater than roots
        if ((node->getDTree()->getUsername() < username))
            return retrieve(username, node->_right);
        //smaller than root's
        return retrieve(username, node->_left);
    }

}
/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc) {
    //then queries the DTree for a DNode with a matching discriminator.
    //find the UNode with mattching username-> get its Dtree-> pass in disc to be found in specific d tree;
    return retrieve(username)->getDTree()->retrieve(disc); //will return the DNode if found or null other wise.

}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {
    return retrieve(username)->getDTree()->getNumUsers();   // find the Unode with that username,
    // get its DTrees number of users using dtrees func;
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear(UNode* node){
    if(node == nullptr){//there is no pointer to delete
        return;
    }
    else{
        clear(node->_left);//first delete the left child
        clear(node->_right);//then delete the right child
        delete node;//then delete the node itself
    } //the dtree in a node is deleted from Unodes func to deallocate dtree in utree.cpp
}
void UTree::clear() {
    clear(this->_root);
}


/**
 * Prints all accounts' details within every DTree.
 * This function prints the Account details of all accounts in all DTrees. It calls the DTree::printAccounts() function.
 */
void UTree::printUsers() const {
    printUsers(this->_root);
}

void UTree::printUsers(UNode* node) const {
    if(node == nullptr) return;
    printUsers(node->_left);    //in order traversal of each UNode- then print the specific DTree in that UNode
    node->getDTree()->printAccounts();
    printUsers(node->_right);

}

/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {
    //The height of a leaf node is 0. The height of all internal nodes can
    //be calculated based on the heights of their immediate children.
    if ( node == nullptr ) return ;
    int leftHeight = ( node->_left == nullptr ? -1 : node->_left->_height );
    int rightHeight = ( node->_right == nullptr ? -1 : node->_right->_height );
    node->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node) {
//take height of both children, check if balanced
    int balance = -1;
    if (node != nullptr){
        int leftHeight = -1;
        int rightHeight = -1;
        if (node->_left != nullptr)
            leftHeight= node->_left->_height ;
        if (node->_right != nullptr)
            rightHeight = node->_right->_height ;
        balance = (leftHeight - rightHeight);
        if(balance < -1 || balance > 1){  // height diffrence is not 0 , 1, -1
            return 1;                     //return true if imbalance occured
        }
        checkImbalance(node->_left);//first visit the left child
        checkImbalance(node->_right);//second visit the right child
    }
    return 0;           //return false if imbalance doesnt occure
}


/*
DNode* DTree::findMin(DNode* aNode){
    if (aNode == nullptr || aNode->_left == nullptr)
        return aNode;
    else//to find min we only need to move to left
        return findMin(aNode->_left);
}

*/

//----------------
/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */
//void UTree::rebalance(UNode*& node) {}

// -- OR --


/**
 * Begins and manages the rebalance procedure for an AVL tree (returns a pointer).
 * @param node UNode object where an imbalance occurred
 * @return UNode object replacing the unbalanced node's position in the tree
 */
UNode* UTree::leftRotation(UNode* aNode){
    UNode* z = aNode;
    UNode* y = z->_right;
    z->_right = y->_left;
    y->_left = z;
    updateHeight(z);
    updateHeight(y);
    return y;
}

UNode* UTree::rightRotation(UNode* aNode){
    UNode* z = aNode;
    UNode* y = z->_left;
    z->_left = y->_right;
    y->_right = z;
    updateHeight(z);
    updateHeight(y);
    return y;
}

int UTree::hDiff(UNode* aNode){
    if (aNode == nullptr)
        return -1;
    else{
        int leftHeight = -1;
        int rightHeight = -1;
        if (aNode->_left != nullptr)
            leftHeight = aNode->_left->_height;
        if (aNode->_right != nullptr)
            rightHeight = aNode->_right->_height;
        return (leftHeight - rightHeight);
    }
}
// rebalance a specific node
UNode* UTree::rebalance(UNode* node) {
    if ((hDiff(node) < -1) && (hDiff(node->_right) <= 0))
        return leftRotation(node);//do left rotation at z
    else if ((hDiff(node) > 1) && (hDiff(node->_left) >= 0))
        return rightRotation(node);//do right rotation at z
    else if ((hDiff(node) < -1) && (hDiff(node->_right) >=0)){
        //double rotation, right rotation at node->_right, left rotation at aNode
        node->_right = rightRotation(node->_right);//right rotation at aNode->m_right, i.e. y
        return leftRotation(node);//left rotation at aNode, i.e. z
    }
    else if ((hDiff(node) > 1) && (hDiff(node->_left) <= 0)){
        //double rotation, left rotation at aNode->m_left, right rotation at aNode
        node->_left = leftRotation(node->_left);//left rotation at aNode->m_left, i.e. y
        return rightRotation(node);//right rotation at aNode, i.e. z
    }
    else
        return node;
}