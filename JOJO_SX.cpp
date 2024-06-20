#include "JOJO_SX.hpp"

int main(){
    //all the variables we're going to use

    //user Variables
	float userBalance=0;//user's money
	float preBalance=0; 
	char userStock[37][10]; //primary attribute for identifying stock
	int userStockAmmount[37];
	float previousNetWorth=0;
	float currentNetWorth=0;
	float gain_loss=0;

	//data to be read into
	char stockSymbol[37][10];
	char stockName[37][50];
	float currentStockPrice[37];

	//temp data for each session
	float lowPrice[37];
	float highPrice[37];
	float prePrice[37];
	char bestPerformer[10]="";
	char worstPerformer[10]="";

    //initializing the values for current session
	for(int i=0;i<37;i++){
		strcpy(userStock[i],"n/a");
		userStockAmmount[i]=0;
	}
	readData(stockSymbol,stockName,currentStockPrice,userBalance,userStock,userStockAmmount,preBalance,previousNetWorth,currentNetWorth);
	
	for(int i=0;i<37;i++){
		lowPrice[i]=currentStockPrice[i]; highPrice[i]=currentStockPrice[i];
		prePrice[i]=currentStockPrice[i];
	}



	char option;//for choosing option i.e. adding/removing stock, viewing portfolio
    bool current_platform=true; //true=stockmarket  false=portfolio

    //menu
    do {
        if(current_platform){
        displayMarket(stockSymbol,stockName,currentStockPrice,lowPrice,highPrice,bestPerformer,worstPerformer,prePrice, userBalance,userStock,preBalance,userStockAmmount);}
        else{
            displayPortfolio(stockSymbol,stockName,currentStockPrice,lowPrice,highPrice,prePrice,userBalance,userStock,preBalance,userStockAmmount,gain_loss);
        }

        option=cin.get();//works for both porfolio and stk market
        
        if(current_platform){
	        if(option=='\n'){
		        bestWorstPerfomer(stockSymbol,currentStockPrice,bestPerformer,worstPerformer);
		        stockRandomizer(currentStockPrice,lowPrice,highPrice,prePrice);
				calculateGainLoss(stockSymbol,currentStockPrice,userStock,userStockAmmount,previousNetWorth,currentNetWorth,gain_loss);
	        }
	        else if(option=='M'||option=='m'){
		        float Money;
		        cout<<"Enter Ammount: ";
		        cin>>Money;
		        preBalance=userBalance;
		        userBalance+=Money;
		        cin.ignore();
	        }
            else if(option=='P'||option=='p'){
		        cin.ignore();
                current_platform=false;
            }
            else if(option=='A'||option=='a'){//these only work for stk market
                cin.ignore();
		        addStock(stockSymbol,currentStockPrice,userBalance,userStock,userStockAmmount);
            }
            else if(option=='R'||option=='r'){//these only work for stk market
                cin.ignore();
                removeStock(stockSymbol,currentStockPrice,userBalance,userStock,userStockAmmount);
            }
            else if(option=='E'||option=='e'){
                //exiting program
				cout<<"Exiting ..."<<endl;
				//writing data back to files
				break;
            }
        }
        else{
	        if(option=='\n'){
		        bestWorstPerfomer(stockSymbol,currentStockPrice,bestPerformer,worstPerformer);
		        stockRandomizer(currentStockPrice,lowPrice,highPrice,prePrice);
				calculateGainLoss(stockSymbol,currentStockPrice,userStock,userStockAmmount,previousNetWorth,currentNetWorth,gain_loss);
	        }
			else if(option=='M'||option=='m'){
		        float Money;
		        cout<<"Enter Ammount: ";
		        cin>>Money;
		        preBalance=userBalance;
		        userBalance+=Money;
		        cin.ignore();
			}
			else if(option=='L'||option=='l'){
		        cin.ignore();
                current_platform=true;
			}
			else if(option=='A'||option=='a'){
				cin.ignore();
				addStockPort(stockSymbol,currentStockPrice,userBalance,userStock,userStockAmmount);
			}
			else if(option=='R'||option=='r'){
				cin.ignore();
				removeStockPort(stockSymbol,currentStockPrice,userBalance,userStock,userStockAmmount);
			}
            else if(option=='E'||option=='e'){
				cout<<"Exiting ..."<<endl;
				//writing data back to files
				break;
			}
        }
    }
	while(option!='E');

	writeData(stockSymbol,stockName,currentStockPrice,userBalance,userStock,preBalance,userStockAmmount,previousNetWorth,currentNetWorth);

    return 0;
}
