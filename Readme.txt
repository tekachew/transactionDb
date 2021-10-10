


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
     
     

 
