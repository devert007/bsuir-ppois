#pragma once
#include "Order.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Mig.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Acetaminophen.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Antigistat.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Aspirin.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Diclofenac.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Headflex.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Ibyprofen.h"
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Ketorelac.h"
#include "Human.h"

class Manager :public Human {
private:
	Order order_of_client;
	Order compare_an_order(int indexOfOrder);
	Order sayHelloAndMakeOrder();
public:
	Manager();
	Order sendAconfirmationToClient();
};
