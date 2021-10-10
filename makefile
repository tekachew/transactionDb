all: app

app: Main DbConnect 
	g++ Main.o DbConnect.o -o app -lmysqlcppconn -lpthread 

DbConnect: DbConnect.cc
	g++ -c DbConnect.cc

Main: Main.cc
	g++ -c Main.cc 