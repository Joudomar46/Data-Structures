#include "dtree.h"
#include "utree.h"
#include <random>

#define NUMACCTS 10
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testSameDisc(DTree& dtree);
    void testRetrieve(DTree& dtree, int disc);
    void testPrintAccounts(DTree& dtree);
    bool testBalance(DTree& dtree1);
    void testPrintAccAddress(DTree& tree);
    bool testRebalence(DTree& tree);
    void testRemove(DTree& tree, int num);
    bool testBasicUTreeInsert(UTree& utree);
    bool testUtreeRemove(UTree& utree, string username, int disc);
};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}
bool Tester::testSameDisc(DTree& dtree) {
    bool allInserted = false;
    Account newAcct = Account("", 1344, 0, "", "");
    if(!dtree.insert(newAcct)) {
        allInserted = true;
    }
    return allInserted;
}
void Tester::testRetrieve(DTree& dtree , int disc) {
    if(dtree.retrieve(disc)) {
        cout << "test passed" << endl;
        cout << "Account retrieved with disc: " << disc <<" :" << endl;
        cout << dtree.retrieve(7293)->getAccount();
        cout << endl;

    }
    if(!dtree.retrieve(disc)) {
        cout << "test passed"<< endl;
        cout << "Tree does not have disc: " << disc << endl;
        dtree.dump();
        cout << endl;
    }
}

void Tester::testPrintAccounts(DTree& dtree){
    dtree.printAccounts();
    dtree.dump(); //for comparing
}

bool Tester::testBalance(DTree& dtree1){
    return dtree1.checkImbalance(dtree1._root); //returns true only if there is an imbalance
}

void Tester::testPrintAccAddress(DTree& tree){
    cout << &tree._root->_account;
    cout<<endl;
}

bool Tester::testRebalence(DTree& tree){
    tree.rebalance(tree._root);
    return tree.checkImbalance(tree._root);
}

void Tester::testRemove(DTree& tree,int num){
    tree.remove(num, tree._root);
    tree.dump();
    cout<<endl;
}


bool Tester::testBasicUTreeInsert(UTree& utree) {
    string dataFile = "accounts.csv";
    try {
        utree.loadData(dataFile);
    } catch(std::invalid_argument e) {
        std::cerr << e.what() << endl;
        return false;
    }
    return true;
}
bool Tester::testUtreeRemove(UTree& utree, string username, int disc){
    return utree.removeMain(username, disc);
}

