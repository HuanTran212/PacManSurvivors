#pragma once
#include "IUpgrade.h"

class HealUpgrade : public IUpgrade
{
public:
    HealUpgrade();
    void applyUpgrade(Player& player) override;
    std::string getName() const override;
};