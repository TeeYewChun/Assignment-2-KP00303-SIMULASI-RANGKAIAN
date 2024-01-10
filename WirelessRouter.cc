//Tee Yew Chun BI20110050
//Fong How Yan BI20110070
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class router : public cSimpleModule
{
private:
cMessage *msg;

protected:
virtual void initialize() override;
virtual void handleMessage(cMessage *msg) override;
};

Define_Module(router);

void router::initialize()
{

}

void router::handleMessage(cMessage *msg)
{

cMessage *forwardMsg = new cMessage(msg->getName());

if (msg->getSenderModule() == getParentModule()->getSubmodule("Laptop1")) {

cModule *target = getParentModule()->getSubmodule("Laptop2");
sendDirect(forwardMsg, target, "radioIn");
} else if (msg->getSenderModule() == getParentModule()->getSubmodule("Laptop2")) {

cModule *target = getParentModule()->getSubmodule("Laptop1");
sendDirect(forwardMsg, target, "radioIn");
} else {

EV << "Unexpected message source, deleting the message\n";
delete msg;
delete forwardMsg;
return;
}
}


class laptop : public cSimpleModule
{
protected:
virtual void initialize() override;
virtual void handleMessage(cMessage *msg) override;
};

Define_Module(laptop);

void laptop::initialize()
{
EV << "Laptop initialize" << "\n";
cMessage *msg = new cMessage("Hello");
scheduleAt(simTime() + dblrand(), msg->dup());
EV << "Laptop initialize complete" << "\n";
}

void laptop::handleMessage(cMessage *msg)
{
EV << "Laptop handle message initialize" << "\n";


EV << "Received message: " << msg->getName() << "\n";


if (strcmp(msg->getName(), "Hello") == 0) {
cMessage *responseMsg = new cMessage("Hello I am Tee Yew Chun");
cModule *router = getParentModule()->getSubmodule("Router");
sendDirect(responseMsg, router, "radioIn");
}else if (strcmp(msg->getName(), "Hello I am Tee Yew Chun") == 0) {
cMessage *responseMsg = new cMessage("Hello I am Fong How Yan");
cModule *router = getParentModule()->getSubmodule("Router");
sendDirect(responseMsg, router, "radioIn");
}else if (strcmp(msg->getName(), "Hello I am Fong How Yan") == 0) {
cMessage *responseMsg = new cMessage("Hello I am Tee Yew Chun");
cModule *router = getParentModule()->getSubmodule("Router");
sendDirect(responseMsg, router, "radioIn");
}

else {
cMessage *responseMsg = new cMessage("Something Wrong");
cModule *router = getParentModule()->getSubmodule("Router");
sendDirect(responseMsg, router, "radioIn");
}
}
