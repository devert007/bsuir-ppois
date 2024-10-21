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
		setInfoAboutOrder("Mig — это лекарственный препарат, который содержит мигстон, один из основных антигистаминов, ответственных за производство серотонина и норадреналина, важных нейромедиаторов, которые участвуют в передаче чувствительности и восприятия в мозге.\n\nОсновные преимущества Mig:\n1. Снижение болевого синдрома: Mig помогает снизить болевые ощущения при мигрени, путем уменьшения выделения гистаминовых молекул, таких как продукты гистаминового алкалоида, которые являются основными причинами болевого синдрома.\n2. Улучшение координации движений: Mig может помочь улучшить координацию движений, поскольку он снижает уровень гистамина в мозге, что приводит к более плавной и точной работе нервной системы.");
		this->company.setName("BelFarm");
	}
	string getSupplierName() {
		return this->company.getName();
	}
	string getIdOfFarm() {
		return this->seial_number;
	}
	void help_without_pain() {
		cout << "Приобретите MIG. Вы больше не почувствуете боль в животе и нижних конечностях\n";
	}
	void complete_impact() override
	{
		help_without_pain();
	}
};
