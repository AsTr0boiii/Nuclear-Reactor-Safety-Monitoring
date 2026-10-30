#include <iostream>
#include <limits>
#include "Reactor.h"
#include "DatabaseManager.h"

using namespace std;

void saveCurrentReactorState(DatabaseManager& database, Reactor& reactor) {
    database.saveReactorSnapshot(
        reactor.getTemperature(),
        reactor.getPressure(),
        reactor.getCoolantLevel(),
        reactor.getRadiationLevel(),
        reactor.getPowerOutput(),
        reactor.getStatus()
    );
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Reactor reactor;
    DatabaseManager database;

    if (!database.connectDatabase()) {
        cout << "Database connection failed. Program stopped." << endl;
        return 1;
    }

    database.createTables();

    database.saveEvent("SYSTEM", "Nuclear reactor monitoring system launched", "INFO");
    saveCurrentReactorState(database, reactor);

    int choice;

    do {
        cout << "\n======================================" << endl;
        cout << " NUCLEAR REACTOR SAFETY MONITORING" << endl;
        cout << " Fictional Training Simulation System" << endl;
        cout << "======================================" << endl;

        cout << "1. Start Reactor" << endl;
        cout << "2. Increase Power" << endl;
        cout << "3. Decrease Power" << endl;
        cout << "4. Increase Coolant" << endl;
        cout << "5. Decrease Coolant" << endl;
        cout << "6. Insert Control Rods" << endl;
        cout << "7. Remove Control Rods" << endl;
        cout << "8. Run Simulation Cycle" << endl;
        cout << "9. Emergency Shutdown" << endl;
        cout << "10. View Public Reactor Status" << endl;
        cout << "11. View Detailed Reactor Status" << endl;
        cout << "12. View Component Status" << endl;
        cout << "13. View Database Event Logs" << endl;
        cout << "14. View Database Reactor Snapshots" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            reactor.startReactor();
            database.saveEvent("START", "Reactor started by operator", "INFO");
            saveCurrentReactorState(database, reactor);
            break;

        case 2:
            reactor.increasePower();
            database.saveEvent("POWER_CHANGE", "Power output increased by operator", "LOW");
            saveCurrentReactorState(database, reactor);
            break;

        case 3:
            reactor.decreasePower();
            database.saveEvent("POWER_CHANGE", "Power output decreased by operator", "LOW");
            saveCurrentReactorState(database, reactor);
            break;

        case 4:
            reactor.increaseCoolant();
            database.saveEvent("COOLANT_CHANGE", "Coolant level increased by operator", "LOW");
            saveCurrentReactorState(database, reactor);
            break;

        case 5:
            reactor.decreaseCoolant();
            database.saveEvent("COOLANT_CHANGE", "Coolant level decreased by operator", "MEDIUM");
            saveCurrentReactorState(database, reactor);
            break;

        case 6:
            reactor.insertControlRods();
            database.saveEvent("CONTROL_ROD", "Control rods inserted", "INFO");
            saveCurrentReactorState(database, reactor);
            break;

        case 7:
            reactor.removeControlRods();
            database.saveEvent("CONTROL_ROD", "Control rods removed", "LOW");
            saveCurrentReactorState(database, reactor);
            break;

        case 8:
            reactor.runSimulationCycle();
            database.saveEvent("SIMULATION", "One simulation cycle completed", "INFO");
            saveCurrentReactorState(database, reactor);
            break;

        case 9:
            reactor.emergencyShutdown();
            database.saveEvent("EMERGENCY", "Emergency shutdown activated", "HIGH");
            saveCurrentReactorState(database, reactor);
            break;

        case 10:
            reactor.viewPublicStatus();
            break;

        case 11:
            reactor.viewDetailedStatus();
            break;

        case 12:
            reactor.viewComponentStatus();
            break;

        case 13:
            cout << "\nEVENT LOGS FROM DATABASE:" << endl;
            database.viewEventLogs();
            break;

        case 14:
            cout << "\nREACTOR SNAPSHOTS FROM DATABASE:" << endl;
            database.viewReactorSnapshots();
            break;

        case 0:
            database.saveEvent("SYSTEM", "System closed by operator", "INFO");
            saveCurrentReactorState(database, reactor);
            cout << "Exiting system..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}