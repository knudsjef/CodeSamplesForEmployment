#pragma once
#include "Collection.h"
#include "Item.h"
#include <list>

class Inventory : public Collection<const Item>
{
public:
    virtual unsigned int getSize() const;

    virtual void forEach(
        const std::function<void(const Item&)>& accept)
        const;

    virtual void forEach(
        const std::function<void(const Item&)>& accept);

    const Item& getLast() const;
    void add(const Item& item);
    bool remove(const Item& item);

private:
    std::list<const Item*> inventoryList;
    
    double valueWeightRatio(const Item& item);
};