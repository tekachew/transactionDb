


  How to Build and Run 
  
  Database
  1.install mysql server and create database.  
  2.uncompress Dump20211008.zip for the sql scripts 
  3.run the scripts in your mysql databse to create the account_inof , transcation table and process_z_score view
  
  Note: you might need to change "root"@  to your db user in the sql scripts if you run in to error 
 
  DbConnect client 
  1.Install mysqlcpp librabry  apt-get install libmysqlcppconn-dev for ubuntu 
  2.  Note: change the folowing in the Main.cc  to your needs     
    string dbServer = "tcp://127.0.0.1:3306";
    string dbUser = "user01";
    string dbUserPassword = "user123";
    string database = "Code";
  3.make 
  4.run ./app 
  


  
       Rule 1: Identify abnormally high transactions in a customers’ spending.
     
     In statistics, the z-score (or standard score) of an observation is the number of standard deviations that it is above or below the population mean.

     we can use the z-score to answer questions like the following:

        What percentage of values fall below a specific value?
        What values can be expected to be outliers?
        What is the relative score of one distribution versus another? Literally comparing apples and oranges.

     It is generally accepted that z-scores lower than -1.96 or higher than 1.96 to be outliers, or at the least worth a second look.
     These values are statistically significant at the 95% confidence level. For a higher confidence level of 99%, 
     you are interested in z-scores of higher than 2.576 or lower than -2.576. We are assuming that your data fits a normal distribution.
     
     
     On Transaction Table:
    1. The transaction_datetime changed to Date and time format (12182020 15:29:12 => 12/18/2020 15:29:12)
    2. Transaction amount has ‘– ‘after every value, so it is tanicated (1.06- => 1.06)
    3. Post_date colum some values are lessthan 8 digits, so for values with less than 8 value length, ‘0’ is added at the front and the value changed to date            format (2202021 => 02202021 =>02/20/2021)
    4. The Merchant_description column contains multiple information such as: description, city and state. Since the state is required for the analysis, the state       is split from the column and new column created with the value.  (MAVERIK #488           DRAPER       LAUS => LAUS) , (MACEY'S LEHI           LEHI                 LA => LA)
    5. The new State column have some value with ‘US’ appended on state code, therefore the ‘US’ is truncated from the data (LAUS=> LA)
     
     
 Creates View for Z-Score:
(View: process_zscore)

CREATE VIEW transaction_info.process_zscore as
               SELECT tr.account_number, tr.merchant, tr.transaction_number, tr.transaction_amount,                
                             AVG(tr.transaction_amount) as avg_transaction, STD(tr.transaction_amount) as 
                             stdev_transaction,  if (STD(tr.transaction_amount)<>0, (transaction_amount – 
                             AVG(tr.transaction_amount))/ STD(tr.transaction_amount), 0) as z_score
                                  FROM transaction tr GROUP BY tr.merchant, tr.account_number;
                                  
                                  
                                  
Create z-score with account information:
(View: process_zscore_account)
use transaction_info;
CREATE VIEW transaction_info.process_zscore_account as
	SELECT CONCAT(CONCAT(acc.first_name, " "), acc.last_name) as  customer_name, 
                            zs.transaction_number,  acc.account_number, zs.merchant, zs.transaction_amount,                    
                            zs.z_score
	             FROM account_info acc inner join process_zscore zs on 
			acc.account_number =   zs.account_number

 
