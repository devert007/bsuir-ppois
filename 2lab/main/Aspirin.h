#pragma once
#include "D:\LABY\BSUIR\PPOIS\2laba_PPOIS\Order.h"
class ASPIRIN :public Order {
private:
	Company company;
public:
	ASPIRIN() {
		setName("ASPIRIN");
		setPrice(40);
		setInfoAboutOrder("Aspirin � ��� ������������� ��������, ������� �������� �������, ���� �� �������� ������������ ��������������������� ���������� (NSAIDs), ������������� �� �������� ������� �������� � ���������� ������������ �����������.\n\n�������� ������������ Aspirin:\n1. �������� �������� ��������: Aspirin �������� ������� ������� �������� ��� ��������� ������������, ����� ���������� ��������� ������������ �������, ����� ��� �������� ������������� ���������, ������� �������� ��������� ��������� �������� ��������.\n2. ����������� ����������� ����: Aspirin �������� ������������ ����������� ���� � ���������� ���������, ��������� �� ������� ��������� �������, ������������� �� ��������� �����������, ����� ��� ��������� � ��������.\n3. �������������� ������� ��������: Aspirin ����� ������ ������������� ������� ��������, ��������� �� ������� ������� ��������� � �����, ��� �������� � ����� ������� � ������ ������ ������� �������.");
		this->company.setName("TyanShiFarm");
	}
	string getSupplierName() {
		return this->company.getName();
	}
};

