#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Airplane {
protected:
    bool _isBoarding; // Tracks the boarding status

public:
    Airplane() : _isBoarding(false) {} // Default not boarding

    virtual void reserveSeat() = 0;
    virtual bool hasAvailableSeats() const = 0;

    bool isBoarding() const {
        return _isBoarding;
    }

    void startBoarding() {
        _isBoarding = true;
    }

    void stopBoarding() {
        _isBoarding = false;
    }
};

class EconomyClass : public Airplane {
private:
    int economyClassSeats;
public:
    EconomyClass() : Airplane(), economyClassSeats(5) {}

    void reserveSeat() override {
        if (economyClassSeats > 0) {
            economyClassSeats--;
        }
    }

    bool hasAvailableSeats() const override {
        return economyClassSeats > 0;
    }
};

class FirstClass : public Airplane {
private:
    int firstClassSeats;
public:
    FirstClass() : Airplane(), firstClassSeats(5) {}

    void reserveSeat() override {
        if (firstClassSeats > 0) {
            firstClassSeats--;
        }
    }

    bool hasAvailableSeats() const override {
        return firstClassSeats > 0;
    }
};
