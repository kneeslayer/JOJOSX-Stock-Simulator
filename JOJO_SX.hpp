#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cstring>

using namespace std;

void readData(char (&stockSymbol)[37][10],char (&stockName)[37][50],float (&currentStockPrice)[37],float &userBalance,char (&userStock)[37][10],int (&userStockAmmount)[37],float &preBalance, float (&previousNetWorth), float (&currentNetWorth)){
    
	//for companies.txt
    fstream file;
	file.open("companies.txt",ios::in);
	int row=0;
	while(!file.eof() && row<37){
		//file.getline(rawData[row],70,'\n');
		file.getline(stockSymbol[row],10,',');
		file.getline(stockName[row],50,',');
		file>>currentStockPrice[row];
		file.ignore();
		row++;
	}
	file.close();

	//for reading portfolio file
	fstream infile;
	infile.open("portfolio.txt",ios::in);
	
	int index=0;
	while(index<37){
		infile.getline(userStock[index],10,',');
		infile>>userStockAmmount[index];
		infile.ignore();//wherever there is a '\n'
		index++;
	}
	infile>>userBalance;infile.ignore();
	infile>>preBalance;infile.ignore();
	infile>>previousNetWorth;infile.ignore();
	infile>>currentNetWorth;infile.ignore();
	infile.close();


}

void writeData(char (&stockSymbol)[37][10],char (&stockName)[37][50],float (&currentStockPrice)[37],float &userBalance,char (&userStocks)[37][10],float &preBalance,int (&userStockAmmount)[37], float (&previousNetWorth), float (&currentNetWorth)){
    fstream stock;
	stock.open("companies.txt",ios::out);
	int row=0;
	while(row<37){
		stock<<stockSymbol[row]<<','<<stockName[row]<<','<<currentStockPrice[row]<<'\n';
		row++;
	}
	stock.close();
	fstream portfolio;
	portfolio.open("portfolio.txt",ios::out);
	row=0;
	while(row<37){
		portfolio<<userStocks[row]<<','<<userStockAmmount[row]<<'\n';
		row++;
	}
		portfolio<<userBalance<<'\n'<<preBalance<<'\n'<<previousNetWorth<<'\n'<<currentNetWorth<<'\n';
	portfolio.close();

}

void printData(char stockSymbol[37][10],char stockName[37][50],float currentStockPrice[37],float lowPrice[37],float highPrice[37],float prePrice[37],char userStocks[37][10],int userStockAmmount[37], bool printFrom){

	string red="\033[31m↓";
    string green="\033[32m↑";
    string resetColor="\033[0m";

	int val;
	if(printFrom)
		val=14;
	else
		val =18;
	string color;

	int id;
	//displaying current data
	if(!printFrom){
		for(int i=0;i<37;i++){
		id=i;
		if(currentStockPrice[i]>prePrice[i])
			color=green;
		else
			color=red;
			
		cout << left
		 << setw(5)  << id+1
         << setw(15) << stockSymbol[i]
         << setw(50) << stockName[i];
		 cout<<left
         << setw(18) << prePrice[i] << setw(4) << color
         << setw(14) << currentStockPrice[i] << setw(4) << resetColor
         << setw(val) << highPrice[i]
         << setw(10) << lowPrice[i] << endl;
	}
	}
	else{
		for(int i=0;i<37;i++){
			if(strcmp(userStocks[i],"n/a")==0)
				continue;
			for(int k=0;k<37;k++){
				if(strcmp(userStocks[i],stockSymbol[k])==0)
				{
					id=k;
					break;
				}
			}
			
			if(currentStockPrice[i]>prePrice[i])
				color=green;
			else
				color=red;
			
			cout << left
			 << setw(5)  << i+1
        	 << setw(15) << stockSymbol[id]
        	 << setw(50) << stockName[id];
			 cout<<setw(10)<<userStockAmmount[i];//no of
			 cout<<left
        	 << setw(18) << prePrice[id] << setw(4) << color
        	 << setw(14) << currentStockPrice[id] << setw(4) << resetColor
        	 << setw(val) << highPrice[id]
        	 << setw(10) << lowPrice[id] << endl;
		}
	}

}

