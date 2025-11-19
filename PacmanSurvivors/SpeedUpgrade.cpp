#include "SpeedUpgrade.h"
#include "Player.h"

SpeedUpgrade::SpeedUpgrade() {
    // Hàm dựng rỗng
}

void SpeedUpgrade::applyUpgrade(Player& player)
{
    // Tăng tốc độ thêm 10 (khoảng 15%)
    player.addMoveSpeed(10.f);
}

std::string SpeedUpgrade::getName() const
{
    return "Tang Toc Do Di Chuyen";
}