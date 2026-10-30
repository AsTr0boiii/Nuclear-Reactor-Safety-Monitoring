#pragma once
#include <string>
#include "sqlite3.h"

class DatabaseManager {

    private:
     
    sqlite3* db;

    public:
    
    DatabaseManager();
    ~DatabaseManager();

    bool connectDatabase();
    void createTables();
    void closeDatabase();

    bool saveEvent(
    
        const std::string& eventType,
        const std::string& description,
        const std::string& severity

    );

    bool saveReactorSnapshot(
    double temperature,
    double pressure,
    double coolantLevel,
    double radiationLevel,
    double powerOutput,
    const std::string& status
);

void viewReactorSnapshots();

    void viewEventLogs();

};