void displayMarket(char (&stockSymbol)[37][10],char (&stockName)[37][50],float (&currentStockPrice)[37],float (&lowPrice)[37],float (&highPrice)[37],char (&bestPerformer)[10],char (&worstPerformer)[10],float (&prePrice)[37],float &userBalance,char (&userStock)[37][10], float &preBalance,int (&userStockAmmount)[37]){
    
	string magenta="\033[35m";
	string blue="\033[34m";
	string red="\033[31m↓";
	string bkgblue="\033[44m";
    string green="\033[32m↑";
    string Cyan="\033[36m";
    string bkgBlack="\033[40m";
    string resetColor="\033[0m";

	system("clear");
	cout <<magenta<<bkgBlack<<right<<setw(75)<<"JOJO STOCK PLATFORM"<<setw(64)<<setfill(' ')<<" \n"<<resetColor;    
	cout<<bkgblue<<setw(24)<<left<<"Update Market:  ↵"<<setw(24)<<"Show Portfolio: P"<<setw(24)<<"AddStock: A"<<setw(24)<<"Remove Stock: R"<<setw(22)<<"Add Money: M"<<setw(22)<<"Exit: E"<<resetColor<<endl;
	cout<<left<<bkgBlack<<Cyan<<
	setw(5)  << "No. "<<
	setw(15) << "Symbol"<<
	setw(50) << "Company Name"<<
	setw(18) << "Pre Price"<<
	setw(15) << "Cur Price"<<
	setw(18) << "High Price"<<
	setw(17) << "Low Price"<<resetColor<<endl;
    printData(stockSymbol,stockName,currentStockPrice,lowPrice,highPrice,prePrice,userStock,userStockAmmount,0);

	cout<<bkgBlack<<Cyan;
	cout<<"Best Performer: "<<green<<setw(7)<<bestPerformer<<resetColor<<bkgBlack<<Cyan<<left;
	cout<<"Worst Performer: "<<red<<setw(10)<<worstPerformer<<Cyan;
	cout<<left<<"Your Balance: "<<blue<<setw(72)<<left<<fixed<<setprecision(2)<<userBalance<<resetColor<<'\n';
	cout<<"Option: ";
}

void bestWorstPerfomer(char (&stockSymbol)[37][10],float (&currentStockPrice)[37],char (&bestPerformer)[10],char (&worstPerformer)[10]){

	int best=currentStockPrice[0];
	int bestIndex;
	int worst=currentStockPrice[0];
	int worstIndex;

	for(int i=0;i<37;i++){
		if(best<currentStockPrice[i]){
			best=currentStockPrice[i];
			bestIndex=i;
		}
		if(worst>currentStockPrice[i]){
			worst=currentStockPrice[i];
			worstIndex=i;
		}
	}

	//for(int i=0;i<5;i++){
		strcpy(bestPerformer,stockSymbol[bestIndex]);
		strcpy(worstPerformer,stockSymbol[worstIndex]);
	//}
		//cout<<bestPerformer;


}

