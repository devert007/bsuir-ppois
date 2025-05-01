import sqlite3

class Database:
    def __init__(self, db_name="notes.db"):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.create_template_db()

    def __del__(self):
        self.conn.close()

    def create_template_db(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS notes (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                fio TEXT NOT NULL,
                address TEXT NOT NULL,
                date_birth TEXT NOT NULL,
                getting_date TEXT NOT NULL,
                fio_doctor TEXT NOT NULL,
                conclusion TEXT NOT NULL
            )
        ''')
        self.conn.commit()

    def load_from_db(self):
        self.cursor.execute("SELECT fio, address, date_birth, getting_date, fio_doctor, conclusion FROM notes")
        db_notes = self.cursor.fetchall()
        return [
            {
                "fio": note[0],
                "address": note[1],
                "date_birth": note[2],
                "getting_date": note[3],
                "fio_doctor": note[4],
                "conclusion": note[5]
            } for note in db_notes
        ]

    def insert_note(self, note):
        self.cursor.execute('''
            INSERT INTO notes (fio, address, date_birth, getting_date, fio_doctor, conclusion)
            VALUES (?, ?, ?, ?, ?, ?)
        ''', (note["fio"], note["address"], note["date_birth"], note["getting_date"], note["fio_doctor"], note["conclusion"]))
        self.conn.commit()

    def delete_note(self, note):
        self.cursor.execute('''
            DELETE FROM notes 
            WHERE fio = ? AND address = ? AND date_birth = ? AND getting_date = ? AND fio_doctor = ? AND conclusion = ?
        ''', (note["fio"], note["address"], note["date_birth"], note["getting_date"], note["fio_doctor"], note["conclusion"]))
        self.conn.commit()

    def clear_db(self):
        self.cursor.execute("DELETE FROM notes")
        self.conn.commit()

    def get_total_items(self):
        self.cursor.execute("SELECT COUNT(*) FROM notes")
        return self.cursor.fetchone()[0]

    def get_paginated_notes(self, items_per_page, offset):
        self.cursor.execute("""
            SELECT fio, address, date_birth, getting_date, fio_doctor, conclusion 
            FROM notes 
            LIMIT ? OFFSET ?
        """, (items_per_page, offset))
        return self.cursor.fetchall()