import tkinter as tk
from tkcalendar import Calendar
from tkinter import ttk, messagebox, filedialog

class UserInterface:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title('app')
        self.root.geometry("1200x700")
        self.controller = None  
        self.create_menu()

    def set_controller(self, controller):
        """Set the controller and bind commands after initialization."""
        self.controller = controller
        self.bind_commands()

    def create_menu(self):
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

    def bind_commands(self):
        """Bind commands to buttons after controller is set."""
        self.save_xml_button.config(command=self.controller.save_state)
        self.load_xml_button.config(command=self.controller.load_state)
        self.prev_button.config(command=self.controller.prev_page)
        self.next_button.config(command=self.controller.next_page)
        self.first_button.config(command=self.controller.first_page)
        self.last_button.config(command=self.controller.last_page)
        self.create_button.config(command=self.controller.create_note)
        self.delete_button.config(command=self.controller.delete_note)
        self.search_button.config(command=self.controller.search_note)
        self.apply_items_button.config(command=self.controller.update_items_per_page)

    def setup_home_page(self):
        self.current_page = 1
        self.items_per_page = 5
        self.total_pages = 0
        self.save_xml_button = tk.Button(self.home_frame, text="Скачать xml")
        self.save_xml_button.pack(pady=4)
        self.load_xml_button = tk.Button(self.home_frame, text="Загрузить xml")
        self.load_xml_button.pack(pady=4)
        self.table = ttk.Treeview(self.home_frame, columns=("ФИО пациента", "Адрес прописки", "Дата рождения", "Дата приема", "ФИО врача", "Заключение"), show="headings")
        self.table.heading("ФИО пациента", text="ФИО пациента")
        self.table.heading("Адрес прописки", text="Адрес прописки")
        self.table.heading("Дата рождения", text="Дата рождения")
        self.table.heading("Дата приема", text="Дата приема")
        self.table.heading("ФИО врача", text="ФИО врача")
        self.table.heading("Заключение", text="Заключение")
        self.table.pack(pady=4, fill="both", expand=True)

        self.pagination_frame = tk.Frame(self.home_frame)
        self.pagination_frame.pack(pady=10)
        
        tk.Label(self.pagination_frame, text="Записей на странице:").grid(row=0, column=0, padx=5)
        self.items_per_page_var = tk.StringVar(value=str(self.items_per_page))
        self.items_per_page_entry = ttk.Entry(self.pagination_frame, textvariable=self.items_per_page_var, width=5)
        self.items_per_page_entry.grid(row=0, column=1, padx=5)
        self.apply_items_button = ttk.Button(self.pagination_frame, text="Применить")
        self.apply_items_button.grid(row=0, column=2, padx=5)
                
        self.first_button = ttk.Button(self.pagination_frame, text="<<")
        self.first_button.grid(row=0, column=3, padx=5)

        self.prev_button = ttk.Button(self.pagination_frame, text="< Предыдущая")
        self.prev_button.grid(row=0, column=4, padx=5)
        self.page_label = ttk.Label(self.pagination_frame, text=f"Страница {self.current_page} из {self.total_pages}")
        self.page_label.grid(row=0, column=5, padx=5)
        self.next_button = ttk.Button(self.pagination_frame, text="Следующая >")
        self.next_button.grid(row=0, column=6, padx=5)
        
        self.last_button = ttk.Button(self.pagination_frame, text=">>")
        self.last_button.grid(row=0, column=7, padx=5)

        self.tree = ttk.Treeview(self.home_frame)
        self.tree.pack(pady=4, fill="both", expand=True)

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
        self.create_button = tk.Button(self.create_frame, text="Создать запись")
        self.create_button.pack(pady=4)

    def setup_delete_page(self):
        self.delete_field = tk.Entry(self.delete_frame, width=30)
        tk.Label(self.delete_frame, text="Введите одно из данных для удаления (достаточно одного поля):").pack(pady=2)
        tk.Label(self.delete_frame, text="").pack(pady=2)
        self.delete_field.pack(pady=4)
        self.delete_button = tk.Button(self.delete_frame, text="Удалить запись")
        self.delete_button.pack(pady=10)

    def setup_search_page(self):
        self.search_field = tk.Entry(self.search_frame, width=30)
        tk.Label(self.search_frame, text="Введите данные для поиска (достаточно одного поля):").pack(pady=2)
        self.search_field.pack(pady=4)
        self.search_button = tk.Button(self.search_frame, text="Найти запись")
        self.search_button.pack(pady=10)
        self.search_table = ttk.Treeview(self.search_frame, columns=("ФИО пациента", "Адрес прописки", "Дата рождения", "Дата приема", "ФИО врача", "Заключение"), show="headings")
        self.search_table.heading("ФИО пациента", text="ФИО пациента")
        self.search_table.heading("Адрес прописки", text="Адрес прописки")
        self.search_table.heading("Дата рождения", text="Дата рождения")
        self.search_table.heading("Дата приема", text="Дата приема")
        self.search_table.heading("ФИО врача", text="ФИО врача")
        self.search_table.heading("Заключение", text="Заключение")
        self.search_table.pack(pady=4, fill="both", expand=True)

    def start(self):
        self.root.mainloop()