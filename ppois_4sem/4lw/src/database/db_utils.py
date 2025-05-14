import sqlite3
from typing import List, Dict, Optional

class StationDB:
    def __init__(self, db_name: str = "metro.db"):
        """Initialize database connection and create stations table if not exists."""
        self.db_name = db_name
        self._create_table()

    def _get_connection(self):
        """Return a new database connection."""
        return sqlite3.connect(self.db_name)

    def _create_table(self):
        """Create stations table if it doesn't exist."""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS stations (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL UNIQUE,
                    line TEXT NOT NULL
                )
            """)
            conn.commit()

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