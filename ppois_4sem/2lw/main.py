from controller import Controller
from user_interface import UserInterface

if __name__ == "__main__":
    ui = UserInterface() 
    controller = Controller(ui)  
    ui.set_controller(controller)  
    ui.start()