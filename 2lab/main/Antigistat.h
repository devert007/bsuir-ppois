#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
class Antigistat :public Order {
private:
	Company company;
	string seial_number = "9876543210-ABC-DEF";
public:
	void destroy_infection() {
		cout << "Принимайте препарат "<< this->getName() <<" больше двух недель и инфекция ослабнет\n";
	}
	Antigistat() {
		setName("ANTIGISTAT");
		setPrice(40);
		setInfoAboutOrder("Antigistat — это лекарственный препарат, который содержит антигистамин, один из основных антигистаминовых препаратов, ответственных за снижение болевых ощущений и уменьшение инфекционных заболеваний.\n\nОсновные преимущества Antigistat:\n1. Снижение болевого синдрома: Antigistat помогает снизить болевые ощущения при различных заболеваниях, путем уменьшения выделения гистаминовых молекул, таких как продукты гистаминового алкалоида, которые являются основными причинами болевого синдрома.\n2. Поддержание температуры тела: Antigistat помогает поддерживать температуру тела в нормальном диапазоне, поскольку он снижает выделение веществ, ответственных за повышение температуры, таких как адреналин и кортизол.");
		this->company.setName("TyanShiFarm");
	}
	string getSupplierName() {
		return this->company.getName();
	}
	
	void complete_impact() override
	{
		destroy_infection();
	}
};
