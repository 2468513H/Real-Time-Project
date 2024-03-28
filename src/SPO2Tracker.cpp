#include "SPO2Tracker.h"

SPO2Tracker::SPO2Tracker(sensor *s) {
    SPO2Tracker::_s = s;
}


// constructor for new class for testing
SPO2Tracker::SPO2Tracker(sensorTest *s) {
    test = true;
    SPO2Tracker::_s = reinterpret_cast<sensor*>(s);
}

void SPO2Tracker::start() {
    // start threads
    threadRunning = true;
    std::thread t1(&SPO2Tracker::tracker, this);
    t1.detach();
}

// set false for thread and terminates it
void SPO2Tracker::stop() {
    threadRunning = false;
}


void SPO2Tracker::ping() {
	std::thread t2(&SPO2Tracker::pingThread, this);
	t2.detach();
}

// thread for pinging SPO2 critical values, 
void SPO2Tracker::pingThread() {
    // start threads for FastDDS
    std::cout<<"Starting alert message"<<std::endl;
    // sends the same message 3 times
    uint32_t tries = 3;

    DevicePublisher alertPub;
    if (!alertPub.init()) {
        std::cerr << "Pub not init'd." << std::endl;
        return;
    }

    alert alertMessage;
    // add more specific message
    alertMessage.message();
    uint32_t pingTries = 0;
    // tries to send a message every 1 second for 3 times
    while (pingTries < tries) {
        if (alertPub.publish(alertMessage)) {
            pingTries++;
        } else {
            std::cout << "Waiting for listener" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void SPO2Tracker::tracker(){
    // thread that checks using determineSymptom() and calls alert if conditions are met
    // use threadRunning to stop the thread
    while (threadRunning) {
        std::string symptom = determineSymptom(getVal());
        if (false) {
            // define out of range behaviour (check if crit low)
            alert();
        }
    }
}

int SPO2Tracker::getVal() {
    // start threads
    return _s->getSpO2();
}