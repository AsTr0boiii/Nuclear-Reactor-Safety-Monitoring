# Nuclear Reactor Safety Monitoring System

## Overview

This project is a C++ based nuclear reactor safety monitoring simulator developed as a learning-focused project.

The simulator models basic reactor behaviour, monitors important reactor conditions, and uses SQLite to store reactor-related data for later inspection.

The main purpose of the project was to practice object-oriented programming, system simulation, database integration, and structured C++ program design.

---

## Project Status

This is an early and relatively simple version of a nuclear reactor safety monitoring simulator.

It was mainly developed to strengthen my understanding of C++ object-oriented programming, simulation logic, system monitoring, and SQLite database integration.

The current implementation uses simplified reactor behaviour and safety logic, so it should be treated as a learning-focused prototype rather than a high-fidelity reactor simulation.

More advanced versions of this project may be developed in the future with improved simulation models, additional reactor systems, better safety logic, more realistic data handling, and an improved monitoring interface.

---

## Features

- Object-oriented C++ design
- Reactor simulation logic
- Reactor component monitoring
- Safety-related condition tracking
- SQLite database integration
- Persistent storage of reactor data
- Database schema for structured records
- Separation of reactor logic and database logic

---

## Technologies Used

- C++
- SQLite
- SQL
- Object-Oriented Programming
- File-based local database storage

---

## Project Structure

```text
Nuclear-Reactor-Safety-Monitoring/
│
├── main.cpp
├── Reactor.cpp
├── Reactor.h
├── DatabaseManager.cpp
├── DatabaseManager.h
├── Schema.sql
├── sqlite3.c
├── sqlite3.h
├── README.md
└── .gitignore
```

### Main Files

`main.cpp`  
Contains the main entry point of the program and controls the execution of the simulation.

`Reactor.cpp` / `Reactor.h`  
Contain the main reactor simulation logic, reactor state, components, and monitoring behaviour.

`DatabaseManager.cpp` / `DatabaseManager.h`  
Handle communication between the C++ program and the SQLite database.

`Schema.sql`  
Contains the SQL structure used to create the required database tables.

`sqlite3.c` / `sqlite3.h`  
SQLite amalgamation source files used by the project for database support.

---

## Database Integration

The project uses SQLite as a local database system.

The database layer is separated from the reactor simulation through the `DatabaseManager` class.

This allows the reactor logic to focus on simulation behaviour while the database manager handles data storage operations.

The project uses `Schema.sql` to define the database structure.

Local generated database files are not included in the repository because they can be recreated from the schema.

---

## Object-Oriented Design

The project uses object-oriented programming to separate different responsibilities.

The `Reactor` class manages the reactor simulation and its internal systems.

The `DatabaseManager` class manages database-related operations.

This separation makes the code easier to understand, maintain, and expand in future versions.

---

## How to Compile

The compilation process depends on the compiler environment and SQLite configuration being used.

The project was developed in C++ with SQLite database integration. The required source files include the reactor simulation, database manager, and SQLite components.

Users should compile the project using a C++ compiler configured with SQLite support.

---

## How to Run

After successful compilation, run the generated executable from the chosen development or terminal environment.

---

## Future Improvements

Possible future versions may include:

- More realistic reactor physics
- Improved temperature and pressure modelling
- Additional reactor subsystems
- More detailed coolant system simulation
- Improved safety and emergency logic
- Better sensor modelling
- More detailed database analytics
- Graphical monitoring interface
- Real-time charts and visualization
- More advanced simulation controls

---

## Disclaimer

This project is an educational software simulation.

It is not intended for the design, operation, safety evaluation, or control of real nuclear facilities.

The reactor behaviour and safety logic used in this project are simplified for programming and learning purposes.

---

## Author

Mohd Nabeel Qureshi

B.Sc. Computer Science with Research
