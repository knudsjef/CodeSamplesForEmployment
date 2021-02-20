#include "Character.h"
#include <stdexcept>

using namespace std;

const Collection<const Item>& Character::getInventory()
{
    return inventory;
}

void Character::addItem(const Item& item)
{
    try
    {
        const Weapon& weapon = dynamic_cast<const Weapon&>(item);
        allWeapons.push_back(weapon);
        inventory.add(allWeapons.back());
    }
    catch (bad_cast)
    {
        try
        {
            const Armor& armor = dynamic_cast<const Armor&>(item);
            allArmor.push_back(armor);
            inventory.add(allArmor.back());
        }
        catch (bad_cast)
        {
            allGenericItems.push_back(item);
            inventory.add(allGenericItems.back());
        }
    }
}

void Character::dropItem(const Item& item)
{
    if (inventory.remove(item))
    {
        try
        {
            const Weapon& weapon = dynamic_cast<const Weapon&>(item);
            for (auto i = allWeapons.begin(); i != allWeapons.end(); i++)
            {
                if (&(*i) == &weapon)
                {
                    allWeapons.erase(i);
                    return;
                }
            }
        }
        catch (bad_cast)
        {
            try
            {
                const Armor& armor = dynamic_cast<const Armor&>(item);
                for (auto i = allArmor.begin(); i != allArmor.end(); i++)
                {
                    if (&(*i) == &armor)
                    {
                        allArmor.erase(i);
                        return;
                    }
                }
            }
            catch (bad_cast)
            {
                for (auto i = allGenericItems.begin(); i != allGenericItems.end(); i++)
                {
                    if (&(*i) == &item)
                    {
                        allGenericItems.erase(i);
                        return;
                    }
                }
            }
        }
    }
    else
    {
        throw logic_error("Item to be dropped is not in the inventory.");
    }
}

double Character::getTotalWeight() const
{
    double totalWeight = 0.0;

    for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
    {
        if (equippedArmor[i])
        {
            totalWeight += equippedArmor[i]->getWeight();
        }
    }

    if (equippedWeapon)
    {
        totalWeight += equippedWeapon->getWeight();
    }

    inventory.forEach([&totalWeight](const Item& item)
    {
        totalWeight += item.getWeight();
    });

    return totalWeight;
}

const Armor* Character::getEquippedArmor(unsigned int slotID) const
{
    if (slotID >= Armor::SLOT_COUNT)
    {
        throw out_of_range("Invalid slot ID: " + to_string(slotID));
    }
    else
    {
        return equippedArmor[slotID];
    }
}

unsigned int Character::getTotalArmorRating() const
{
    int rating = 0;

    for (const Armor* armorSlot : equippedArmor)
    {
        if (armorSlot)
        {
            rating += armorSlot->getRating();
        }
    }

    return rating;
}

void Character::equipArmor(const Armor& armor)
{
    if (inventory.remove(armor))
    {
        unsigned int slotID = armor.getSlotID();
        if (equippedArmor[slotID])
        {
            inventory.add(*equippedArmor[slotID]);
        }

        equippedArmor[slotID] = &armor;
    }
    else
    {
        throw logic_error("Armor to be equipped is not in the inventory.");
    }
}

void Character::unequipArmor(unsigned int slotID)
{
    if (slotID >= Armor::SLOT_COUNT)
    {
        throw out_of_range("Invalid slot ID: " + to_string(slotID));
    }
    else if (equippedArmor[slotID])
    {
        inventory.add(*equippedArmor[slotID]);
        equippedArmor[slotID] = nullptr;
    }
}

const Weapon* Character::getEquippedWeapon() const
{
    return equippedWeapon;
}

void Character::equipWeapon(const Weapon& weapon)
{
    if (inventory.remove(weapon))
    {
        if (equippedWeapon)
        {
            inventory.add(*equippedWeapon);
        }

        equippedWeapon = &weapon;
    }
    else
    {
        throw logic_error("Weapon to be equipped is not in the inventory.");
    }
}

void Character::unequipWeapon()
{
    if (equippedWeapon)
    {
        inventory.add(*equippedWeapon);
    }

    equippedWeapon = nullptr;
}

void Character::optimizeInventory(double maximumWeight)
{
    if (maximumWeight < 0)
    {
        throw out_of_range("Maximum weight must be non-negative.");
    }

    double totalWeight = getTotalWeight();
    while (maximumWeight < totalWeight && inventory.getSize() != 0)
    {
        totalWeight -= inventory.getLast().getWeight();
        dropItem(inventory.getLast());
    }
}

void Character::optimizeEquipment()
{
    const Weapon* optimalWeapon = getEquippedWeapon();
    const Armor* optimalArmor[Armor::SLOT_COUNT];
    for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
    {
        optimalArmor[i] = getEquippedArmor(i);
    }

    inventory.forEach([&](const Item& item)
    {
        try
        {
            const Weapon& weapon = dynamic_cast<const Weapon&>(item);
            if (!optimalWeapon || optimalWeapon->getDamage() < weapon.getDamage())
            {
                optimalWeapon = &weapon;
            }
        }
        catch (bad_cast)
        {
            try
            {
                const Armor& armor = dynamic_cast<const Armor&>(item);
                unsigned int slotID = armor.getSlotID();
                if (!optimalArmor[slotID] || optimalArmor[slotID]->getRating() < armor.getRating())
                {
                    optimalArmor[slotID] = &armor;
                }
            }
            catch (bad_cast)
            {
            }
        }
    });

    if (optimalWeapon && optimalWeapon != getEquippedWeapon())
    {
        equipWeapon(*optimalWeapon);
    }

    for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
    {
        if (optimalArmor[i] && optimalArmor[i] != getEquippedArmor(i))
        {
            equipArmor(*optimalArmor[i]);
        }
    }
}
