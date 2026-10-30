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