void addStock(char (&stockSymbol)[37][10],float (&currentStockPrice)[37],float &userBalance,char (&userStock)[37][10],int (&userStockAmmount)[37]){
	
	int stockNum=2;
	int stockammount=2;//2 dummy val for starting the input validation
	int costofStocks;

	bool addFrom;//false= stock market  true=portfolio
	
	do{
		if(stockNum<1 ||stockNum>37)
		cout<<"Invalid Input!"<<endl;
		cout<<"Enter Stock Number: ";
		cin>>stockNum;
	}
	while(stockNum<1 ||stockNum>37);

	stockNum-=1;			

	do{
		cout<<"Enter the amount of Stocks:  ";
		cin>>stockammount;
		costofStocks = stockammount*currentStockPrice[stockNum]; 
			if(userBalance<costofStocks){
				cout<<"You don't have enough balance to buy this many shares.\n";
				cout<<"Current Balance: "<<userBalance<<endl;
				cout<<"Num of shares You can Buy: "<<int(userBalance/currentStockPrice[stockNum])<<endl;
			}
	}while(costofStocks>userBalance);

	bool check=false;
	int temp;
	for(int i=0;i<37;i++){//if stock is in portfolio, add more	
			if(strcmp(stockSymbol[stockNum],userStock[i])==0){
			check=true;
			temp=i;
			break;
			}
	}
	//
	if(check){
		userStockAmmount[temp]=stockammount;
		userBalance-=costofStocks;
	}
	else{
		//for adding new stocks
		for(int i =0;i<37;i++){
			if(strcmp(userStock[i],"n/a")==0){
				temp=i;
				strcpy(userStock[i],stockSymbol[stockNum]);
				userStockAmmount[i]=stockammount;
				userBalance-=costofStocks;
				break;
			}

		}

	}

	cout<<"You've Bought "<<stockammount<<" "<<stockSymbol[stockNum]<< " shares\n";
	char dummy;
	dummy=cin.get();
	dummy=cin.get();


}

void removeStock(char (&stockSymbol)[37][10],float (&currentStockPrice)[37],float &userBalance,char (&userStock)[37][10],int (&userStockAmmount)[37]){
	
	cout<<"Stocks In Portfolio:";
	for(int i =0;i<37;i++){
		if(strcmp(userStock[i],"n/a")==0)
			break;
		cout<<" "<<userStock[i];
	}
	cout<<endl;

	int stockNum=2;
	int stockammount=2;//2 dummy val for starting the input validation
	int moneyEarned;
	
	do{
		if(stockNum<1 ||stockNum>37)
		cout<<"Invalid Input!"<<endl;
		cout<<"Enter Stock Number: ";
		cin>>stockNum;
	}
	while(stockNum<1 ||stockNum>37);

	stockNum-=1;
	
	bool check=false;
	int temp;
	for(int i=0;i<37;i++){//if stock is in portfolio or not
			if(strcmp(stockSymbol[stockNum],userStock[i])==0){
			check=true;
			temp=i;//for identifying stock in userStock array
			break;
			}
	}
	
	if(!check){
		cout<<"Cant Sell any shares as this stock is not in Portfolio.\n";
		char op;
		op=cin.get();
		op=cin.get();
		return;
	}

	do{
		cout<<"Enter the amount of Stocks:  ";
		cin>>stockammount;
		if(userStockAmmount[temp]<stockammount){
				cout<<"You don't have this many Stocks to sell.\n";
				cout<<"Num of Stock You can sell: "<<userStockAmmount[temp]<<endl;
		}
	}while(userStockAmmount[temp]<stockammount);

	userStockAmmount[temp]-=stockammount;
	moneyEarned = stockammount*currentStockPrice[stockNum]; 

	userBalance+=moneyEarned;


	if(userStockAmmount[temp]==0){
		strcpy(userStock[temp],"n/a");
	}
	cout<<"You've sold "<<stockammount<<" "<<stockSymbol[stockNum]<< " shares\n";
	char dummy;
	dummy=cin.get();
	dummy=cin.get();
}

