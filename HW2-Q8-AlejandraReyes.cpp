/* 
8. Company X generally processes orders based on a first come, first serve basis.
Sometimes a client will ask for rush processing and will be awarded a number based on
the urgency. If they pay extra they will receive a 3 priority, if they have a bulk order they
will receive a 2 priority, and if they know someone in the company and ask for a favor
they will receive the highest priority, a 1. Design a system that accepts orders from
clients and processes these orders based on no priority or somewhere on the priority
scale. Show how the system will work for random orders with a random processing time
*/
#include<iostream>
#include<time.h>
using namespace std;

//** QUEUE CLASS ** //
//Implementation of a queue using an array
template<typename dataType>
class queue{
private:
    dataType* array; //pointer to array that holds the queue
    int count; //store number of elements currently in queue
    size_t maxSize; //maximum number of elements that can be stored in the queue 
    int queueFront; //index of element at front of the queue (first element pushed to queue)
    int queueRear; //index of element at the end of the queue (last element pushed to queue)
public:
    queue<dataType> (){
        maxSize = 100; //set the maximum size of the queue
        queueFront = 0; //the top of the queue is the first element in the array
        queueRear = 0;//stores index of next empty spot in the queue
        array = new dataType[maxSize]; //create an array of specified size 
        count = 0; //a queue is initialized with 0 elements
    } //constructor; queue is initialized with a size of 1000

    ~queue(){
        delete[] array; //delete the array containing the queue elements
    }//destructor

    void push(const dataType& newElement); //add newElement to the queue, const makes it immutable and & indicates we are passing a reference so we do not have to copy the element
    dataType front(); //returns first element of the queue
    dataType back(); //returns last element in the queue
    void pop(); //remove front element in queue

    bool full(); //checks if queue is full
    bool empty(); //checks if queue is empty 
};

template<typename dataType>
void queue<dataType>::push(const dataType& newElement){
    if ( !full() ){ //if the queue is not full
        array[queueRear] = newElement; //add the element to the current rear, which is an empty spot
        queueRear++; //advance the rear
        count++; //increment number of elements in the queue
    }
    else cout << "Cannot add elements to a full queue." << endl;

}

template<typename dataType>
dataType queue<dataType>::front(){
    if ( !empty() ) { return array[queueFront];} //if the queue is not empty, return the element at the top
    else { cout << "Cannot return the front of an empty queue." << endl; }
 }

template<typename dataType>
dataType queue<dataType>::back(){
    if ( !empty() ) { return array[queueRear-1]; } //if the queue is not empty, return the element at the back
    else { cout << "Cannot return the back of an empty queue." << endl; }
}

template<typename dataType>
void queue<dataType>::pop(){
     if ( empty() ) { cout << "Cannot pop from an empty queue. " << endl; }
     else {
         count--; //decrement element counter
         queueFront = queueFront + 1; //the new front is the next element in the queue
     }

}

template<typename dataType>
bool queue<dataType>::empty(){
    return ( count == 0); //if the queue has no elements, it is empty
}

template<typename dataType>
bool queue<dataType>::full(){
    return ( count == maxSize );//if number of elements equals the maximum size of the queue, the queue is full
}
// ** END QUEUE CLASS ** //


class Order{
public: 
    //the following variables will be used to determine an orders priority
    bool fastShipping; //this bool represents if someone paid extra to receive a priority bump for their order
    bool bulkOrder; //if number of items is greater than 10, it is a bulk order
    bool favor; //represents if someone asked for a favor from someone in the company

    int numItems; //the number of items in an order, which will be used to determine if it is a bulk order
    int priority = 0; //by default an order has no priority

    Order(){ 
    this->numItems = 1 + rand() % (( 20 + 1) - 1); //set random number of items for a new order
    this->fastShipping = rand()%2; //randomly decide if a customer paid extra 
    this->favor = rand()%2; //randomly decide if a favor was called in 
    if (this->numItems >= 10) { this->bulkOrder = true; } //use numItems in order to determine if it is a bulk order
    else { this->bulkOrder = false; }
    this->priority = this->checkPriority(); //calculate and store the order priority
    }//default constructor, generates a random order

    void printOrder(){
        cout << "Number of items: " << numItems << endl;
        cout << "Priorities: ";
        if (favor == 1) { cout << " favor ";};
        if (bulkOrder == 1) { cout << " bulk order ";}
        if ( fastShipping == 1 ) { cout << " fast shipping ";}
        cout << endl << "Priority: " << priority;
    }//printOrder

