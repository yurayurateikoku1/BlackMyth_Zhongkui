#pragma once
#include "../core/actor.h"
class States : public Object
{
protected:
    /* data */
    Actor *_parent = nullptr;
    float _health = 100.0f;
    float _max_health = 100.0f;
    float _mana = 100.0f;
    float _max_mana = 100.0f;
    float _damage = 40.0f;
    float _mana_regen = 10.0f;
    bool _is_alive = true;
    float _invincible_time = 1.0f;  // 受伤后无敌时间
    float _invincible_timer = 0.0f; // 无敌时间计时器
    bool _is_invincible = false;

public:
    static States *addStatesChild(Actor *parent, float max_health = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);
    virtual void update(float dt) override;
    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);
    void takeDamage(float damage);
    void regenMana(float dt);

    float getHealth() const { return _health; }
    float getMana() const { return _mana; }
    float getMaxHealth() const { return _max_health; }
    float getMaxMana() const { return _max_mana; }
    float getDamage() const { return _damage; }
    float getManaRegen() const { return _mana_regen; }
    bool getIsAlive() const { return _is_alive; }
    Actor *getParent() const { return _parent; }

    void setHealth(float health) { _health = health; }
    void setMana(float mana) { _mana = mana; }
    void setMaxHealth(float max_health) { _max_health = max_health; }
    void setMaxMana(float max_mana) { _max_mana = max_mana; }
    void setDamage(float damage) { _damage = damage; }
    void setManaRegen(float mana_regen) { _mana_regen = mana_regen; }
    void setIsAlive(bool is_alive) { _is_alive = is_alive; }
    void setParent(Actor *parent) { _parent = parent; };

    void setInvincible() { _is_invincible = true; }
    bool getInvincible() const { return _is_invincible; }
};