void stockRandomizer(float (&currentStockPrice)[37],float (&lowPrice)[37],float (&highPrice)[37],float (&prePrice)[37]){

	srand(time(0));

	float temp[37];
	int percent15=0;
	float randomValue=0;
	float decimalValue=0;
	bool plusMinus=false;//to determine whether to add or subtract rand 15% value

	
	for(int i =0;i<37;i++){
		prePrice[i]=currentStockPrice[i];

		percent15= currentStockPrice[i]*0.15;
		decimalValue= currentStockPrice[i]*0.15 -percent15;
		randomValue= 1 + (rand()%(percent15-1))  + decimalValue;//creating random value
		plusMinus = int(randomValue)%2;

		if(plusMinus)
			currentStockPrice[i]+=randomValue;
		else
			currentStockPrice[i]-=randomValue;

		if(currentStockPrice[i]>highPrice[i]){
			highPrice[i]=currentStockPrice[i];
		}

		if(currentStockPrice[i]<lowPrice[i]){
			lowPrice[i]=currentStockPrice[i];
		}
	}

}

void displayPortfolio(char (&stockSymbol)[37][10],char (&stockName)[37][50],float (&currentStockPrice)[37],float (&lowPrice)[37],float (&highPrice)[37],float (&prePrice)[37],float &userBalance,char (&userStock)[37][10],float &preBalance,int (&userStockAmmount)[37],float(&gain_loss)){

	string magenta="\033[35m";
	string blue="\033[34m";
	string red="\033[31m↓";
	string bkgblue="\033[44m";
    string green="\033[32m↑";
    string Cyan="\033[36m";
    string bkgBlack="\033[40m";
    string resetColor="\033[0m";

	string gain_loss_color;
	if(gain_loss<0)
		gain_loss_color=red;
	else
		gain_loss_color=green;

	char option;

	system("clear");
	cout <<magenta<<bkgBlack<<right<<setw(75)<<"JOJO STOCK PLATFORM"<<setw(64)<<setfill(' ')<<" \n"<<resetColor;    
	cout<<bkgblue<<setw(24)<<left<<"Update Market:  ↵"<<setw(24)<<"Live Market: L"<<setw(24)<<"AddStock: A"<<setw(24)<<"Remove Stock: R"<<setw(22)<<"Add Money: M"<<setw(22)<<"Exit: E"<<resetColor<<endl;
	cout<<left<<bkgBlack<<Cyan<<
	setw(5)  << "No. "<<
	setw(15) << "Symbol"<<
	setw(50) << "Company Name"<<
	setw(10) << "Shares"<<
	setw(18) << "Pre Price"<<
	setw(15) << "Cur Price"<<
	setw(14) << "High Price"<<
	setw(11) << "Low Price"<<resetColor<<endl;
    printData(stockSymbol,stockName,currentStockPrice,lowPrice,highPrice,prePrice,userStock, userStockAmmount,1);
	cout<<bkgBlack<<Cyan;
	cout<<left<<"Todays Gain/Loss:"<<gain_loss_color<<setw(10)<<gain_loss<<bkgBlack<<Cyan;
	cout<<"Prev Balance: "<<setw(15)<<preBalance<<Cyan;
	cout<<left<<"Curr Balance: "<<blue<<setw(78)<<left<<fixed<<setprecision(2)<<userBalance<<resetColor<<'\n';
	cout<<"Option: ";
}

void addStockPort(char (&stockSymbol)[37][10],float (&currentStockPrice)[37],float &userBalance,char (&userStock)[37][10],int (&userStockAmmount)[37]){

	int stockNum=2;
	int stockammount=2;//2 dummy val for starting the input validation
	int costofStocks;
	
	if(strcmp(userStock[0],"n/a")==0){
		cout<<"No stocks in Portfolio"<<endl;
		char dummy;
		dummy=cin.get();
		dummy=cin.get();
		
		return;
	}

	int max_amount=0;
	for(int i=0;i<37;i++){
		if(strcmp(userStock[i],"n/a")!=0){
			max_amount++;//checking what is max no of 
			break;
		}
	}

	do{
		cout<<"Enter Stock Number: ";
		cin>>stockNum;
		if(stockNum<1 ||stockNum>max_amount)
		cout<<"Invalid Input!"<<endl;
	}
	while(stockNum<1 ||stockNum>max_amount);

	stockNum-=1;//now we'll traslate this number to the stock number in stock market
	int temp1=stockNum;
	for(int i =0;i<37;i++){
		if(strcmp(userStock[temp1],stockSymbol[i])==0){
			stockNum=i;
			break;
		}
	}

	do{
		cout<<"Enter the amount of Stocks:  ";
		cin>>stockammount;
		costofStocks = stockammount*currentStockPrice[stockNum]; 
			if(userBalance<costofStocks){
				cout<<"You don't have enough balance to buy this many shares.\n";
				cout<<"Current Balance: "<<userBalance<<endl;
				cout<<"Num of shares You can Buy: "<<int(userBalance/currentStockPrice[stockNum])<<endl;
			}
	}while(costofStocks>userBalance);

	userStockAmmount[temp1]+=stockammount;
	cout<<"You've Bought "<<stockammount<<" "<<stockSymbol[stockNum]<< " shares\n";
	char dummy;
	dummy=cin.get();
	dummy=cin.get();


}

