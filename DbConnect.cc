
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "DbConnect.h"
using namespace std;
DbConnect::DbConnect(){}
DbConnect::~DbConnect(){}
sql::Connection* DbConnect::ConnectDb(const string  &server, const string &user, const string &password,const string &database)
{
    try
    {      

        /* Create a connection */
        driver = get_driver_instance();
       // con = driver->connect("tcp://127.0.0.1:3306", "user01", "user123");
        con = driver->connect(server, user, password);

        /* Connect to the MySQL  database */
        con->setSchema(database);   
         
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;   
        
        delete con;   
    }
    
    return con;
}