#include <bits/stdc++.h>
#include<queue>
using namespace std;


mutex msgqMutex;
queue<string> msgQ;

condition_variable trigger;

void mailProcessor()
{
    while(true)
    {
        unique_lock qlock(msgqMutex);
        trigger.wait(qlock, []{return msgQ.size() > 0;});
        cout<<"Processor:"<<msgQ.front()<<endl;
		cout.flush();
        msgQ.pop();
    }
}

void mailGenerator()
{
    vector<string> sampleMails{"hi there", "whats up"};
    for(auto mail: sampleMails)
    {
		cout<<"Generator:"<<mail<<endl;
		cout.flush();
		{
			unique_lock qlock(msgqMutex);
			msgQ.push(mail);
			trigger.notify_one();
		}
		this_thread::sleep_for(std::chrono::milliseconds(5000)); 
    }
}


int main() {
    thread mailGeneratorThread(mailGenerator);
    thread mailProcessorThread(mailProcessor);

    mailProcessorThread.join();
    mailGeneratorThread.join();
    return 0;
}

