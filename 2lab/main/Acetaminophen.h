#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
class Acetaminophen :public Order {
private:
	Company company;
	string seial_number = "A1B2C3D4E5F6G7H8I9J0";
public:
	Acetaminophen() {
		setName("ACETAMINOPHEN");
		setPrice(40);
		setInfoAboutOrder("Acetaminophen � ��� ������������� ��������, ������� �������� ������������, ���� �� �������� ������������ ��������������������� ���������� (NSAIDs), ������������� �� �������� ������� �������� � ���������� ������������ �����������.\n\n�������� ������������ Acetaminophen:\n1. �������� �������� ��������: Acetaminophen �������� ������� ������� �������� ��� ��������� ������������, ����� ���������� ��������� ������������ �������, ����� ��� �������� ������������� ���������, ������� �������� ��������� ��������� �������� ��������.\n2. ����������� ����������� ����: Acetaminophen �������� ������������ ����������� ���� � ���������� ���������, ��������� �� ������� ��������� �������, ������������� �� ��������� �����������, ����� ��� ��������� � ��������.\n3. ��������� ����������� ��������: Acetaminophen ����� ������ �������� ����������� ��������, ��������� �� ������� ������� ��������� � �����, ��� �������� � ����� ������� � ������ ������ ������� �������.");
		this->company.setName("TyanShiFarm");
	}
	void getAcetaminopehForClient() {
		cout << "����� ������������� "<<this->getName()<<" �������� ���������, ��� � ��� �� �������� �� ������ ��������.\n";
	}
	
	string getSupplierName() {
		return this->company.getName();
	}
	void complete_impact() override
	{
		getAcetaminopehForClient();
	}
};
