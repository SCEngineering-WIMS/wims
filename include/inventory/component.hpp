#pragma once

#include <mutex>
#include <string>

namespace wims
{
class Component
{
  public:
    Component(const std::string part_number, const std::string supplier);

    Component(const Component& other) noexcept;
    Component(Component&& other) noexcept;
    Component& operator=(const Component& other);
    Component& operator=(Component&& other);

    void partNumber(const std::string& val);
    void supplier(const std::string& val);
    const std::string partNumber() const;
    const std::string supplier() const;
  
  private:
    std::string part_number_;
    std::string supplier_;
    mutable std::mutex part_mutex_;
    mutable std::mutex supplier_mutex_;
};

Component::Component(const std::string part_number, const std::string supplier) :
    part_number_(part_number),
    supplier_(supplier)
{
};

Component::Component(const Component& other) noexcept : part_number_(other.part_number_), supplier_(other.supplier_)
{
};

Component::Component(Component&& other) noexcept :
    part_number_(std::move(other.part_number_)),
    supplier_(std::move(other.supplier_))
{
};

Component& Component::operator=(Component&& other)
{
    part_number_ =std::move(other.part_number_);
    supplier_ =std::move(other.supplier_);
    return *this;
};

Component& Component::operator=(const Component& other)
{
    part_number_ = other.part_number_;
    supplier_ =other.supplier_;

    return *this;
};

void Component::partNumber(const std::string& val)
{
    std::scoped_lock<std::mutex> lock(part_mutex_);
    part_number_ = val;
};

void Component::supplier(const std::string& val)
{
    std::scoped_lock<std::mutex> lock(supplier_mutex_);
    supplier_ = val;
};

const std::string Component::partNumber() const
{
    std::scoped_lock<std::mutex> lock(part_mutex_);
    return part_number_;
};

const std::string Component::supplier() const
{
    std::scoped_lock<std::mutex> lock(supplier_mutex_);
    return supplier_;
};
}  // namespace wims