    const int checkPriority(){
    //determine the priority of the order (1, 2, 3, or 4)
    //if an order has multiple priority flags, the highest one will determine the priority of the order
    if ( this->favor == 1) { return 1;} //highest priority
    else if ( this->bulkOrder == 1 ) { return 2; } //
    else if ( this->fastShipping == 1 ) { return 3; } //lowest priority
    else return 4; //if none of the above flags were set, the orders will not receive a priority bump in processing
    }//checkPriority
};



class OrderProcessor{
private:
    //In the order processor, use a queue to store orders in a first come first serve basis
    queue<Order*> priority1Orders;
    queue<Order*> priority2Orders;
    queue<Order*> priority3Orders;
    queue<Order*> regularOrders;

public:
    OrderProcessor() {} //default constructor, no orders

    void ProcessOrder(Order *order){
        //this function adds an order to the appropriate queue based on the order priority
        if ( order->priority == 1) { priority1Orders.push(order); return; } 
        else if ( order->priority == 2) { priority2Orders.push(order); return;}
        else if ( order->priority == 3) { priority3Orders.push(order); return; }
        else { regularOrders.push(order); return; }
    }//given an order, insert it into proper position

    void PrintProcessedOrders(){
        int counter = 1; //number of orders processed
        cout << "*********Processing Orders*********" << endl;
        while ( priority1Orders.empty() != 1 ) //while there are orders of priority 1 to process
        {
            cout << "=====ORDER #" << counter << "=====" << endl; 
            Order *curr = priority1Orders.front();
            curr->printOrder();//print out the order at the top of this queue
            priority1Orders.pop(); //pop the order that was printed
            cout << endl <<  "=========================" << endl;
            counter++; //an order was processed, increment the count
        }
        while ( priority2Orders.empty() != 1 ) //while there are orders of priority 2 to process
        {
            cout << "=====ORDER #" << counter << "=====" << endl; 
            Order *curr = priority2Orders.front();
            curr->printOrder();//print out the order at the top of this queue
            priority2Orders.pop(); //pop the order that was printed
            cout << endl <<  "=========================" << endl;
            counter++;//an order was processed, increment the count
        }
        while ( priority3Orders.empty() != 1 ) //while there are orders of priority 3 to process
        {
            cout << "=====ORDER #" << counter << "=====" << endl;;
            Order *curr = priority3Orders.front();
            curr->printOrder();//print out the order at the top of this queue
            priority3Orders.pop();//pop the order that was printed
            cout << endl <<  "=========================" << endl;
            counter++;
        }
        while ( regularOrders.empty() != 1 )//while there are orders to proccess with no priority
        {
            cout << "=====ORDER #" << counter << "=====" << endl;;
            Order *curr = regularOrders.front();
            curr->printOrder();//print out the order at the top of this queue
            regularOrders.pop();//pop the order that was printed
            cout << endl <<  "=========================" << endl;
            counter++;
        }
    cout << "*********" << counter-1 << " orders processed*********" << endl;
    }//PrintProcessedOrders

    void generateRandomOrders( int numOrders){
        for (int i = 0; i < numOrders; i++) //loop until we have generated numOrders orders
        {
            Order *newOrder = new Order(); //create a new random order
            ProcessOrder(newOrder); //process the order according to its priority
        }
    }//generateRandomOrders
};

int main(){
    srand(time(NULL));

    //QUEUE TESTING//
    cout << " ***QUEUE TESTING***" << endl;
    queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    cout << q1.front() << endl; 
    cout << q1.back() << endl;
    q1.pop();
    cout << q1.front() << endl;
    q1.pop();
    cout << q1.empty() << endl;
    q1.pop();
    cout << q1.empty() << endl;
    cout << "***END QUEUE TESTING***" << endl;
    /* output should be:
    1 (front)
    3 (back)
    2 (front after popping 1)
    0 (queue is not empty because it still has a 3)
    1 (queue is empty after popping 3)
    */
    //END QUEUE TESTING//

    
    OrderProcessor* randomOrders = new OrderProcessor(); //instantiate an order processor
    randomOrders->generateRandomOrders(100);//generate random orders and process them immediately
    randomOrders->PrintProcessedOrders();//print the orders that were processed
}