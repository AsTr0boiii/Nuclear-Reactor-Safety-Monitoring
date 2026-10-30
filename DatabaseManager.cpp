#include "DatabaseManager.h"
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager() {

    db = nullptr;
}

DatabaseManager::~DatabaseManager() {

   

    closeDatabase();
}

bool DatabaseManager::connectDatabase() {

    int result = sqlite3_open("reactor.db", &db);

    if(result != SQLITE_OK) {

        cout << "Database connection failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    cout << "Database connected sucessfully." << endl;
    return true;

}

void DatabaseManager::createTables() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS event_logs (
            log_id INTEGER PRIMARY KEY AUTOINCREMENT,
            event_type TEXT NOT NULL,
            description TEXT NOT NULL,
            severity TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS reactor_snapshots (
            snapshot_id INTEGER PRIMARY KEY AUTOINCREMENT,
            temperature REAL NOT NULL,
            pressure REAL NOT NULL,
            coolant_level REAL NOT NULL,
            radiation_level REAL NOT NULL,
            power_output REAL NOT NULL,
            status TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    char* errorMessage = nullptr;

    int result = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        cout << "Table creation failed: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    } else {
        cout << "Tables created successfully." << endl;
    }
}


bool DatabaseManager::saveEvent(
    const string& eventType,
    const string& description,
    const string& severity
) {
    const char* sql =
        "INSERT INTO event_logs (event_type, description, severity) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt* statement;

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        cout << "Failed to prepare insert statement." << endl;
        return false;
    }

    sqlite3_bind_text(statement, 1, eventType.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, severity.c_str(), -1, SQLITE_TRANSIENT);

    result = sqlite3_step(statement);

    if (result != SQLITE_DONE) {
        cout << "Failed to save event." << endl;
        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Event saved successfully." << endl;
    return true;
}

bool DatabaseManager::saveReactorSnapshot(
    double temperature,
    double pressure,
    double coolantLevel,
    double radiationLevel,
    double powerOutput,
    const string& status
) {
    const char* sql =
        "INSERT INTO reactor_snapshots "
        "(temperature, pressure, coolant_level, radiation_level, power_output, status) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* statement;

    int result = sqlite3_prepare_v2(db, sql, -1, &statement, nullptr);

    if (result != SQLITE_OK) {
        cout << "Failed to prepare snapshot insert statement." << endl;
        return false;
    }

    sqlite3_bind_double(statement, 1, temperature);
    sqlite3_bind_double(statement, 2, pressure);
    sqlite3_bind_double(statement, 3, coolantLevel);
    sqlite3_bind_double(statement, 4, radiationLevel);
    sqlite3_bind_double(statement, 5, powerOutput);
    sqlite3_bind_text(statement, 6, status.c_str(), -1, SQLITE_TRANSIENT);

    result = sqlite3_step(statement);

    if (result != SQLITE_DONE) {
        cout << "Failed to save reactor snapshot." << endl;
        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Reactor snapshot saved successfully." << endl;
    return true;
}

static int displayEventCallback(void* data, int columnCount, char** columnValues, char** columnNames) {
    cout << "\n-----------------------------" << endl;

    for (int i = 0; i < columnCount; i++) {
        cout << columnNames[i] << ": ";

        if (columnValues[i] != nullptr) {
            cout << columnValues[i] << endl;
        } else {
            cout << "NULL" << endl;
        }
    }

    return 0;
}

void DatabaseManager::viewEventLogs() {
    const char* sql =
        "SELECT * FROM event_logs ORDER BY log_id DESC;";

    char* errorMessage = nullptr;

    int result = sqlite3_exec(db, sql, displayEventCallback, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        cout << "Failed to view event logs: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

void DatabaseManager::viewReactorSnapshots() {
    const char* sql =
        "SELECT * FROM reactor_snapshots ORDER BY snapshot_id DESC;";

    char* errorMessage = nullptr;

    int result = sqlite3_exec(db, sql, displayEventCallback, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        cout << "Failed to view reactor snapshots: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

void DatabaseManager::closeDatabase() {

    if(db != nullptr) {

        sqlite3_close(db);
        db = nullptr;
        cout << "Database closed." << endl;
    }


}