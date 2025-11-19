#include "HealUpgrade.h"
#include "Player.h"

HealUpgrade::HealUpgrade() {
    // Hàm dựng rỗng
}

void HealUpgrade::applyUpgrade(Player& player)
{
    // Hồi 50 máu
    player.heal(50);
}

std::string HealUpgrade::getName() const
{
    return "Hoi 50 Mau (Ngay lap tuc)";
}