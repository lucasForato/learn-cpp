#include "db/Database.h"
#include "db/models/User.h"
#include <crow/app.h>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        Database db("test.db");

        db.user->select("SELECT * FROM users");
        return 0;
    });

    app.port(8000).multithreaded().run();
}
