import json
import xml.etree.ElementTree as ET
from xml.dom import minidom
from datetime import datetime
from tkinter import messagebox, filedialog
import tkinter as tk
from database import Database
class Controller:
    def __init__(self, ui):
        self.ui = ui
        self.db = Database()  
        self.notes = self.db.load_from_db()
        self.update_home_displays()
        print('app is started')

    def create_note(self):
        fio = self.ui.create_fio_entry.get().strip()
        adress = self.ui.create_address_entry.get().strip()
        date_birth = str(self.ui.create_cal_date_birth.get_date())
        getting_date = str(self.ui.create_cal_getting_date.get_date())
        fio_doctor = self.ui.create_fio_doctor_entry.get().strip()
        conclusion = self.ui.create_conclusion_entry.get().strip()
        all_info = [fio, adress, date_birth, getting_date, fio_doctor, conclusion]
        
        if not all(all_info):
            messagebox.showerror("Ошибка", "Заполните все поля!")
            return
        birth_date = datetime.strptime(date_birth, '%d.%m.%Y')
        get_date = datetime.strptime(getting_date, '%d.%m.%Y')
        if birth_date >= get_date:
            messagebox.showerror("Ошибка", "Дата рождения должна быть раньше даты приема!")
            return
        new_note = {
            "fio": fio,
            "address": adress,
            "date_birth": date_birth,
            "getting_date": getting_date,
            "fio_doctor": fio_doctor,
            "conclusion": conclusion
        }
        self.db.insert_note(new_note)
        self.notes.append(new_note)
        print("запись создана!")
        self.update_home_displays()

    def delete_note(self):
        notes_to_delete = self.search_note(self.ui.delete_field.get().strip())
        if notes_to_delete is None:
            return
        initial_count = len(self.notes)
        for note in notes_to_delete:
            self.db.delete_note(note)
        self.notes = self.db.load_from_db()
        deleted_count = initial_count - len(self.notes)
        if deleted_count > 0:
            messagebox.showinfo("Удаление успешно завершено", f"Удалено записей: {deleted_count}")
            self.update_home_displays()
        else:
            messagebox.showinfo("Нет успешно", "Записи по заданным критериям не найдены")
        self.ui.delete_field.delete(0, tk.END)

    def search_note(self, to_search=""):
        to_search = to_search.strip() if to_search else self.ui.search_field.get().strip()
        if not to_search:
            messagebox.showerror("Ошибка", "Заполните поле для поиска!")
            return
        all_find_result = []
        to_compare_str = ["fio", "address", "date_birth", "getting_date", "fio_doctor"]
        for note in self.notes:
            for field in to_compare_str:
                if to_search.lower() in note[field].lower() and note not in all_find_result:
                    all_find_result.append(note)
        if not all_find_result:
            messagebox.showinfo("Не успешно", "Записи по заданным критериям не найдены")
            return
        for item in self.ui.search_table.get_children():
            self.ui.search_table.delete(item)
        for note in all_find_result:
            self.ui.search_table.insert("", tk.END, values=(note["fio"], note["address"], note["date_birth"],
                                                            note["getting_date"], note["fio_doctor"], note["conclusion"]))
        return all_find_result

    def clear_db(self):
        try:
            self.db.clear_db()
            self.notes.clear()
            self.ui.current_page = 1
            self.update_home_displays()
        except Exception as e:
            print(f"Error clearing database: {e}")
            messagebox.showerror("Ошибка", "Ошибка при очистке базы данных")

    def load_state(self):
        file_path = filedialog.askopenfilename(filetypes=[("XML files", "*.xml")])
        if file_path:
            try:
                if messagebox.askyesno("Подтверждение", "Очистить текущую базу данных перед загрузкой?"):
                    self.clear_db()
                tree = ET.parse(file_path)
                root = tree.getroot()
                for note in root:
                    fio = note.find('fio').text 
                    address = note.find('address').text
                    date_birth = note.find('date_birth').text
                    getting_date = note.find('getting_date').text
                    fio_doctor = note.find('fio_doctor').text
                    conclusion = note.find('conclusion').text
                    new_note = {
                        'fio': fio,
                        'address': address,
                        'date_birth': date_birth,
                        'getting_date': getting_date,
                        'fio_doctor': fio_doctor,
                        'conclusion': conclusion
                    }
                    self.db.insert_note(new_note)
                    if new_note not in self.notes:
                        self.notes.append(new_note)
                self.update_home_displays()
            except Exception as e:
                print(f"Error loading file: {e}")

    def save_state(self):
        root = ET.Element("notes")
        for note in self.notes:
            note_elem = ET.SubElement(root, "note")
            for name, value in note.items():
                elem = ET.SubElement(note_elem, name)
                elem.text = str(value)
        xml_string = ET.tostring(root, encoding='utf-8', method='xml')
        pretty_xml = xml_string.decode('utf-8')
        file_path = filedialog.asksaveasfilename(defaultextension=".xml", filetypes=[("XML files", "*.xml")])
        if file_path:
            try:
                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(pretty_xml)
                print(f"Saved to {file_path}")
            except Exception as e:
                print(f"Error saving file: {e}")

    def update_home_displays(self):
        for item in self.ui.table.get_children():
            self.ui.table.delete(item)
        
        total_items = self.db.get_total_items()
        self.ui.total_pages = (total_items + self.ui.items_per_page - 1) // self.ui.items_per_page
        self.ui.page_label.config(text=f"Страница {self.ui.current_page} из {self.ui.total_pages}")
        if self.ui.current_page > self.ui.total_pages and self.ui.total_pages > 0:
            self.ui.current_page = self.ui.total_pages
        
        start_idx = (self.ui.current_page - 1) * self.ui.items_per_page
        notes = self.db.get_paginated_notes(self.ui.items_per_page, start_idx)
        for note in notes:
            self.ui.table.insert("", tk.END, values=note)

        for item in self.ui.tree.get_children():
            self.ui.tree.delete(item)
        for i, note in enumerate(self.notes):
            note_id = self.ui.tree.insert("", tk.END, text=f"Запись {i + 1}", open=True)
            for key, value in note.items():
                self.ui.tree.insert(note_id, tk.END, text=f"{key}: {value}")

    def update_items_per_page(self):
        try:
            new_value = int(self.ui.items_per_page_var.get())
            if new_value <= 0:
                raise ValueError("Значение должно быть положительным")
            self.ui.items_per_page = new_value
            self.ui.current_page = 1
            self.update_home_displays()
        except ValueError:
            messagebox.showerror("Ошибка", "Введите корректное число (целое положительное)")
            self.ui.items_per_page_var.set(str(self.ui.items_per_page))

    def prev_page(self):
        if self.ui.current_page > 1:
            self.ui.current_page -= 1
            self.update_home_displays()

    def next_page(self):
        if self.ui.current_page < self.ui.total_pages:
            self.ui.current_page += 1
            self.update_home_displays()
    def first_page(self):
        self.ui.current_page = 1
        self.update_home_displays()
    def last_page(self):
        self.ui.current_page = self.ui.total_pages
        self.update_home_displays()