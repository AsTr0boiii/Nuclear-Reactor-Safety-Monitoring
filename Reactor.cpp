#include <iostream>
#include "Reactor.h"
using namespace std;


// ========== ReactorComponent fucntions ==========

ReactorComponent::ReactorComponent () {
    componentName = "Umknown Component";
    working = true;
    
    
}

ReactorComponent::ReactorComponent(string name) {
    componentName = name;
    working = true;
}

void ReactorComponent::displayInfo() {
    cout << "Component: " << componentName << endl;
    cout << "Status: " << (working ? "Working" : "Failed") << endl;


}

void ReactorComponent::failComponent() {
    working = false;
    cout << componentName << " has failed.\n"; 
}

void ReactorComponent::repairComponent() {
    working = true;
    cout << componentName << " has been repaired.\n";

}

bool ReactorComponent::isWorking() {
    return working;
}

string ReactorComponent::getComponentName() {
    return componentName;
}

// ========== CoolantSystem functions ==========

CoolantSystem::CoolantSystem() : ReactorComponent("Coolant System") {
    coolantLevel = 80;
    pumpSpeed = 50;
}


void CoolantSystem::increaseCoolant () {
    if(!working) {
        cout << "Coolant System is not working. Repair it first.\n";
        return;
    }
        
    coolantLevel += 10;
    pumpSpeed += 5;

    if(coolantLevel > 100) {
        coolantLevel = 100;
    }

     if(pumpSpeed > 100) {
        pumpSpeed = 100;
     }

     cout << "Coolant flow increased.\n";

}

void CoolantSystem::decreaseCoolant () {

    if(!working) {
        cout << "Coolant System is not working. Repair it first.\n";
        return;
    }

    coolantLevel -= 10;
    pumpSpeed -= 5;

    if(coolantLevel < 0) {
        coolantLevel = 0;
    }

    if(pumpSpeed < 0) {
        pumpSpeed - 0;
    }

    cout << "Coolant flow decreased.\n";
}

void CoolantSystem::displayInfo() {
    cout << "\n----- COOLANT SYSTEM -----\n";
    cout << "Component status: " << (working ? "Working" : "Failed") << endl;
    cout << "Coolant Level: " << coolantLevel << "%" << endl;
    cout << "Pump Speed: " << pumpSpeed << "%" << endl;
}

double CoolantSystem::getCoolantLevel() {

    return coolantLevel;
}

double CoolantSystem::getPumpSpeed() {
    
    return pumpSpeed;
}

// ========== ControlRod functions ==========

ControlRod::ControlRod() : ReactorComponent("Control Rod System") {

    insertionLevel = 0;
}

void ControlRod::insertRods() {

    if(!working) {

        cout << "Control Rod system is not working. Please repair it first.\n";
        return;
    }

    insertionLevel += 10;

    if(insertionLevel > 100) {

        insertionLevel = 100;
    }

    cout << "Control Rods inserted furthur.\n";
    
}

void ControlRod::removeRods() {

    if(!working) {

        cout << "Control Rod system is not working. Please repair it first.\n";
        return;
    }

    if(insertionLevel < 100) {

        insertionLevel = 0;
    }

    cout << "Inertion Rods removed slightly";
}

void ControlRod::emergencyInsert() {

    insertionLevel = 100;

    cout << "Control Rods fully inserted for emergency shutdown.\n";
}

void ControlRod::displayInfo() {

    cout << "\n----- Control Rod -----\n";
    cout << "Component Status: " << (working ? "Working" : "Failed") << endl;
    cout << "Insertion Level: " << insertionLevel << "%" << endl;
}

double ControlRod::getInsertionLevel() {

    return insertionLevel;
}

// ========== Sensor System Functions ==========

Sensor::Sensor() : ReactorComponent("Sensor System") {

    sensorType = "Generic";
    reading = 0;

}

Sensor::Sensor(string type) : ReactorComponent(type + " Sensor") {

    sensorType = type;
    reading = 0;
}

void Sensor::updateReading(double value) {

    if(!working) {

        cout << "Sensor is not working. Reading not updated.\n";
        return;
    }

    reading = value;
}

void Sensor::displayInfo() {

    cout << "\n----- Sensor System -----\n";
    cout << "Sensor Status: " << (working ? "Failed" : "Working") << endl;
    cout << "Sensor Type: " << sensorType << endl;
    cout << "Current Reading: " << reading << "%" << endl;
}

string Sensor::getSensorType() {

    return sensorType;
}

double Sensor::getReading() {

    return reading;
}

// ========== Reactor Functions ==========

Reactor::Reactor() 
: temperatureSensor("Temperature"),
  pressureSensor("Pressure"),
  radiationSensor("Radiation") {

    reactorId = 1;
    reactorName = "Alpha Reactor";
    reactorType = "Research Reactor";

    temperature = 40;
    pressure = 30;
    radiationLevel = 5;
    powerOutput = 0;

    status = "Shutdown";
    running = false;

    updateSensors();

  }

  double Reactor::getCoolantLevel() {
    return coolantSystem.getCoolantLevel();
}


void Reactor::startReactor() {

    if(running) {
        
        cout << "Reactor is already running.\n";
        return;
    }

    running = true;
    powerOutput = 20;
    temperature = 45;
    pressure = 30;
    radiationLevel = 6;

    updateStatus();
    updateSensors();

    cout << "Reactor started sucessfuly.\n";

}

void Reactor::increasePower() {

    if(!running) {
        cout << "Reactor is not running. Start the Reactor first.\n";
        return;
    }

    powerOutput += 10;
    temperature += 6;
    pressure =+ 4;
    radiationLevel += 1;

    limitValues();
    updateStatus();
    updateSensors();

    cout << "Power output increased.\n";

}

