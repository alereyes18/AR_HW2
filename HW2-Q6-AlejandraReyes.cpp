/*
Use a stack to pass in a string and reverse each word in the string. For instance, if you
have the string “When Chuck Norris falls in water, Chuck Norris doesn't get wet. Water
gets Chuck Norris.” It should now say, “nehW kcuhC sirroN sllaf ni retaw, …” That is, it
should take in one string and be a function (or multiple functions) that use a stack (or
multiple stacks) to reverse each word in the sentence. Create a text file that you input of
Chuck Norris jokes and have the program reverse each of the jokes. [Here is some help
if you want ot teg detracts:
https://www.techiedelight.com/reverse-string-without-using-recursion/
*/
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

//** STACK CLASS ** // 
template<typename dataType>
class stack{
private:
    dataType* array; //pointer to array that holds the stack
    size_t maxSize; //size of the stack
    int stackTop; //index of element at the top of the stack (last element pushed to stack)
public:

    stack<dataType> (int size){
        if ( size <= 0) { cout << "Stack must have a size greater than 0." << endl; }
        else {
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
};

template<typename dataType>
void stack<dataType>::push(const dataType& newElement){
    if ( !full() ){
        array[stackTop] = newElement; //add the new element to the top of the stack
        stackTop++; //the index in which the element was stored is no longer the top of the stack; top-1 = index of top element in the stack
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
    else stackTop--; //remove the top element from the stack
}

template<typename dataType>
bool stack<dataType>::empty(){
    if ( stackTop == 0) return true; //if the top of the stack is 0, the stack is empty
    else return false;
}

template<typename dataType>
bool stack<dataType>::full(){
    if ( stackTop == maxSize) return true; //if the current top is equal to the max size of the stack, the stack is full
    else return false;
}
//** END STACK CLASS ** //



void reverseJoke(string& joke){
    cout << "Reversing Joke:   ";
    int length = joke.length(); //store the length of the line
    stack<char> word (length); //declare a stack of characters that will store each word in the line/joke
    bool comma = false; //track when there is a comma in the line
    bool period = false; //track when there is a period in the line
    for (int i = 0; i < joke.length(); i++) //traverse the characters of the line/joke
    {
        if (joke[i] != ' '){ //as long as we do not see a space, store the characters of the line. when we see a space, we have reached the end of the word, and will begin reversing the word by popping the stack
            word.push(joke[i]); //push the character onto the stack
        }
        else{ //if we see a character other than a space
            period = false; //by default, a word does not include a period
            comma = false; //or a comma
            if (word.top() == '.') //if the end of the word includes a period
            {
                word.pop(); //remove the period
                period = true; //set tracker to true, we will use this to add the period at the end of the reversed word
            } 
            if (word.top() == ','){ //if the end of the word includes a comma,
                word.pop();//pop the comma, removing it from the stack
                comma = true; //set tracker to true to add the comma at the end of the reversed word
            }
            while ( word.empty() == false){ //while the word stack has a character, 
                cout << word.top(); //print the character
                word.pop(); //pop the character from the stack
            }
            if (comma == true) { cout << ","; } //if the word included a comma, print it at after the reversed word is printed
            if (period == true) { cout << "."; }//if the word included a period, print it at after the reversed word is printed
            cout << " "; //print a space after a word is printed
        }
    }
    while ( !word.empty() ){ //if the word stack is not empty 
        if ( word.top() == '.') { word.pop();} //if the top of the stack contains a period, remove it
        cout << word.top(); //print each character in the stack
        word.pop(); //until the stack is empty
    }  
    
    
    cout << '.' << endl; //print out a new line at the end of each reversed joke
}

void readJokes(string fileName){
    ifstream file; //declare an ifstream to read line by line from the file
    file.open(fileName); //open the file so we can read its contents
    while ( file.is_open()){ 
        string joke; //declare a string to store each line of the file
        while (getline(file,joke)){ //while there is a line to be read in the file
            cout << "Joke Read:  " << joke << endl;
            reverseJoke(joke); //reverse the line/joke
        }
        file.close(); //when there is no next line, close the file
    }//while the file is open 
}

int main(){
    
    readJokes("CNjokes.txt"); //read jokes to be reversed from a text file
}