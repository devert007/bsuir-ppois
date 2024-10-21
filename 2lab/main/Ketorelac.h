#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
class Ketorolac :public Order {
private:
	Company company;
	string seial_number = "9876543210-1234567890-ABC";

public:
	Ketorolac() {
		setName("KETOROLAC");
		setPrice(40);
		setInfoAboutOrder("Ketorolac � ��� ������������� ��������, ������� �������� ���������, ���� �� �������� ������������ ��������������������� ���������� (NSAIDs), ������������� �� �������� ������� �������� � ���������� ������������ �����������.\n\n�������� ������������ Ketorolac:\n1. �������� �������� ��������: Ketorolac �������� ������� ������� �������� ��� ��������� ������������, ����� ���������� ��������� ������������ �������, ����� ��� �������� ������������� ���������, ������� �������� ��������� ��������� �������� ��������.\n2. ����������� ����������� ����: Ketorolac �������� ������������ ����������� ���� � ���������� ���������, ��������� �� ������� ��������� �������, ������������� �� ��������� �����������, ����� ��� ��������� � ��������.\n3. ��������� ����������� ��������: Ketorolac ����� ������ �������� ����������� ��������, ��������� �� ������� ������� ��������� � �����, ��� �������� � ����� ������� � ������ ������ ������� �������.");
		this->company.setName("RussianFarm");
	}
	string getSupplierName() {
		return this->company.getName();
	}
	void getDoctorRecipe() {
		if (this->company.getName() == "RussianFarm") {
			cout <<"�������� " << this->getName() << " ���� �� ��� ���������, ������������������� � ����� ������������.\n";
		}
	}
	void complete_impact() override
	{
		getDoctorRecipe();
	}
};

