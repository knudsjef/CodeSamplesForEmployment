#pragma once
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Inventory.h"
#include <array>
#include <list>

class Character
{
public:
    Character() = default;
    Character(const Character& character) = delete;
    Character& operator = (const Character& character) = delete;

    const Collection<const Item>& getInventory();

    void addItem(const Item& item);
    void dropItem(const Item& item);
    double getTotalWeight() const;

    const Armor* getEquippedArmor(unsigned int slotID) const;
    unsigned int getTotalArmorRating() const;
    void equipArmor(const Armor& armor);
    void unequipArmor(unsigned int slotID);

    const Weapon* getEquippedWeapon() const;
    void equipWeapon(const Weapon& weapon);
    void unequipWeapon();

    void optimizeInventory(double maximumWeight);
    void optimizeEquipment();

private:
    std::list<Weapon> allWeapons;
    std::list<Armor> allArmor;
    std::list<Item> allGenericItems;

    Inventory inventory;
    std::array<const Armor*, Armor::SLOT_COUNT> equippedArmor {};
    const Weapon* equippedWeapon { nullptr };
};