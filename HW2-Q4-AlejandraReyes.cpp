/*
4. Create your own stack functions to do the following:
a. List all the elements in the stack
b. Iterate through the stack and change one of the values based on its position
*/

#include<iostream>
using namespace std;

//** STACK CLASS ** //
//Implementation of a stack using an array
template<typename dataType>
class stack{
private:
    dataType* array; //pointer to array that holds the stack
    size_t maxSize; //size of the stack
    int stackTop; //index of element at the top of the stack (last element pushed to stack)
    int count; //number of elements in the stack (used to print the stack)
public:
    stack<dataType> (int size){
        if ( size <= 0) { cout << "Stack must have a size greater than 0." << endl; }
        else {
            count = 0;
            maxSize = size; //set the size of the stack
            stackTop = 0; //the top of the stack is the first element in the array
            array = new dataType[maxSize]; //create an array of specified size 
        }
    } //constructor; stack must be initialized with a size

    ~stack(){
        delete[] array; //delete the array containing the stack elements
    }//destructor

    void push(const dataType& newElement); //add newElement to the stack, const makes it immutable and & indicates we are passing a reference so we do not have to copy the element
    dataType top(); //returns top element of the stack
    void pop(); //remove top element in stack
    bool full(); //checks if stack is full
    bool empty(); //checks if stack is empty 

    //** PRINT AND REPLACE DECLARATIONS 
    void print(); //print a stack
    void replace(int i, dataType newValue); //replace data at position i in the stack
};

template<typename dataType>
void stack<dataType>::push(const dataType& newElement){
    if ( !full() ){ //if the stack is not full, we can add more elements
        array[stackTop] = newElement; //add the new element to the top of the stack
        stackTop++; //the index in which the element was stored is no longer the top of the stack; stackTop-1 = index of top element in the stack
        count++; //increment the number of elements in the stack
    }//if the stack is not full
    else{
        cout << "Stack is full. No more elements can be added." << endl;
    }//if the stack is full
}

template<typename dataType>
dataType stack<dataType>::top(){
    if ( empty() ) { cout << "Cannot return the top of an empty stack. " << endl;}
    else return array[stackTop-1]; //return element at the top of the stack
}

template<typename dataType>
void stack<dataType>::pop(){
    if ( empty() ) { cout << "Cannot pop from an empty stack. " << endl; }
    else { stackTop--; //remove the top element from the stack 
    count--;//decrese the number of elements in the stack
    }
}

template<typename dataType>
bool stack<dataType>::empty(){
    if ( stackTop == 0) return true; //if the index of the top element is 0, the stack has no elements so it is empty
    else return false; //if the index of the top element is not 0, the stack has at least one element so it is not empty
}

template<typename dataType>
bool stack<dataType>::full(){
    if ( stackTop == maxSize) return true; //if the current top is equal to the max size of the stack, the stack is full
    else return false;
}


//The print and replace functions make use of the fact that our stacks are being stored using arrays.
//We can directly access the data at a certain position in the stack by working with the array that holds the stack elements.
//Print iterates through the array and prints each value
//Replace changes the value of the array at a given position to a given value.
template<typename dataType>
void stack<dataType>::print(){
    for (int i = 0; i < count; i++) //iterate through the array
    {
        cout << array[i] << "  " ; //print each element in the array
    }
    cout << endl;
}

template<typename dataType>
void stack<dataType>::replace(int i, dataType newValue){
    array[i] = newValue; //change the value of the array at the specified position to the new value
}

// ** END STACK CLASS ** //


int main(){

    int count = 20;
    stack<int> s(count); //create a stack

    for (int i = 0; i < count; i++)
    {
        s.push(i); //fill it with numbers from 0 to count-1
    }

    cout << "Stack: ";
    s.print(); //print the stack
    cout << "-----------" << endl;
  
    for (int i = 0; i < count; i++)
    {
        s.replace(i, 9); //replace each stack element with 9
    }
    
    cout << "Replaced all elements with 9 " << endl;  
    s.print(); //print the stack
    cout << "-----------" << endl;

    s.replace(0, 0); //replace the first element with 0
    s.replace(count-1, 0); //repalce the last element with 0

    cout << "Replaced first and last elements with 0 " << endl;
    s.print(); //print the stack
}

