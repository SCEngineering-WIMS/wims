#include "inventory/container.hpp"
#include "inventory/resistor.hpp"
#include "web/server.hpp"

#include <functional>

int main()
{
    wims::Container container("resistors");
    
    wims::Resistor resistor1234("R1234", "Altronics");
    wims::Resistor resistor5678("R5678", "JayCar");

    std::function<const std::string()> containerId = std::bind(&wims::Container::id, container);
    std::function<const std::string()> containerComponents
        = std::bind(&wims::Container::componentsAsString, container);

    container.addComponent(resistor1234);
    container.addComponent(resistor5678);

    std::cout << container.componentsAsString() << std::endl;

    for(const auto part : container.components())
    {
        std::cout << part.partNumber() << std::endl;
    }

    wims::WimServer server("127.0.0.1", 8080);

    CROW_ROUTE(server.application(), "/container/")(containerId);
    CROW_ROUTE(server.application(), "/parts/")(containerComponents);

    server.start();

    return 0;
}
