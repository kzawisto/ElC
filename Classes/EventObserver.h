/*
 * EventObserver.h
 *
 *  Created on: Oct 18, 2015
 *      Author: krystian892
 */


#pragma once
#include<string>
#include<vector>
using namespace std;
class MyEvent{

public:
  MyEvent(std::string str, int val) :str(str), val(val){
  }
    string str;
  int val;
};
class Receiver{
public:
   virtual void sendEvent(MyEvent & e){
   }
   virtual ~Receiver(){};
};
class EventObserver : public Receiver
{
vector<Receiver*> receivers;
public:

    EventObserver();
    void addReceiver(Receiver * receiver){
      receivers.push_back(receiver);
    }
    void sendEvent(MyEvent & e){
      for(Receiver * receiver: receivers)
	receiver->sendEvent(e);
   }
   static EventObserver& get(){
      static EventObserver instance;
      return instance;
   }
};

class Observable{
   virtual void sendEvent(MyEvent & e){
   }
   virtual ~Observable(){};

};


