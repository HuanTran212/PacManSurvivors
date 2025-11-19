#include "UpgradeManager.h"
#include <random>
#include <algorithm>
#include <iostream>

#include "HealthUpgrade.h"
#include "OrbitalWeaponUpgrade.h"
#include "RandomShooterUpgrade.h"
#include "PelletShooterUpgrade.h"
#include "SpeedUpgrade.h"
#include "HealUpgrade.h"

UpgradeManager& UpgradeManager::getInstance() {
	static UpgradeManager instance;
	return instance;
}

UpgradeManager::UpgradeManager() {
	m_upgradePool.push_back(std::make_unique<HealthUpgrade>());
	m_upgradePool.push_back(std::make_unique<OrbitalWeaponUpgrade>());
	m_upgradePool.push_back(std::make_unique<RandomShooterUpgrade>());
	m_upgradePool.push_back(std::make_unique<PelletShooterUprade>());
	m_upgradePool.push_back(std::make_unique<SpeedUpgrade>());
	m_upgradePool.push_back(std::make_unique<HealUpgrade>());
}

std::vector<IUpgrade*> UpgradeManager::getRandomUpgrades(int count) {
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(m_upgradePool.begin(), m_upgradePool.end(), g);
	std::vector<IUpgrade*> selectedUpgrades;
	int numUpgrades = std::min(count, static_cast<int>(m_upgradePool.size()));
	for (int i = 0; i < numUpgrades; ++i) {
		selectedUpgrades.push_back(m_upgradePool[i].get());
	}
	return selectedUpgrades;
}