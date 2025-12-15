#pragma once
#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    /* data */
    ObjectScreen *parrent = nullptr;
    virtual void init() override {}

public:
    ObjectAffiliate(/* args */);
    ~ObjectAffiliate();
};

ObjectAffiliate::ObjectAffiliate(/* args */)
{
}

ObjectAffiliate::~ObjectAffiliate()
{
}
