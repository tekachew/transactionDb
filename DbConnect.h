#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;
class DbConnect
{
private:
    sql::Driver *driver;
    sql::Connection *con;

public:
    sql::Connection* ConnectDb(const string& server, const string& user, const string& password,const string& database);
    DbConnect();
    ~DbConnect();
};