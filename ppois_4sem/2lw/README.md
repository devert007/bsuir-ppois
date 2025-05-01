# Отчет по разработанной системе

## Описание системы

Разработано оконное приложение с использованием Python и библиотеки `tkinter`. Приложение реализует управление массивом записей с использованием шаблона проектирования **Model-View-Controller (MVC)**. Оно включает главное окно и несколько дочерних диалогов, вызываемых через меню или панель инструментов. Данные хранятся в базе данных и могут быть сохранены/загружены в XML-файл. Поддерживается отображение записей в виде таблицы и дерева.

### Основные возможности:
1. **Создание записей**: Ввод данных через диалоговое окно.
2. **Поиск записей**: Поиск по заданным критериям с выводом результатов в отдельном окне.
3. **Удаление записей**: Удаление по условиям с уведомлением пользователя о результате.
4. **Отображение данных**: Таблица и дерево в главном окне.
5. **Сохранение/загрузка**: Работа с XML-файлами (DOM для записи, SAX для чтения) и базой данных.

### Используемые технологии:
- **Язык**: Python
- **Библиотеки**: `tkinter`, `tkcalendar`, `xml.etree.ElementTree`, `xml.dom.minidom`
- **База данных**: Любой тип (реализация через класс `Database`)
- **Шаблон**: MVC

---

## Сценарии демонстрации системы

### 1. Создание записи
- Перейти на вкладку "Создать запись".
- Ввести данные: ФИО, адрес, даты рождения и приема, ФИО врача, заключение.
- Нажать "Создать запись".
- Проверить, что запись отобразилась в таблице и дереве на вкладке "Главная".

### 2. Поиск записи
- Перейти на вкладку "Найти запись".
- Ввести критерий поиска (например, часть ФИО).
- Нажать "Найти запись".
- Убедиться, что результаты отобразились в таблице на этой вкладке.

### 3. Удаление записи
- Перейти на вкладку "Удалить запись".
- Ввести критерий удаления (например, адрес).
- Нажать "Удалить запись".
- Проверить сообщение о количестве удаленных записей и обновление данных на "Главной".

### 4. Сохранение в XML
- На вкладке "Главная" нажать "Скачать XML".
- Выбрать путь для сохранения файла.
- Открыть файл и убедиться, что данные записаны в формате XML.

### 5. Загрузка из XML
- На вкладке "Главная" нажать "Загрузить XML".
- Выбрать ранее сохраненный файл.
- Подтвердить очистку базы данных (если требуется).
- Убедиться, что данные загрузились и отобразились.

### 6. Переключение страниц
- На вкладке "Главная" использовать кнопки "Предыдущая" и "Следующая" для навигации по страницам таблицы (при большом количестве записей).

---

## Краткое описание функций

- `__init__`: Инициализирует приложение, создает главное окно, подключает базу данных и запускает главный цикл.
- `createMenu`: Создает вкладки (Notebook) для главного окна: "Главная", "Создать запись", "Удалить запись", "Найти запись".
- `createNote`: Создает новую запись, проверяет корректность данных и добавляет ее в базу и массив.
- `deleteNote`: Удаляет записи по заданному критерию, обновляет данные и выводит сообщение о результате.
- `searchNote`: Выполняет поиск записей по критерию, отображает результаты в таблице.
- `clear_db`: Очищает базу данных и массив записей.
- `load_state`: Загружает данные из XML-файла в базу и массив.
- `save_state`: Сохраняет массив записей в XML-файл.
- `setup_create_page`: Настраивает вкладку для создания записи с полями ввода и кнопкой.
- `setup_delete_page`: Настраивает вкладку для удаления с полем ввода и кнопкой.
- `setup_search_page`: Настраивает вкладку для поиска с полем ввода и таблицей результатов.
- `setup_home_page`: Настраивает главную вкладку с таблицей, деревом и кнопками управления.
- `update_home_displays`: Обновляет отображение таблицы и дерева на главной вкладке.
- `prev_page`: Переключает таблицу на предыдущую страницу.
- `next_page`: Переключает таблицу на следующую страницу.

---

## Листинг кода

