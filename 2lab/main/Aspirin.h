#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
class Aspirin :public Order {
private:
	Company company;
	string seial_number = "XYZ-1234567890-ABC";
	int data = 19102024;
public:
	Aspirin() {
		setName("ASPIRIN");
		setPrice(40);
		setInfoAboutOrder("Aspirin � ��� ������������� ��������, ������� �������� �������, ���� �� �������� ������������ ��������������������� ���������� (NSAIDs), ������������� �� �������� ������� �������� � ���������� ������������ �����������.\n\n�������� ������������ Aspirin:\n1. �������� �������� ��������: Aspirin �������� ������� ������� �������� ��� ��������� ������������, ����� ���������� ��������� ������������ �������, ����� ��� �������� ������������� ���������, ������� �������� ��������� ��������� �������� ��������.\n2. ����������� ����������� ����: Aspirin �������� ������������ ����������� ���� � ���������� ���������, ��������� �� ������� ��������� �������, ������������� �� ��������� �����������, ����� ��� ��������� � ��������.\n3. �������������� ������� ��������: Aspirin ����� ������ ������������� ������� ��������, ��������� �� ������� ������� ��������� � �����, ��� �������� � ����� ������� � ������ ������ ������� �������.");
		this->company.setName("TyanShiFarm");
	}
	void helpAfterParty() {
		cout << "��� ������ ����� ����� ��������� ���������, ���������� ���� ��������� ����� ��������� "<<this->getName()<<"\n";
	}
	string getSupplierName() {
		return this->company.getName();
	}
	int getTheLastDayOfFarm() {
		int theLastDayOfFarm = this->data + 1;
		return theLastDayOfFarm;
	}
	void complete_impact() override
	{
		helpAfterParty();
	}

};