void Reactor::decreasePower() {

    if(!running) {

        cout << "Reactor is not running. Start the reactor first.\n";
        return;
    }

    powerOutput -= 10;
    temperature -= 3;
    pressure -= 2;
    radiationLevel -= 1;

    limitValues();
    updateStatus();
    updateSensors();

    cout << "Power output deacreased.\n";
}

void Reactor::increaseCoolant() {

    if(!running) {

        cout << "Reactor is not running. Start the reactor first.\n";
        return;
    }

    coolantSystem.increaseCoolant();

    temperature -= 6;
    pressure -= 2;

    limitValues();
    updateStatus();
    updateSensors();

}

void Reactor::decreaseCoolant() {

     if(!running) {

        cout << "Reactor is not running. Start the reactor first.\n";
        return;
    }

    coolantSystem.decreaseCoolant();

    temperature += 4;
    pressure += 2;

    limitValues();
    updateStatus();
    updateSensors();

}

void Reactor::insertControlRods() {

     if(!running) {

        cout << "Reactor is not running. Start the reactor first.\n";
        return;
    }

    controlRod.insertRods();

    powerOutput -= 10;
    temperature -= 4;
    radiationLevel -= 1;

    limitValues();
    updateStatus();
    updateSensors();

}

void Reactor::removeControlRods() {

     if(!running) {

        cout << "Reactor is not running. Start the reactor first.\n";
        return;
    }

    controlRod.removeRods();

    powerOutput += 5;
    temperature += 3;
    radiationLevel += 1;

    limitValues();
    updateStatus();
    updateSensors();

}

void Reactor::runSimulationCycle() {

     if(!running) {

        cout << "Reactor is not running. Start the reactor first.\n";
        return;
    }

    cout << "\nRunning one simulation cycle........\n";

    // A fictional simplified simulation logic

    temperature += powerOutput / 20;
    pressure += temperature / 50;
    radiationLevel += powerOutput / 100;

    // coolant will reduce temperature if the system is working

    if(coolantSystem.isWorking()) {

        temperature -= coolantSystem.getCoolantLevel() / 30;

    }

    else {
        temperature += 5;
        cout << "Warning: Coolant system failiure is increasing temperature.\n";

    }

    // control rods reduce power if inserted

    powerOutput -= controlRod.getInsertionLevel() / 40;

    limitValues();
    updateStatus();
    updateSensors();

    cout << "Simulation cycle completed...\n";

}

void Reactor::emergencyShutdown() {

     if(!running) {

        cout << "Reactor is already shutdown.\n";
        return;
    }

    running = false;
    powerOutput = 0;

    controlRod.emergencyInsert();

    temperature -= 15;
    pressure -= 10;
    radiationLevel -= 2;

    limitValues();

    status = "Shutdown";
    updateSensors();

    cout << "Emergency shutdown completed....\n";

}

void Reactor::viewPublicStatus() {

    cout << "\n========== Public Reactor Status ==========\n";
    cout << "Reactor Name: " << reactorName << endl;
    cout << "Reactor Type: " << reactorType << endl;
    cout << "Current Status: " << status << endl;
    cout << "Running: " << (running ? "Yes" : "no") << endl;

}

void Reactor::viewDetailedStatus() {

    cout << "\n========== Detailed Reactor Status ==========\n";
    cout << "Reactor ID: " << reactorId << endl;
    cout << "Reactor Name: " << reactorName << endl;
    cout << "Reactor Type: " << reactorType << endl;
    cout << "Temperature: " << temperature << endl;
    cout << "Pressure: " << pressure << endl;
    cout << "Radiation Level: " << radiationLevel << endl;
    cout << "Power Output: " << powerOutput << "%" << endl;
    cout << "Status: " << status << endl;
    cout << "Running: " << (running ? "Yes" : "No") << endl;
}

void Reactor::viewComponentStatus() {

    cout << "\n========== Componenet Status ==========\n";

    coolantSystem.displayInfo();
    controlRod.displayInfo();

    temperatureSensor.displayInfo();
    pressureSensor.displayInfo();
    radiationSensor.displayInfo();

}

// ========== Private Helper Functions ==========

void Reactor::updateStatus() {

    if(!running) {

        status = "Shutdown";
        return;
    }

    if(temperature >= 90 || pressure >= 90 || radiationLevel >= 80) {

        status = "Critical";
    }

    else if (temperature >= 70 || pressure >= 70 || coolantSystem.getCoolantLevel() <= 30) {
        status = "Warning";

    }

    else {
        status = "Stable";
    }

}

void Reactor::limitValues() {

    if(temperature < 0) temperature = 0;
    if(temperature > 100) temperature = 100;

    if(pressure < 0) pressure = 0;
    if(pressure > 100) pressure = 100;

    if(radiationLevel < 0) radiationLevel = 0;
    if(radiationLevel > 100) radiationLevel = 100;

    if(powerOutput < 0) powerOutput = 0;
    if(powerOutput > 100) powerOutput = 100;

}

void Reactor::updateSensors() {

    temperatureSensor.updateReading(temperature);
    pressureSensor.updateReading(pressure);
    radiationSensor.updateReading(radiationLevel);

}

// ========== Getter Functions ==========

int Reactor::getReactorId() {

    return reactorId;
}

string Reactor::getReactorName() {

    return reactorName;
}

string Reactor::getReactorType() {

    return reactorType;
}

double Reactor::getTemperature() {

    return temperature;
}

double Reactor::getPressure() {

    return pressure;
}

double Reactor::getRadiationLevel() {

    return radiationLevel;
}

double Reactor::getPowerOutput() {

    return powerOutput;
}

string Reactor::getStatus() {

    return status;
}

bool Reactor::isRunning() {

    return running;
}