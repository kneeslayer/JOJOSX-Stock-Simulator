# JOJOSX-Stock-Simulator

Welcome to JOJO_SX Stock Trading Platform !!

This was my programming fundamentals final project, hope you learn from it.

When first loading the program make sure you have all the files required. 
They are :
	1. "companies.txt": contains stock symbol, name and price
 	2. "portfolio.txt": contains owned stock and shares, prev and current balance 
       and also the prev and current networth of all shares owned. 

These are required for the proper functioning of the program as they arent created automaticaly by program. 

Main Function:
     
     In the main function, I declared all variables that were going to be used.
     Then I initialized the variables approriaptly. 

     The main function is basically the menu program of the whole program, its where both the stock market and the portfolio are updated.

Other Functions in Header File:

    For all functions apart from the "printData" function I have passed parameters as references to the actual variables from the main function.

    i.e. 
        simple variable =  <type> (& <identifier>)
        1d array =  <type> (& <identifier>)[x]
        2d array =  <type> (& <identifier>)[x][y]


    "readData" Function:
        This fucntion reads from both the "companies.txt" and "portfolio.txt" file.     
    
    "writeData" Function:
    Writes all the updated data back to "companies.txt" and "portfolio.txt".

    "printData" Function:
    This is a generic function made both for portfolio and stock market. This is done by utilizing a bool variable to identify where its being called from, and so it prints stock info 	 
    appropriately.
		
    "displayMarket" Function
    This is the main function to display the live stock market, it calls upon "printData" function by setting the value of the bool variable to zero. Here we also prompt the user to choose an 
    option of the current platform. 
    
    "bestWorstPerformer" Function
    This function decides the best and worst performing stock in the market, it does this by simple comparison. 

    "addStock" Function
    This function is the adding stock function for the live market section of the program. The user enters the index of the desired stock and also chooses amount of shares that the user wants 
    to buy. If the user doesnt have the money to buy said amount of shares of a specific stock, the user is prompted to buy the amount that is in range.

    "removeStock" Function
    This function is the removing stock function for the live market section of the program.The function promts the user the stock the he/she can sell. The user enters the index of the desired 
    stock and also chooses amount of shares that the user wants to sell. If the user doesnt have the selected stock in porfolio, he is promted to do accordingly.

    "stockRandomizer" Function 
    The basic working of this function is to randomize the value of the stock by 15 percent. First, the value of current stock value is stored in previous stock variable. Then the random value 
    is generated by using 15% of the current stock value. Then another random value is generated that decides whether the last value is to be added or subtracted. This function calculates the 
    low and high of the selected stock by simple comparison with previous stock value.

    "displayPortfolio"
    This is the main function to display the portfolio, it calls upon "printData" function by setting the value of the bool variable to one. Here we also prompt the user to choose an option of 
    the current platform. 

    "addStockPort" Function
    This is the adding stock function of the portfolio part of the program. It only allows the user to buy more shares of the currently owned stocks. 

    "removeStockPort" Function
    This is the removing stock function of the portfolio part of the program. It only allows the user to sell shares of the currently owned stocks. 

    "calulateGainLoss" Function
    This function calculates the net value of all stock owned. This net value is then subtracted by the previous net value and then is stored in "gainLoss" variable. This polarity of the this 
    variable decides the "gain" or "loss" of the portfolio.
