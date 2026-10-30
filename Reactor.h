#pragma once

#include <string>
using namespace std;

// Base class for reactor parts

class ReactorComponent {
protected:
    string componentName;
    bool working;

public:
    ReactorComponent();
    ReactorComponent(string name);

    virtual void displayInfo();
    void failComponent();
    void repairComponent();

    bool isWorking();
    string getComponentName();
};


// Coolant system class

class CoolantSystem : public ReactorComponent {
private:
    double coolantLevel;
    double pumpSpeed;

public:
    CoolantSystem();

    void increaseCoolant();
    void decreaseCoolant();
    void displayInfo();

    double getCoolantLevel();
    double getPumpSpeed();
};


// Control rod class

class ControlRod : public ReactorComponent {
private:
    double insertionLevel;

public:
    ControlRod();

    void insertRods();
    void removeRods();
    void emergencyInsert();
    void displayInfo();

    double getInsertionLevel();
};


// Sensor class

class Sensor : public ReactorComponent {
private:
    string sensorType;
    double reading;

public:
    Sensor();
    Sensor(string type);

    void updateReading(double value);
    void displayInfo();

    string getSensorType();
    double getReading();
};


// Main Reactor class

class Reactor {
private:
    int reactorId;
    string reactorName;
    string reactorType;

    double temperature;
    double pressure;
    double radiationLevel;
    double powerOutput;

    string status;
    bool running;

    CoolantSystem coolantSystem;
    ControlRod controlRod;

    Sensor temperatureSensor;
    Sensor pressureSensor;
    Sensor radiationSensor;

    void updateStatus();
    void limitValues();
    void updateSensors();

public:
    Reactor();

    void startReactor();
    void increasePower();
    void decreasePower();

    void increaseCoolant();
    void decreaseCoolant();

    void insertControlRods();
    void removeControlRods();

    void runSimulationCycle();
    void emergencyShutdown();

    void viewPublicStatus();
    void viewDetailedStatus();
    void viewComponentStatus();

    int getReactorId();
    string getReactorName();
    string getReactorType();

    double getTemperature();
    double getPressure();
    double getRadiationLevel();
    double getPowerOutput();
    double getCoolantLevel();


    string getStatus();
    bool isRunning();
};