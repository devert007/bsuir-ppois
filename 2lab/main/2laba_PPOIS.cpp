
#include <iostream>
#include <string>
using namespace std;
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Client.cpp"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Manager.h"
#include <vector>
#include "Company.h"
#include "Director.h"
int main()
{
    setlocale(LC_ALL, "russian");
    RegMenu menu;
    Client new_client(menu);
    Director director;
    Company lekar = director.showCompany();
    bool flagForMenuLoop = true;
    int chooseClient = 5;
    system("cls");
    cout << "\t\t\tДобро пожаловать в компанию LEKAR.by\n";
    while (flagForMenuLoop && chooseClient>0 && chooseClient<6) {
       
       cout << "|Cash: " << new_client.getCash() << "\n";
       cout << "\t\t\tВыберите необходимую вам операцию\n";
       cout << "1. Узнать детали компании\n";
       cout << "2. Указать свои симптомы\n";
        cout << "3. Добавить в корзину\n";
        cout << "4. Просмотреть корзину\n";
        cout << "5. Узнать информацию о лекарственных препаратах\n";
        cout << "6. Удалить из корзины\n";
        cout << "7. Сделать заказ\n";
        cout << "8. Завершить сеанс\n";
       
        cin >> chooseClient;
        switch (chooseClient)
        {
        case 1:
            cout << lekar.showInfoAboutCompany() << "\n\n";
            cout << "Хотите узнать поставщиков компании?(1-да,0-нет)" << '\n';
            int indexOfChooseAboutSuppliers;
            cin >> indexOfChooseAboutSuppliers;
            if (indexOfChooseAboutSuppliers) {
                for (int i = 0; i < lekar.getSuppliers().size(); i++) {
                    cout << "Поставщик: " << lekar.getSuppliers()[i].getName()
                        << "\nПодробная информация на сайте поставщика: " << lekar.getSuppliers()[i].showInfoAboutCompany() << '\n';
                }
                
            }
            break;
        case 2:
        {cout << "Укажите номер вашего потенциального симптома и мы подберем вам нужное лекарство:\n";
        cout << "1.Болит голова \n";
        cout << "2.Повреждение кожного покрова.Устранение инфекций из крови.Противоспалительное\n";
        cout << "3.Болит голова после выходного вечера. Отравление, головокружение.\n";
        cout << "4.Сильное сокращение мышечных волокон, сильное напряжение в мышцахю\n";
        cout << "5.Сильная головная боль в лобной части\n";
        cout << "6.Боли в суставах, мышцах, головные боли\n";
        cout << "7.Вирусные инфекции, бактериальные заболевания\n";
        cout << "8.Боли в различных частях цела, мышечные боли, боли в животе и нижних конечностях.\n";
        int choose_client_about_disease;
        cin >> choose_client_about_disease;
        Manager manager1(false);
        manager1.getAnFarmAndCompare(choose_client_about_disease);
        } break;
        case 3:
        {Manager manager;
        Order orderOfClient;
        orderOfClient = manager.sendAconfirmationToClient();
        new_client.addBasket(orderOfClient); }
            system("cls");
            break;
        case 4: {
            vector<Order>basket = new_client.getBasketList();
            std::cout << "Ваша корзина:\n";
            for (int i = 0; i < basket.size(); i++)
            {
                cout << i + 1 << ") " << basket[i].getName() << "\nPrice:" << basket[i].getPrice() << '\n';
            }}
            break;
        case 5:
            cout << "1. MIG\n";
            cout << "2. HeadFlex\n";
            cout << "3. IBYPROFEN\n";
            cout << "4. ANTIGISTAT\n";
            cout << "5. ACETAMINOPHEN\n";
            cout << "6. ASPIRIN\n";
            cout << "7. DICLOFENAC\n";
            cout << "8. KETOROLAC\n";
            cout << "Введите номер лекарства: ";
            int indexOfPotencialOrder;
            cin >> indexOfPotencialOrder;
            if (indexOfPotencialOrder == 1) {
                MIG mig;
                cout << mig.getInfoAboutOrder() << "\nЦЕНА: " << mig.getPrice() << "\nПоставщик: " << mig.getSupplierName() << '\n';
            }
            else if(indexOfPotencialOrder==2){
                HeadFlex head;
                cout << head.getInfoAboutOrder()<<"\nЦЕНА: " << head.getPrice()<<"\nПоставщик: "<<head.getSupplierName() << '\n';
            }
            else if (indexOfPotencialOrder == 4) {
                Antigistat anti;
                cout << anti.getInfoAboutOrder() << "\nЦЕНА: " << anti.getPrice() << "\nПоставщик: " << anti.getSupplierName() << '\n';
            }
            else if (indexOfPotencialOrder == 3) {
                Ibuprofen iby;
                cout << iby.getInfoAboutOrder() << "\nЦЕНА: " << iby.getPrice() << "\nПоставщик: " << iby.getSupplierName() << '\n';
            }
            else if (indexOfPotencialOrder == 5) {
                Acetaminophen aceta;
                cout << aceta.getInfoAboutOrder() << "\nЦЕНА: " << aceta.getPrice() << "\nПоставщик: " << aceta.getSupplierName() << '\n';
            }
            else if (indexOfPotencialOrder == 6) {
                Aspirin aspi;
                cout << aspi.getInfoAboutOrder() << "\nЦЕНА: " << aspi.getPrice() << "\nПоставщик: " << aspi.getSupplierName() << '\n';
            }
            else if(indexOfPotencialOrder==7){
                Diclofenac diclo;
                cout << diclo.getInfoAboutOrder() << "\nЦЕНА: " << diclo.getPrice() << "\nПоставщик: " << diclo.getSupplierName() << '\n';
            }
            else if (indexOfPotencialOrder == 8) {
                Ketorolac keto;
                cout << keto.getInfoAboutOrder() << "\nЦЕНА: " << keto.getPrice() << "\nПоставщик: " << keto.getSupplierName() << '\n';
            }
            break;
        case 6:
            new_client.deleteFromBasket();
            break;
        case 7:
            new_client.doMainOrder();

            break;
        case 8:
            flagForMenuLoop = false;
        default:
            break;
        }
    }
 


}
