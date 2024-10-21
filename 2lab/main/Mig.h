#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"

class MIG :public Order {
private:
	Company company;
	string seial_number = "AB1234567890-CDE";
public:
	MIG() {
		setName("MIG");
		setPrice(20);
		setInfoAboutOrder("Mig � ��� ������������� ��������, ������� �������� �������, ���� �� �������� ��������������, ������������� �� ������������ ���������� � �������������, ������ ���������������, ������� ��������� � �������� ���������������� � ���������� � �����.\n\n�������� ������������ Mig:\n1. �������� �������� ��������: Mig �������� ������� ������� �������� ��� �������, ����� ���������� ��������� ������������ �������, ����� ��� �������� ������������� ���������, ������� �������� ��������� ��������� �������� ��������.\n2. ��������� ����������� ��������: Mig ����� ������ �������� ����������� ��������, ��������� �� ������� ������� ��������� � �����, ��� �������� � ����� ������� � ������ ������ ������� �������.");
		this->company.setName("BelFarm");
	}
	string getSupplierName() {
		return this->company.getName();
	}
	string getIdOfFarm() {
		return this->seial_number;
	}
	void help_without_pain() {
		cout << "����������� MIG. �� ������ �� ������������ ���� � ������ � ������ �����������\n";
	}
	void complete_impact() override
	{
		help_without_pain();
	}
};
