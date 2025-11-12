#pragma once
#include "IUpgrade.h"
#include "Player.h"

class HealthUpgrade : public IUpgrade {
public:
	HealthUpgrade();
	void applyUpgrade(Player& player) override;
	std::string getName() const override;
private:
	int m_hpToAdd;
};