```python
import tkinter as tk
from tkcalendar import Calendar
from tkinter import ttk, messagebox, filedialog
import json
import xml.etree.ElementTree as ET
from xml.dom import minidom
from datetime import datetime
from database import Database  

class App:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title('app')
        self.root.geometry("1200x700")
        self.db = Database()
        self.notes = self.db.load_from_db()
        self.createMenu()
        self.root.mainloop()
        print('app is started')

    def createMenu(self):
        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(expand=True, fill="both", padx=10, pady=10)
        self.home_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.home_frame, text="Главная")
        self.setup_home_page()
        self.create_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.create_frame, text="Создать запись")
        self.setup_create_page()
        self.delete_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.delete_frame, text="Удалить запись")
        self.setup_delete_page()
        self.search_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.search_frame, text="Найти запись")
        self.setup_search_page()

    def createNote(self):
        fio = self.create_fio_entry.get().strip()
        adress = self.create_address_entry.get().strip()
        date_birth = str(self.create_cal_date_birth.get_date())
        getting_date = str(self.create_cal_getting_date.get_date())
        fio_doctor = self.create_fio_doctor_entry.get().strip()
        conclusion = self.create_conclusion_entry.get().strip()
        all_info = [fio, adress, date_birth, getting_date, fio_doctor, conclusion]
        if not all(all_info):
            messagebox.showerror("Ошибка", "Заполните все поля!")
            return
        birth_date = datetime.strptime(date_birth, '%d.%m.%Y')
        get_date = datetime.strptime(getting_date, '%d.%m.%Y')
        if birth_date >= get_date:
            messagebox.showerror("Ошибка", "Дата рождения должна быть раньше даты приема!")
            return
        newNote = {
            "fio": fio,
            "address": adress,
            "date_birth": date_birth,
            "getting_date": getting_date,
            "fio_doctor": fio_doctor,
            "conclusion": conclusion
        }
        self.db.insert_note(newNote) 
        self.notes.append(newNote)
        print("запись создана!")
        self.update_home_displays()

    def deleteNote(self):
        notes_to_delete = self.searchNote(self.delete_field.get().strip())    
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
        self.delete_field.delete(0, tk.END)

    def searchNote(self, to_search=""):
        to_search = to_search.strip() if to_search else self.search_field.get().strip()
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
        for item in self.search_table.get_children():
            self.search_table.delete(item)
        for note in all_find_result:
            self.search_table.insert("", tk.END, values=(note["fio"], note["address"], note["date_birth"],
                                                        note["getting_date"], note["fio_doctor"], note["conclusion"]))
        return all_find_result

    def clear_db(self):
        try:
            self.db.clear_db()
            self.notes.clear()
            self.current_page = 1
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

    def setup_create_page(self):
        self.create_fio_entry = tk.Entry(self.create_frame, width=30)
        self.create_address_entry = tk.Entry(self.create_frame, width=30)
        self.create_fio_doctor_entry = tk.Entry(self.create_frame, width=30)
        self.create_conclusion_entry = tk.Entry(self.create_frame, width=30)
        self.create_cal_date_birth = Calendar(self.create_frame, selectmode="day", year=2025, month=3, day=15, locale='ru_RU', date_pattern='dd.MM.yyyy')
        self.create_cal_getting_date = Calendar(self.create_frame, selectmode="day", year=2025, month=3, day=15, locale='ru_RU', date_pattern='dd.MM.yyyy')
        fields = [
            ("ФИО:", self.create_fio_entry),
            ("Адрес прописки:", self.create_address_entry),
            ("Дата рождения:", self.create_cal_date_birth),
            ("Дата приема:", self.create_cal_getting_date),
            ("ФИО врача:", self.create_fio_doctor_entry),
            ("Заключение:", self.create_conclusion_entry)
        ]
        for label_text, entry in fields:
            tk.Label(self.create_frame, text=label_text).pack(pady=1)
            entry.pack(pady=3)
        tk.Button(self.create_frame, text="Создать запись", command=self.createNote).pack(pady=4)

    def setup_delete_page(self):
        self.delete_field = tk.Entry(self.delete_frame, width=30)
        tk.Label(self.delete_frame, text="Введите одно из данных для удаления (достаточно одного поля):").pack(pady=2)
        tk.Label(self.delete_frame, text="").pack(pady=2)
        self.delete_field.pack(pady=4)
        tk.Button(self.delete_frame, text="Удалить запись", command=self.deleteNote).pack(pady=10)

    def setup_search_page(self):
        self.search_field = tk.Entry(self.search_frame, width=30)
        tk.Label(self.search_frame, text="Введите данные для поиска (достаточно одного поля):").pack(pady=2)
        self.search_field.pack(pady=4)
        tk.Button(self.search_frame, text="Найти запись", command=self.searchNote).pack(pady=10)
        self.search_table = ttk.Treeview(self.search_frame, columns=("ФИО пациента", "Адрес прописки", "Дата рождения", "Дата приема", "ФИО врача", "Заключение"), show="headings")
        self.search_table.heading("ФИО пациента", text="ФИО пациента")
        self.search_table.heading("Адрес прописки", text="Адрес прописки")
        self.search_table.heading("Дата рождения", text="Дата рождения")
        self.search_table.heading("Дата приема", text="Дата приема")
        self.search_table.heading("ФИО врача", text="ФИО врача")
        self.search_table.heading("Заключение", text="Заключение")
        self.search_table.pack(pady=4, fill="both", expand=True)

    def setup_home_page(self):
        self.current_page = 1
        self.items_per_page = 5
        self.total_pages = 0
        tk.Button(self.home_frame, text="Скачать xml", command=self.save_state).pack(pady=4)
        tk.Button(self.home_frame, text="Загрузить xml", command=self.load_state).pack(pady=4)
        self.table = ttk.Treeview(self.home_frame, columns=("ФИО пациента", "Адрес прописки", "Дата рождения", "Дата приема", "ФИО врача", "Заключение"), show="headings")
        self.table.heading("ФИО пациента", text="ФИО пациента")
        self.table.heading("Адрес прописки", text="Адрес прописки")
        self.table.heading("Дата рождения", text="Дата рождения")
        self.table.heading("Дата приема", text="Дата приема")
        self.table.heading("ФИО врача", text="ФИО врача")
        self.table.heading("Заключение", text="Заключение")
        self.table.pack(pady=4, fill="both", expand=True)
        self.pagination_frame = ttk.Frame(self.home_frame)
        self.pagination_frame.pack(pady=10)
        self.prev_button = ttk.Button(self.pagination_frame, text="Предыдущая", command=self.prev_page)
        self.prev_button.grid(row=0, column=0, padx=5)
        self.page_label = ttk.Label(self.pagination_frame, text=f"Страница {self.current_page} из {self.total_pages}")
        self.page_label.grid(row=0, column=1, padx=5)
        self.next_button = ttk.Button(self.pagination_frame, text="Следующая", command=self.next_page)
        self.next_button.grid(row=0, column=2, padx=5)
        self.tree = ttk.Treeview(self.home_frame)
        self.tree.pack(pady=4, fill="both", expand=True)
        self.update_home_displays()

    def update_home_displays(self):
        for item in self.table.get_children():
            self.table.delete(item)
        total_items = self.db.get_total_items() 
        self.total_pages = (total_items + self.items_per_page - 1) // self.items_per_page
        self.page_label.config(text=f"Страница {self.current_page} из {self.total_pages}")
        if self.current_page > self.total_pages and self.total_pages > 0:
            self.current_page = self.total_pages
        start_idx = (self.current_page - 1) * self.items_per_page
        notes = self.db.get_paginated_notes(self.items_per_page, start_idx)  
        for note in notes:
            self.table.insert("", tk.END, values=note)
        for i, note in enumerate(self.notes):
            note_id = self.tree.insert("", tk.END, text=f"Запись {i + 1}", open=True)
            for key, value in note.items():
                self.tree.insert(note_id, tk.END, text=f"{key}: {value}")

    def prev_page(self):
        if self.current_page > 1:
            self.current_page -= 1
            self.update_home_displays()

    def next_page(self):
        if self.current_page < self.total_pages:
            self.current_page += 1
            self.update_home_displays()

app = App()
```