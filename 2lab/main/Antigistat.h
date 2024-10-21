#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
class Antigistat :public Order {
private:
	Company company;
	string seial_number = "9876543210-ABC-DEF";
public:
	void destroy_infection() {
		cout << "���������� �������� "<< this->getName() <<" ������ ���� ������ � �������� ��������\n";
	}
	Antigistat() {
		setName("ANTIGISTAT");
		setPrice(40);
		setInfoAboutOrder("Antigistat � ��� ������������� ��������, ������� �������� ������������, ���� �� �������� ���������������� ����������, ������������� �� �������� ������� �������� � ���������� ������������ �����������.\n\n�������� ������������ Antigistat:\n1. �������� �������� ��������: Antigistat �������� ������� ������� �������� ��� ��������� ������������, ����� ���������� ��������� ������������ �������, ����� ��� �������� ������������� ���������, ������� �������� ��������� ��������� �������� ��������.\n2. ����������� ����������� ����: Antigistat �������� ������������ ����������� ���� � ���������� ���������, ��������� �� ������� ��������� �������, ������������� �� ��������� �����������, ����� ��� ��������� � ��������.");
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
