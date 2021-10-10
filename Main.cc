
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "DbConnect.h"

using namespace std;

int main(void)
{
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    DbConnect dbConn;

    string dbServer = "tcp://127.0.0.1:3306";
    string dbUser = "user01";
    string dbUserPassword = "user123";
    string database = "Code";

    con = dbConn.ConnectDb(dbServer, dbUser, dbUserPassword, database);
    stmt = con->createStatement();

    /*
     Rule 1: Create two rules for analyzing customer transactions and identify customers with possible fraudulent spending.
     In statistics, the z-score (or standard score) of an observation is the number of standard deviations that it is above or below the population mean.

     we can use the z-score to answer questions like the following:

        What percentage of values fall below a specific value?
        What values can be expected to be outliers?
        What is the relative score of one distribution versus another? Literally comparing apples and oranges.

     It is generally accepted that z-scores lower than -1.96 or higher than 1.96 to be outliers, or at the least worth a second look.
     These values are statistically significant at the 95% confidence level. For a higher confidence level of 99%, 
     you are interested in z-scores of higher than 2.576 or lower than -2.576. We are assuming that your data fits a normal distribution.

    */

    cout<<"Rule 1: Identify abnormally high transactions in a customers’ spending."<<endl<<endl;

    res = stmt->executeQuery("SELECT * FROM process_zscore_account where z_score>1.96 OR z_score<-1.96;");
    std::stringstream queryOutput;

    while (res->next())
    {
        queryOutput << "Customer name:\t" << res->getString(1) << "\ttranscation_number:\t" << res->getString(2)
                    << "\taccount_number:\t" << res->getString(3) << "\tmerchant:\t"
                    << res->getString(4) <<"\ttranscation_amount:\t" << res->getString(5) << "\tz-score:\t" << res->getString(6) << endl;
    }
    cout << queryOutput.str() << endl;

    std::ofstream rule1Out ("rule1Out.txt",std::ofstream::binary);
    rule1Out<<queryOutput.str()<<endl;
    rule1Out.close();

    /*
    Rule 2: Identify customer transactions that occurred in a different state from the customers’ primary state.

    */
   cout<<"Rule 2: Identify customer transactions that occurred in a different state from the customers’ primary state."<<endl<<endl;

    res = stmt->executeQuery("SELECT acc.first_name, acc.last_name, acc.account_number,acc.state as\     
             Expected_Transaction_Location, tr.transaction_number, tr.transaction_state as\  
             Actual_Transaction_Location\
             FROM account_info acc inner join transaction tr on acc.account_number = tr.account_number\ 
            WHERE acc.state <> tr.transaction_state;");
    
   
    std::stringstream queryOutput2;
    
    while (res->next())
    {
        queryOutput2 <<"firstName\t" << res->getString(1) <<"\tlastName\t" << res->getString(2) 
        <<"\taccount_number\t" << res->getString(3) << "\tExpected_Transaction\t" << res->getString(4) 
        << "\ttransaction_number\t" << res->getString(5)<<"\tactual_transaction\t"<<res->getString(6)<<endl;    
    }
    cout<<queryOutput2.str();
    std::ofstream rule2Out ("rule2Out.txt",std::ofstream::binary);
    rule2Out<<queryOutput2.str()<<endl;
    rule2Out.close();


}