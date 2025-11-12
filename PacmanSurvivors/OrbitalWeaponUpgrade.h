#pragma once
#include "IUpgrade.h"
#include "Player.h"

class OrbitalWeaponUpgrade : public IUpgrade {
public:
	OrbitalWeaponUpgrade();
	void applyUpgrade(Player& player);
	std::string getName() const;
};