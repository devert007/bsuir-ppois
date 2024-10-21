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
		setInfoAboutOrder("Acetaminophen Ч это лекарственный препарат, который содержит ацетаминофен, один из основных нестероидных противовоспалительных препаратов (NSAIDs), ответственных за снижение болевых ощущений и уменьшение инфекционных заболеваний.\n\nќсновные преимущества Acetaminophen:\n1. —нижение болевого синдрома: Acetaminophen помогает снизить болевые ощущени€ при различных заболевани€х, путем уменьшени€ выделени€ гистаминовых молекул, таких как продукты гистаминового алкалоида, которые €вл€ютс€ основными причинами болевого синдрома.\n2. ѕоддержание температуры тела: Acetaminophen помогает поддерживать температуру тела в нормальном диапазоне, поскольку он снижает выделение веществ, ответственных за повышение температуры, таких как адреналин и кортизол.\n3. ”лучшение координации движений: Acetaminophen может помочь улучшить координацию движений, поскольку он снижает уровень гистамина в мозге, что приводит к более плавной и точной работе нервной системы.");
		this->company.setName("TyanShiFarm");
	}
	void getAcetaminopehForClient() {
		cout << "ѕеред употреблением "<<this->getName()<<" советуем убедитьс€, что у вас не аллергии на данный препарат.\n";
	}
	
	string getSupplierName() {
		return this->company.getName();
	}
	void complete_impact() override
	{
		getAcetaminopehForClient();
	}
};
