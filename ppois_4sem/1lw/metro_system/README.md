# Metro System

A simplified metro model with a command-line interface (CLI), developed in Python. The project simulates metro operations, including stations, trains, schedules, passengers, tickets, and turnstiles.

## Description

The system allows users to:

- Create metro stations and manage their state.
- Create passengers who can buy tickets, pass through turnstiles, and board trains.
- Manage train schedules and their movement.
- Save and load the system’s state between program runs.

The project is developed in accordance with PEP 8 standards, type annotations, and unit tests. It includes UML diagrams to visualize the structure and behavior.

## Available Commands

Upon startup, you will see a prompt to enter commands. The following commands are supported:

- `add_station` — Add a new station (e.g., "Central").
- `create_passenger` — Create a passenger with a specified name and initial amount of money.
- `go_to_station` — Send a passenger to a station.
- `buy_ticket` — Purchase a ticket for the passenger.
- `pass_turnstile` — Pass through the turnstile with a ticket.
- `board_train` — Check the schedule and board a train.
- `save` — Save the current system state to the `metro_state.json` file.
- `load` — Load the system state from the `metro_state.json` file.
- `list_stations` — Display a list of all stations (recommended to add).
- `exit` — Exit the program.
- `help` — Show the list of commands.

### Usage Example:

Введите команду (help для списка): add_station
Введите имя станции: Central
Станция Central добавлена.
Введите команду (help для списка): create_passenger
Введите имя пассажира: Alice
Пассажир Alice создан.
Введите команду (help для списка): go_to_station
Введите имя станции: Central
Alice входит на станцию Central.

## Saving and Loading System State

The program allows saving the system state to a JSON file and loading it from JSON.
Commands:

- `load` — Load the state.
- `save` — Save the state.

## Author

Ivan Kislitsyn, student of group 321702, 2nd year "Artificial Intelligence" course, BSUIR
