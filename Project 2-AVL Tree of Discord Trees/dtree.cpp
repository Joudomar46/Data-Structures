/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */

#include "dtree.h"


/**
 * Destructor, deletes all dynamic memory.Destructor deallocates all dynamically created
 * memory by calling the helper function DTree::clear(), and reinitialize all member variables.
 */
DTree::~DTree() {
    clear();
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 * need a helper to do preorder
 */
void DTree::operatorHelper(DNode* copy){
    if (copy != nullptr){
        this->insert(copy->getAccount());   //creates nodes and insert account info into function of new DTree
        operatorHelper(copy->_left);    //using preorder
        operatorHelper(copy->_right);
    }
}

DTree& DTree::operator=(const DTree& rhs) {

    if(this != &rhs){       //prevent assigning object to it self
        this->clear();      //deallocated memory if there is anything in this
        this->_root = nullptr; //clear memory then set root to null
        operatorHelper(rhs._root);

    }
    return *this;
}

/**
 * Dynamically allocates a new DNode in the tree.
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 *
 If a vacant node is encountered during traversal,
 * the Account can be placed in that vacant node only if 2 conditions are met:
The BST order property will be maintained.
The discriminator isn’t already in the tree
 (hint: we can use DTree::retrieve() to check whether a discriminator exists in the tree).
Finally, this function should return true if a new node was created
 or a vacant node was re-populated. It should return false otherwise.
 *
 */
bool DTree::insert(Account newAcct) {
    return insert(newAcct, this ->_root);
    //delete node;
}
bool DTree::children(DNode* node, int disc) {
    if (node->_right == nullptr && node->_left != nullptr) //child on left
        return node->_left->getDiscriminator() < disc;
    if (node->_right != nullptr && node->_left == nullptr)  //child on right
        return node->_right->getDiscriminator() > disc;
    if (node->_right != nullptr && node->_left != nullptr) //both
        return ((node->_left->getDiscriminator() < disc) && (node->_right->getDiscriminator() > disc));
    else
        return true;   //no children
}

bool DTree::insert(Account newAcct, DNode*& node){
    //If a node has a discriminator that matches the one to be inserted, a new node should not be created return false
    if (!retrieve(newAcct.getDiscriminator())){
        if (node != nullptr && node->isVacant() && children(node,newAcct.getDiscriminator())){//is vacant but tree property is not ruined
            //fill node with account info
            node->_account._username = newAcct.getUsername();
            node->_account._disc = newAcct.getDiscriminator();
            node->_account._nitro = newAcct.hasNitro();
            node->_account._badge = newAcct.getBadge();
            node->_account._status = newAcct.getStatus();
            node->_vacant = false;                 //set vacancy to false
            updateSize(this->_root);               //update the sizes and number of vacant nodes
            updateNumVacant(this->_root);          //update the sizes and number of vacant nodes
            checkImbalance(this->_root);           //check for an imbalance in tree once something is inserted
            return true;
        }
        if (node == nullptr){                       //check if null pointer
            node = new DNode(newAcct);    //allocate memory
            updateSize(this->_root);               //update the sizes and number of vacant nodes
            updateNumVacant(this->_root);          //update the sizes and number of vacant nodes
            checkImbalance(this->_root);           //check for an imbalance in tree once something is inserted
            return true;
        }
        else{
            if (newAcct.getDiscriminator() < node->getAccount().getDiscriminator()) {      //sort based on _disc
                insert(newAcct, node->_left);
            }
            else{
                insert(newAcct, node->_right);
            }
            return true;
        }
    }
    return false;
}

/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 * setting DNode’s member variable _vacant to true and increasing _numVacant by 1.
 * The node must retain the original discriminator in order for tree traversals to function.
 * If a node is marked vacant, the “removed” parameter should contain the vacant node, and the
 * function should return true. Otherwise, it should return false. The member variable _numVacacant
 * should also be updated accordingly for all parent nodes of the newly vacant node.
 */
//helper to remove
bool DTree::removedIt(int disc, DNode* removed){
    removed = retrieve(disc); //the “removed” parameter should contain the vacant node, if found it has the node else null
    if (removed == nullptr) { //not found is null
        return false;
    }else{
        removed->_vacant = true;         //_vacant to true
        removed->_numVacant =+1;        //increasing _numVacant by 1
        updateNumVacant(this->_root);       //_NumVaccant for all parent nodes of the newly vacant node.
        return true;
    }
}

bool DTree::remove(int disc, DNode*& removed) {
    return removedIt(disc, removed);
}


/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 * This function returns a DNode with a discriminator that matches the
 * integer passed in. If no node with a matching discriminator is found,
 * this function returns nullptr. Vacant nodes should not be returned.
 */
//retrieve helper
DNode* DTree::retrieve(int disc, DNode* node) {
    if (node != nullptr) {
        //if found return node, cant return a vacant
        if ((node->getDiscriminator() == disc) && !node->isVacant()) {
            return node;
        }
        // disc is greater than root's disc
        if (node->getDiscriminator() < disc)
            return retrieve(disc, node->_right);
        // disc is smaller than root's disc
        return retrieve(disc, node->_left);
    }
    return nullptr;  //if nothing found or null return null,
}

DNode* DTree::retrieve(int disc) {
    return retrieve(disc, this->_root);
}

/**
 Helper for the destructor to clear dynamic memory.Helper for the destructor to clear dynamic memory.
(Hint: if you want to implement the functionality recursively, to facilitate a recursive implementation
 you can introduce a helper function.)
 */

void DTree::helpClear(DNode* node){
    // If node is empty, don't bother
    if (node == nullptr)
        return;
    else{
        helpClear(node->_left);
        helpClear(node->_right);
        delete node;
        node = nullptr;
    }
}

void DTree::clear(){
    helpClear(this->_root);
}

/**
 * Prints all accounts' details within the DTree.
 * need helper, in-order traversal, to check whether
insert is working correctly, uses insertion operator
 This function prints out account details using in-order traversal
 of discriminator values. It should use the overloaded insertion
 operator (<<) for the Account class. The implementation of insertion
 operator is provided. Vacant nodes should not be printed.
 */
//print account helper
void DTree::printAccounts(DNode* node) const {
    if(node == nullptr) return;
    printAccounts(node->_left);
    if(!node->isVacant())       //dont print vacant nodes
        cout << node->getAccount() <<endl;
    printAccounts(node->_right);

}

void DTree::printAccounts() const {
    printAccounts(this->_root);
}

/**
 * Dump the DTree in the '()' notation.
 */

void DTree::dump(DNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {
    return this->_root->getSize() - this->_root->getNumVacant();
}

/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 * void DTree::updateSize(DNode* node), uses size from children + 1, if child null use
DEFAULT_SIZE
 a _size variable that holds the size of the subtree
 (total number of nodes in the subtree plus the root of subtree itself),
 */
void DTree::updateSize(DNode* node) {
    if (node != nullptr) {

        updateSize(node->_left);       // first recur on left subtree
        updateSize(node->_right);      // then recur on right subtree
        // now deal with the node
        if (node->_left || node->_right != NULL) {
            if (node->_right == NULL) {              //node only has left child?
                node->_size = node->_left->getSize() + 1;
            }
            if (node->_left == NULL) {               //node only has right child?
                node->_size = node->_right->getSize() + 1;
            } else if (node->_left && node->_right != NULL)      //both children?
                node->_size = node->_left->getSize() + node->_right->getSize() + 1;
        } else
            node->_size = DEFAULT_SIZE;         //no children?
    }
}


/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 * _vacant variable that counts the number of vacant nodes in a node’s subtree plus itself if vacant.
 * children vacant size + itself is vacant, if
child null default value
 */
void DTree::updateNumVacant(DNode* node) {
    if (node == NULL) {
        return;
    }
    // first recur on left subtree
    updateNumVacant(node->_left);
    // then recur on right subtree
    updateNumVacant(node->_right);
    // now deal with the node
    if (node->_left || node->_right != NULL) { //does node have a child?
        if (node->_right == NULL) {             //child on left?
            node->_numVacant = node->_left->getNumVacant() + int(node->isVacant());
        }
        if (node->_left == NULL) {              //child on right?
            node->_numVacant = node->_right->getNumVacant() + int(node->isVacant());
        } else  if (node->_left && node->_right != NULL)                                 //child on both sides?
            node->_numVacant = node->_left->getNumVacant() + node->_right->getNumVacant() + int(node->isVacant());
    } else
        node->_numVacant = int(node->isVacant()) + DEFAULT_NUM_VACANT; //if child null default value
}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 * use balance rules and children sizes to
check
 instead of balancing every small imbalance, we can wait for a larger imbalance
 to occur and re-build the subtree into a complete tree.
 */
bool DTree::checkImbalance(DNode* node) {
    if (node != NULL) { //if null return false

        int leftSize = 0;
        int rightSize = 0;
        if (node->_left != nullptr)     //check left and right sizes
            leftSize = node->_left->getSize();
        if (node->_right != nullptr)
            rightSize = node->_right->getSize(); //tree with one child? temp size already 0
        if ((leftSize >= 4) || (rightSize >= 4)){ //first want to check if any subtree is >=4
            if (leftSize < rightSize)
                return (rightSize >= (leftSize * 1.5));  //small num * 1.5 > big num = imbalance return true
            else
                return (leftSize >= (rightSize * 1.5));
        }
    }   else
        return 0;    //all other cases return false ex 1,3 0 2
}


//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 * First, we must create an array to move the subtree's nodes into.
 * To make rebuilding the tree easier, the nodes should be sorted from least to greatest.
 * We can find the new root of the subtree in constant time by taking the middle element of the array.
 */

//function to convert a BST tree to an Array
void DTree::convertArr(DNode *node, DNode arr[], int *counter) {
    if (node == nullptr ) {
        return;
    }
    //in order traversal
    convertArr(node->_left, arr, counter);    //first visit the left child
    if (!node->isVacant()) {
        arr[*counter] = node->getAccount();
        (*counter)++;
    }
    convertArr(node->_right, arr, counter);//third visit the right child
}
//function to convert an Array to BST with helper to insert
void DTree::sortedArrayToBST(DNode arr[] ,
                             int start, int end)
{
    //Base Case
    if (start > end)
        return;

    int mid = (start + end)/2; //do the division
    //cout << " Mid values: "<< mid ;

    helperAtoBST(mid, arr);    //give mid value and array to helper func
    sortedArrayToBST( arr,start, mid - 1); //recurr to the left mid points
    sortedArrayToBST(arr,  mid + 1, end); //recurr to the right mid points
}

//help sort array to add onto or create new DNodes in subtree
void DTree::helperAtoBST(int mid,DNode arr[]){

    //  cout << arr[mid]->getAccount();
    insert(arr[mid].getAccount());         //use mid value and find the place of insertion
    // (if null or if a child of node: insert takes care of it)
    //This function alone took me 7.4 hours to figure out.....

    //cout << this->_left->getAccount();
}

void DTree::rebalance(DNode*& node) {

    updateNumVacant(node);  //want to make sure we have correct info
    updateSize(node);       //want to make sure we have correct info

    if (this->checkImbalance(node)) {
        int capacity = ((node->getSize() - (node->getNumVacant())));    //dynamic array size is num of non vacant nodes
        DNode *arr = new DNode [capacity];                            //declare dynamic array
        int counter = 0;                                                //counter
        convertArr(node, arr, &counter);                                //tree becomes a dynamic array


        if (counter == capacity) {          //making sure we have the right arr to prevent memory issues
            helpClear(*&node);    // clear the subtree
            node = nullptr;

            sortedArrayToBST(arr, 0, counter - 1); //convert array to BTS tree
            cout<<endl;
            dump();


            if (this->checkImbalance(this->_root)) {
                cout << "There was an error in your rebalancing" << endl;
            }
        }


        //delete[] arr[capacity];
        //arr = nullptr;      //once done set to null and delete
        //delete arr;
        delete[] arr;

    }
}

//help delete a sub tree
void DTree::deleteSubTree(DNode*& node){
    if (node != nullptr) {
        deleteSubTree(node->_left);//first delete the left child
        deleteSubTree(node->_right);//then delete the right child
    }
    node = nullptr;
    delete node;//then delete the node itself
}


void DTree::tester() {
    cout << "is it balanced"<<endl;
    cout << checkImbalance(_root) <<endl;
    // rebalance(this->_root);
    printAccounts();
    cout << remove(5, _root )<<endl;

    dump();
    cout << endl;
    rebalance(_root->_right);
    cout <<endl;

    //printAccounts();
    //updateNumVacant(_root);
    // cout << getNumUsers();
}


/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
*/
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() <<
         "\n\tDiscriminator: " << acct.getDiscriminator() <<
         "\n\tNitro: " << acct.hasNitro() <<
         "\n\tBadge: " << acct.getBadge() <<
         "\n\tStatus: " << acct.getStatus();
    return sout;
}
