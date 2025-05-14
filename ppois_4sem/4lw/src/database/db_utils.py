import sqlite3
from typing import List, Dict, Optional

class StationDB:
    def __init__(self, db_name: str = "metro.db"):
        """Initialize database connection and create stations table if not exists."""
        self.db_name = db_name
        self._create_table()
        self._init_tariffs()

    def _get_connection(self):
        """Return a new database connection."""
        return sqlite3.connect(self.db_name)

    def _create_table(self):
        with self._get_connection() as conn:
            cursor = conn.cursor()
            
            # Stations table
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS stations (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL UNIQUE,
                    line TEXT NOT NULL
                )
            """)
            
            # Passengers table
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS passengers (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    balance REAL DEFAULT 0.0,
                    tariff_id INTEGER DEFAULT 1,
                    station_id INTEGER NOT NULL,
                    is_active BOOLEAN DEFAULT TRUE,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    FOREIGN KEY(station_id) REFERENCES stations(id),
                    FOREIGN KEY(tariff_id) REFERENCES tariffs(id)
                )
            """)
            
            # Tariffs table
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS tariffs (
                    id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL UNIQUE,
                    price REAL NOT NULL
                )
            """)
            
            conn.commit()
    def _init_tariffs(self):
        default_tariffs = [
            (1, "Basic", 2.50),
            (2, "Premium", 5.00),
            (3, "Student", 1.75)
        ]
        
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.executemany(
                """INSERT OR IGNORE INTO tariffs (id, name, price)
                   VALUES (?, ?, ?)""",
                default_tariffs
            )
            conn.commit()

    # Passenger-related methods
    def add_passenger(self, name: str, station_id: int) -> bool:
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute(
                    """INSERT INTO passengers (name, station_id)
                       VALUES (?, ?)""",
                    (name, station_id)
                )
                conn.commit()
                return True
        except sqlite3.IntegrityError:
            return False

    def get_passenger(self, passenger_id: int) -> Optional[Dict]:
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("""
                SELECT p.id, p.name, p.balance, t.name as tariff, 
                       p.station_id, p.is_active, p.created_at
                FROM passengers p
                JOIN tariffs t ON p.tariff_id = t.id
                WHERE p.id = ?
            """, (passenger_id,))
            result = cursor.fetchone()
            
            if result:
                return {
                    "id": result[0],
                    "name": result[1],
                    "balance": result[2],
                    "tariff": result[3],
                    "station_id": result[4],
                    "is_active": bool(result[5]),
                    "created_at": result[6]
                }
            return None

    def get_passengers_by_station(self, station_id: int) -> List[Dict]:
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("""
                SELECT p.id, p.name, p.balance, t.name as tariff, 
                       p.is_active, p.created_at
                FROM passengers p
                JOIN tariffs t ON p.tariff_id = t.id
                WHERE p.station_id = ?
                ORDER BY p.created_at DESC
            """, (station_id,))
            return [{
                "id": row[0],
                "name": row[1],
                "balance": row[2],
                "tariff": row[3],
                "is_active": bool(row[4]),
                "created_at": row[5]
            } for row in cursor.fetchall()]

    def update_passenger_balance(self, passenger_id: int, amount: float) -> bool:
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE passengers 
                    SET balance = balance + ? 
                    WHERE id = ?
                """, (amount, passenger_id))
                conn.commit()
                return cursor.rowcount > 0
        except sqlite3.Error:
            return False

    def update_passenger_tariff(self, passenger_id: int, tariff_id: int) -> bool:
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE passengers 
                    SET tariff_id = ? 
                    WHERE id = ?
                """, (tariff_id, passenger_id))
                conn.commit()
                return cursor.rowcount > 0
        except sqlite3.Error:
            return False

    def toggle_passenger_status(self, passenger_id: int) -> bool:
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE passengers 
                    SET is_active = NOT is_active 
                    WHERE id = ?
                """, (passenger_id,))
                conn.commit()
                return cursor.rowcount > 0
        except sqlite3.Error:
            return False

    def get_tariffs(self) -> List[Dict]:
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT id, name, price FROM tariffs")
            return [{
                "id": row[0],
                "name": row[1],
                "price": row[2]
            } for row in cursor.fetchall()]












    def add_station(self, name: str, line: str) -> bool:
        """Add a new station to the database."""
        print('hello')
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO stations (name, line) VALUES (?, ?)",
                    (name, line)
                )
                conn.commit()
                return True
        except sqlite3.IntegrityError:
            return False

    def get_station(self, station_id: int) -> Optional[Dict]:
        """Retrieve a station by its ID."""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute(
                "SELECT id, name, line FROM stations WHERE id = ?",
                (station_id,)
            )
            result = cursor.fetchone()
            if result:
                return {"id": result[0], "name": result[1], "line": result[2]}
            return None

    def get_all_stations(self) -> List[Dict]:
        """Retrieve all stations."""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT id, name, line FROM stations")
            results = cursor.fetchall()
            return [{"id": r[0], "name": r[1], "line": r[2]} for r in results]

    def update_station(self, station_id: int, name: Optional[str] = None, line: Optional[str] = None) -> bool:
        """Update station details."""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                updates = []
                values = []
                
                if name:
                    updates.append("name = ?")
                    values.append(name)
                if line:
                    updates.append("line = ?")
                    values.append(line)
                
                if not updates:
                    return False
                
                values.append(station_id)
                query = f"UPDATE stations SET {', '.join(updates)} WHERE id = ?"
                cursor.execute(query, values)
                conn.commit()
                return cursor.rowcount > 0
        except sqlite3.IntegrityError:
            return False

    def delete_station(self, station_id: int) -> bool:
        """Delete a station by its ID."""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("DELETE FROM stations WHERE id = ?", (station_id,))
            conn.commit()
            return cursor.rowcount > 0