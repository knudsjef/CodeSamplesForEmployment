#include "Inventory.h"

unsigned int Inventory::getSize() const
{
    return inventoryList.size();
}

void Inventory::forEach(const std::function<void(const Item&)>& accept) const
{
    for (const Item* item : inventoryList)
    {
        accept(*item);
    }
}

void Inventory::forEach(const std::function<void(const Item&)>& accept)
{
    for (const Item* item : inventoryList)
    {
        accept(*item);
    }
}

const Item& Inventory::getLast() const
{
    return *inventoryList.back();
}

void Inventory::add(const Item& item)
{
    double ratioToInsert = valueWeightRatio(item);
    auto i = inventoryList.begin();
    while (i != inventoryList.end() && ratioToInsert < valueWeightRatio(**i))
    {
        i++;
    }

    inventoryList.insert(i, &item);
}

bool Inventory::remove(const Item& item)
{
    unsigned int originalSize = inventoryList.size();
    inventoryList.remove(&item);
    return inventoryList.size() != originalSize;
}

double Inventory::valueWeightRatio(const Item& item)
{
    return item.getGoldValue() / item.getWeight();
}
