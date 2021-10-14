#include "treeLinked.h"
using namespace std;

int main(){

    //to use different types we need to uncomment appropriate lines
    //and comment out the inappropriate lines
    //also we need to specify the intended type in the file treeLinked.h
    int inputInteger[] = {1,2,0,5,4};
    //int inputInteger[] = {10,5,15,4,6};
    char inputCharacter[] = {'F','B','G','A','D','I','C','E','H'};
    TreeLinked aTree;
    for (int i=0;i<5;i++)
        aTree.insert(inputInteger[i]);
    //aTree.insert(inputCharacter[i]);
    aTree.helper();
    cout << endl;
    cout << "  In Order: "; aTree.inOrder();cout << endl;
    aTree.insert(18);
    cout << "  In Order: "; aTree.inOrder();cout << endl;
    aTree.remove(14);
    cout << "  In Order: "; aTree.inOrder();cout << endl;

    //cout << " Pre Order: "; aTree.preOrder();cout << endl;
    //cout << "Post Order: "; aTree.postOrder();cout << endl;
    //cout << "Finding 14: "; aTree.find(14)->printValue();
    //cout << " Finding I: "; aTree.find('I')->printValue();
    //aTree.remove(15);
    //aTree.remove('I');
    //cout << "After removal, " << endl;
    //cout << "  In Order: "; aTree.inOrder();cout << endl;
    return 0;
}