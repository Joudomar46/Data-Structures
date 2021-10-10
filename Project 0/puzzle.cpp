#include "puzzle.h"
//alternative constructor
Puzzle::Puzzle(int size){
    //Test Cases:
    //If the size argument is less than 0, the m_size will be set to zero.
    if (size < 0) {
        size = 0;
    }
    m_table = nullptr; //
    m_size = size; //assign desired size to m_size
    makeMem(); //call makeMem() to allocate the size
    fill(); //call fill() to fill in the dynamic array
}
//destructor
Puzzle::~Puzzle(){
    clear();
}
void Puzzle::clear(){
    //Test Cases:
    //size of m_table = 0, no need to deallocate
    //size of m_table > 0, deallocate the memory
    if (m_size > 0) { //if size is 0
        for (int i = 0; i < m_size; i++) { //iterate through each cell of array pointers
            delete[] m_table[i]; //delete the pointers
            m_table[i] = 0;// set to null/0 VERY IMPORTANT
        }
        delete[] m_table; //delete the double pointer
        m_size = 0; //reset size to 0
    }

}
void Puzzle::makeMem(){
    //Test Cases:
    //if m_size < 0 , puzzle(int size) takes care of this to set to 0
    //if m_size = 0 , invalid entry throw exception
    //if m_size > 0 , allocate memory
    if (m_size != 0) {
        m_table = new char *[m_size]; //m_table point to allocated char array of pointers
        for (int i = 0; i < (m_size); i++) { //go through each cell of pointer array
            m_table[i] = new char[m_size]; //allocated array of columns for each cell
        }
    }//constructor already took care of pointing table to null
}
Puzzle::Puzzle(const Puzzle& rhs){

    m_size = rhs.m_size; //copy size of rhs to new Object puzzle
    makeMem(); //initialize new Object memory to hold rhs
    if (rhs.m_table != nullptr) {
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                if (rhs.m_table[j] != nullptr) //making sure there is something in Object we want to copy
                    m_table[i][j] = rhs.m_table[i][j]; //assign each variable to the correct/new address
            }
        }
    } else {
        m_table = nullptr; //If size 0
    }

}
const Puzzle& Puzzle::operator=(const Puzzle& rhs) {
    //must check against self assignment
    //delete all memory
    //compare address of this pointer to another value
    if (this != &rhs) { //prevent assigning object to it self
        this->clear();
        m_size = rhs.m_size;
        m_table = nullptr; //If size 0
        this->makeMem();
        if (rhs.m_table != nullptr) {
            for (int i = 0; i < m_size; i++) {
                for (int j = 0; j < m_size; j++) {
                    if (rhs.m_table[j] != nullptr) //making sure there is something in Object we want to copy
                        m_table[i][j] = rhs.m_table[i][j]; //assign each variable to the correct/new address
                }
            }
        }
    }
    return *this;
}

void Puzzle::dump(){
    if (m_size > 0){
        int i=0;
        int j=0;
        while(i<m_size){
            while(j<m_size){
                cout << m_table[i][j] << " ";
                j++;
            }
            cout << endl;
            j=0;
            i++;
        }
        cout << endl;
    }
}
void Puzzle::fill(){
    srand(time(NULL));//create the seed value using the current time
    int i=0;
    int j=0;
    while(i<m_size){
        while(j<m_size){
            m_table[i][j] = ALPHA[rand() % MAX];//find a random char from the chars list
            j++;
        }
        j=0;
        i++;
    }
}
