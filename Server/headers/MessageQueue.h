#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <iostream>
#include <queue>
#include <string>
#include <mutex>

class MessageQueue
{
private:
    std::queue<std::string> messageQueue;
    std::mutex mutex_;    
public:
    int enqueue(std::string&);
    std::string dequeue();
    std::string getFirstElement();
    std::string getLastElement();
    int sizes();
    bool isEmpty();

    std::queue<std::string> getQueue();

    MessageQueue();
    ~MessageQueue();
};


#endif