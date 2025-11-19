#pragma once
#include "IUpgrade.h"

class SpeedUpgrade : public IUpgrade
{
public:
    SpeedUpgrade();

    void applyUpgrade(Player& player) override;
    std::string getName() const override;
};