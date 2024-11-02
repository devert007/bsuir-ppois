#pragma once
class Sale {
private:
	int sale;
public:
	Sale(int sale) {
		this->sale = sale;
	}
	int getSaleValue() {
		return this->sale;
	}
};