int main() {
    cout << "Welcome to my long awaited project..." <<endl;
    cout << "****************************************************" <<endl;
    Tester tester;

    //Basic dtree tests: Insertion
    DTree dtree;
    cout << "Testing DTree insertion...";
    if(tester.testBasicDTreeInsert(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;
    cout << endl;

    cout << "Testing DTree insertion same discriminator...";
    if(tester.testSameDisc(dtree)) {
        cout << "test passed" << endl;
        cout << "The disc number already exists in tree" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;
    cout << endl;

    cout << "Testing DTree insertion only one...";
    DTree oneTree;
    Account newAcctOne = Account("", 15, 0, "", "");
    if(oneTree.insert(newAcctOne)){
        cout << "test passed" << endl;
    }else
        cout << "test failed" << endl;
    oneTree.dump();
    cout << endl;
    cout << endl;

    cout << "Testing DTree removing only one...";
    tester.testRemove(oneTree,15);
    if(oneTree.getNumUsers()==0){
        cout << "test passed" << endl;
    }else
        cout << "test failed" << endl;
    cout << endl;
    cout << endl;


    cout << "****************************************************" <<endl;
    //clear() - function works properly, no sigm errors and tested in valgrind for memory leaks
    //update size is visually represented in the dump function. the sizes of the nodes are there

    //DTree retrieve
    cout << "Testing DTree retrieve...";
    tester.testRetrieve(dtree, 7291);   // tests passing
    cout << endl;
    tester.testRetrieve(dtree, 0001);   //tests failing
    cout << endl;

    cout << "****************************************************" <<endl;
    //DTree testPrintAccounts
    cout << "Testing DTree prrintAccounts..."<<endl;
    tester.testPrintAccounts(dtree);
    cout << endl;
    cout << endl;

    cout << "****************************************************" <<endl;
    //DTree test imbalance:
    cout << "Testing DTree imbalance...";
    if(tester.testBalance(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Show balanaced tree" << endl;
    dtree.dump();
    cout << endl;
    cout << endl;

    Tester tester1;
    DTree dtree1;
    for(int i = 3; i < 6; i++) {
        Account newAcct = Account("", i, 0, "", "");
        dtree1.insert(newAcct);
    }
    Account newAcctIn = Account("", 2, 0, "", "");
    dtree1.insert(newAcctIn);
    //DTree test if balanced :
    cout << "Testing DTree when balanced...";
    if(!tester1.testBalance(dtree1)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Show balanaced tree" << endl;
    dtree1.dump();
    cout << endl;
    cout << endl;

    cout << "****************************************************" <<endl;
    //operator= testing:
    cout << "Testing copy constructor...";
    dtree = dtree1;
    cout<<endl;
    cout << &dtree<<endl;
    cout << &dtree1<<endl;
    tester.testPrintAccAddress(dtree); //shows the address of accounts are diffrent
    tester.testPrintAccAddress(dtree1);
    dtree.dump();
    cout<<endl;
    dtree1.dump();
    cout << endl;
    cout << endl;

    cout << "****************************************************" <<endl;
    //testing rebalance
    cout << "Testing rebalance...";
    for(int i = 5; i < 10; i++) {
        Account newAcct = Account("", i, 0, "", "");
        dtree1.insert(newAcct);
    }
    if(tester1.testBalance(dtree1)) {
        cout << "Tree needs to be rebalanced" << endl;
    } else {
        cout << "Tree does not need to be rebalanced" << endl;
    }
    dtree1.dump();
    cout<<endl;
    if(!tester1.testRebalence(dtree1)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Visual rep "<<endl;
    dtree1.dump();
    cout<<endl;
    cout<<endl;

    cout << "****************************************************" <<endl;
    cout << "Testing remove..."<<endl;
    //testing remove
    //update number vacant + remove function work together
    tester.testRemove(dtree1,7); //notice how disc 5 and 7 were both marked as 1 for size of vacancy
    tester.testRemove(dtree1,5); //notice 5 size of vac is 2 now
    tester.testRemove(dtree1,534); //nothing happens - node not found
    for(int i = 20; i < 27; i++) {
        Account newAcct = Account("", i, 0, "", "");
        dtree.insert(newAcct);
    }
    tester.testRemove(dtree,5);
    cout<<endl;

    cout << "****************************************************" <<endl;
    cout << "Testing rebalance with vacant num..." << endl;
    for(int i = 16; i < 23; i++) {
        Account newAcct = Account("", i, 0, "", "");
        dtree1.insert(newAcct);
    }
    if(tester1.testBalance(dtree1)) {
        cout << "Tree needs to be rebalanced" << endl;
    } else {
        cout << "Tree does not need to be rebalanced" << endl;
    }
    dtree1.dump();
    cout<<endl;
    if(!tester1.testRebalence(dtree1)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << "Visual rep "<<endl;    //vacant nodes are gone
    dtree1.dump();
    cout<<endl;
    cout<<endl;

    cout << "****************************************************" <<endl;
    cout << "Testing insert with vacant places..." << endl;
    dtree.dump();
    cout <<endl;
    Account newAcct = Account("", 8, 0, "", "");
    dtree.insert(newAcct);
    dtree.dump(); //notice 5 was replaced
    cout <<endl; cout <<endl;

    cout << "****************************************************" <<endl;
    cout << "End of Testing..." << endl;

    // Basic UTree tests
    cout << "****************************************************" <<endl;
    cout << "UTree insertion..." << endl;
    UTree utree;
    Account newAcct4 = Account("Joud", 50, 0, "4", "2");
    utree.insert(newAcct4);
    Account newAcct5 = Account("JJ", 57, 0, "4", "2");
    utree.insert(newAcct5);
    Account newAcct9 = Account("CC", 10, 0, "4", "2");
    utree.insert(newAcct9);
    Account newAcct6 = Account("KK", 9, 0, "4", "2");
    utree.insert(newAcct6);
    Account newAcct10 = Account("PP", 30, 0, "4", "2");
    utree.insert(newAcct10);
    Account newAcct8 = Account("LL", 30, 0, "4", "2");
    utree.insert(newAcct8);
    Account newAcct11 = Account("NN", 30, 0, "4", "2");
    utree.insert(newAcct11);
    Account newAcct12 = Account("OO", 30, 0, "4", "2");
    utree.insert(newAcct12);
    utree.dump();
    cout<< endl;
    cout<< endl;

    cout << "****************************************************" <<endl;
    cout << "UTree insertion same username..." << endl;
    Account newAcctj = Account("JJ", 30, 0, "4", "2");
    utree.insert(newAcctj);
    Account newAcctjj = Account("JJ", 370, 0, "4", "2");
    utree.insert(newAcctjj);
    cout << "Visual test: note JJ has 3 DTree nodes..." << endl;
    utree.dump();
    cout<< endl;
    cout<< endl;

    cout << "****************************************************" <<endl;
    cout << "UTree removing..." << endl;
    tester.testUtreeRemove(utree, "JJ", 30);
    cout << "Visual test: note JJ has 2 DTree nodes..." << endl;
    utree.dump();
    cout<< endl;
    cout<< endl;
    cout << "UTree removing when all nodes vacant..." << endl;
    tester.testUtreeRemove(utree, "JJ", 57);
    tester.testUtreeRemove(utree, "JJ", 370);
    cout << "Visual test: note JJ is gone..." << endl;
    utree.dump();
    cout<< endl;
    cout<< endl;

    utree.printUsers();

    UTree someTree;
    cout << "\n\nTesting UTree insertion...";
     if(tester.testBasicUTreeInsert(someTree)) {
         cout << "test passed" << endl;
     } else {
         cout << "test failed" << endl;
     }

     cout << "Resulting UTree:" << endl;
     someTree.dump();
     cout << endl;

    return 0;
}