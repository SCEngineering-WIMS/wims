
#include <crow.h>

int main()
{
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")([](){
        return "Hello World";
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.bindaddr("192.168.50.110").port(8080).multithreaded().run();
}
