#pragma once

#include "component.hpp"

namespace wims
{
class Resistor : public Component
{
  public:
    Resistor(const std::string part_number, const std::string supplier);
};

Resistor::Resistor(const std::string part_number, const std::string supplier) : Component(part_number, supplier)
{
};
}