#pragma once

#include "component.hpp"

#include <iostream>
#include <sstream>
#include <vector>

namespace wims
{
class Container
{
  public:
    Container(const std::string id);

    Container(const Container& other) noexcept;
    Container(Container&& other) noexcept;
    Container& operator=(const Container& other);
    Container& operator=(Container&& other);

    const std::string id() const;
    const std::vector<Component>& components() const;
    const std::string componentsAsString() const;
    bool addComponent(const Component& component);

  private:
    std::string id_;
    std::vector<Component> components_;
    mutable std::mutex id_mtx_;
    mutable std::mutex components_mtx_;
};

Container::Container(const std::string id) : id_(id), components_()
{
};

Container::Container(const Container& other) noexcept :
  id_(other.id_),
  components_(other.components_)
{
};

Container::Container(Container&& other) noexcept :
  id_(std::move(other.id_)),
  components_(std::move(other.components_))
{
};

Container& Container::operator=(const Container& other)
{
    this->id_ = other.id_;
    this->components_ = other.components_;
    return *this;
}
Container& Container::operator=(Container&& other)
{
    this->id_ = std::move(other.id_);
    this->components_ = std::move(other.components_);
    return *this;
}

const std::string Container::id() const
{
    std::scoped_lock<std::mutex> lock(id_mtx_);
    return id_;
};

const std::vector<Component>& Container::components() const
{
    std::scoped_lock<std::mutex> lock(components_mtx_);
    return components_;
};

const std::string Container::componentsAsString() const
{
    std::stringstream parts_stream;

    for(const auto& part : this->components())
    {
        parts_stream << part.partNumber() << ",";
    }

    std::string tmp = parts_stream.str();
    if(tmp.empty())
    {
        throw std::range_error("tmp is empty!");
    }
    tmp.pop_back();
    return tmp;
};

bool Container::addComponent(const Component& component)
{
  try
  {
    std::scoped_lock<std::mutex> lock(components_mtx_);
    this->components_.emplace_back(component);
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << std::endl;
    return false;
  }
  return true;
};
}  // namespace wims