void removeStockPort(char (&stockSymbol)[37][10],float (&currentStockPrice)[37],float &userBalance,char (&userStock)[37][10],int (&userStockAmmount)[37]){


	int stockNum=2;
	int stockammount=2;//2 dummy val for starting the input validation
	int moneyEarned;
	
	if(strcmp(userStock[0],"n/a")==0){
		cout<<"No stocks in Portfolio to remove."<<endl;
		char dummy;
		dummy=cin.get();
		dummy=cin.get();
		
		return;
	}

	int max_amount=0;
	for(int i=0;i<37;i++){
		if(strcmp(userStock[i],"n/a")!=0){
			max_amount++;//checking what is max no of stocks in portfolio
			break;
		}
	}
	cout<<"Max="<<max_amount<<endl;

	do{
		cout<<"Enter Stock Number: ";
		cin>>stockNum;
		if(stockNum<1 ||stockNum>max_amount)
		cout<<"Invalid Input!"<<endl;
	}
	while(stockNum<1 ||stockNum>max_amount);

	stockNum-=1;//now we'll traslate this number to the stock number in stock market
	
	int temp1=stockNum;
	for(int i =0;i<37;i++){
		if(strcmp(userStock[temp1],stockSymbol[i])==0){
			stockNum=i;//the stk number is found
			break;
		}
	}

	bool check=false;
	
	do{
		cout<<"Enter the amount of Stocks:  ";
		cin>>stockammount;
		if(userStockAmmount[temp1]<stockammount){
				cout<<"You don't have this many Stocks to sell.\n";
				cout<<"Num of Stock You can sell: "<<userStockAmmount[temp1]<<endl;
		}
	}while(userStockAmmount[temp1]<stockammount);

	userStockAmmount[temp1]-=stockammount;
	moneyEarned = stockammount*currentStockPrice[stockNum]; 

	userBalance+=moneyEarned;


	if(userStockAmmount[temp1]==0){
		strcpy(userStock[temp1],"n/a");
	}
	cout<<"You've sold "<<stockammount<<" "<<stockSymbol[stockNum]<< " shares\n";
	char dummy;
	dummy=cin.get();
	dummy=cin.get();
}

void calculateGainLoss(char (&stockSymbol)[37][10], float (&currentStockPrice)[37], char (&userStock)[37][10], int (&userStockAmmount)[37], float (&previousNetWorth), float (&currentNetWorth),float(&gain_loss)) {
    float networth = 0;
    previousNetWorth = currentNetWorth;

    for (int i = 0; i < 37; i++) {
        if (strcmp(userStock[i], "n/a") != 0) {
            for (int j = 0; j < 37; j++) {
                if (strcmp(userStock[i], stockSymbol[j]) == 0) {
                    networth += currentStockPrice[j] * userStockAmmount[i];
                    break; // break the inner loop, but continue with the outer loop
                }
            }
        }
    }

    currentNetWorth = networth;

	gain_loss= currentNetWorth-previousNetWorth;
}
