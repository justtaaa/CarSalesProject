//No warnings on scanf
#define _CRT_SECURE_NO_WARNINGS

//Required libraries
//output, input, scanf, printf, files
#include <stdio.h>
// boolean algebra, do not need to define true and false
#include <stdbool.h>
// system("cls") 
#include <Windows.h>
// compare strings (strcmp), copy strings (strcpy), join strings (strcat), and all other actions with strings
#include <string.h>
//error-check function
#include <errno.h>
// isalpha function
#include <ctype.h>

//Constants
#define LEGAL_AGE 18 // took this idea from external resourse during my research before coding
#define MAX_AGE 120
#define DISCOUNT_PERCENTAGE 0.05f
#define ARR_LEN 8
#define STRING_LEN 100;

//definig files
#define INFO "info.txt"
#define DATA "data.txt"

//Menu Options
#define MENU_OPTION_VIEW_STOCK 'a'
#define MENU_OPTION_BUY_CAR 'b'
#define MENU_OPTION_VIEW_SALES 'c'
#define MENU_OPTION_EXIT 'x'

//Variables
short  userAge = 0, carsNeeded = 0, stockNeeded = 0, discountValue = 0; 
int totalPrice = 0, totalSales = 0;
char userChoice;
char response;
char fullName[50];

// external int
extern int errno;

// struct is used for store customer's data temporary
//Information taken from Pluralsight
struct Customers {
	char name[80];
	short carsNeded;
	short age;
	int price;
	short discountGiven;
	short discount;
	short amount;
};

//Arrays
int carPrices[ARR_LEN];
char carModels[ARR_LEN][100];
int carStocks[ARR_LEN];
int carSumsSales[ARR_LEN];
int carCountSales[ARR_LEN];

// declaration of arrays
void arrayDeclar() {

	int errorNumber;

	// open existing file to read it and get data to put in arrays which will be used in code later
	FILE* fr = fopen("info.txt", "r");

	// detection of error. Will react if file could not be opened 
	if (fr == NULL) {
		errorNumber = errno;
		printf(" Error!\n ErrNo = %d", errorNumber);
		perror("\n Error Message:\n");
		printf(" Error opening %s, %s.", INFO, strerror(errorNumber));
	}

	// if everything is alright code will declare all needed arrays 
	else {

		//car prices based on real values
		for (int i = 0; i < ARR_LEN; i++) {
			fscanf(fr, "%d", &carPrices[i]);
		}

		//model types
		fgets(carModels[0], 100, fr);
		for (int i = 0; i < ARR_LEN; i++) {
			fgets(carModels[i], 100, fr);
			carModels[i][strlen(carModels[i]) - 1] = '\0';
		}

		//initial stocks
		for (int i = 0; i < ARR_LEN; i++) {
			fscanf(fr, "%d", &carStocks[i]);
		}
		//sum of sales
		for (int i = 0; i < ARR_LEN; i++) {
			fscanf(fr, "%d", &carSumsSales[i]);
		}

		// number of sales
		for (int i = 0; i < ARR_LEN; i++) {
			fscanf(fr, "%d", &carCountSales[i]);
		}

		fclose(fr);

	}

	
}

// clearing the screen for user conveniense 
void clrsys() {
	system("cls");
	//Clear System
}


//Main screen of the programme
// user can see available options to choose
void menu() {

	clrsys();
	printf("  Welcome to Lexus cars! What are you intrested in today?\n\n"); // greeting the customer
	printf("  Please choose an option.\n\n");
	printf("  Menu:\n");
	printf("  a. View Car Stocks\n");
	printf("  b. Buy Cars\n");
	printf("  c. View Sales Data\n");
	printf("  x. Exit\n");

}

// sorting data in descending order
// bubble sorting
void sorter() {

	int tmp; // temporary value
	char c[100];

	for (int i = 0; i < ARR_LEN - 1; i++) {

		for (int j = i + 1; j < ARR_LEN; j++) {

			if (carStocks[i] < carStocks[j]) {
				
				//Sorting of car stocks
				tmp = carStocks[i];
				carStocks[i] = carStocks[j];
				carStocks[j] = tmp;

				//Sorting of car prices
				tmp = carPrices[i];
				carPrices[i] = carPrices[j];
				carPrices[j] = tmp;
				
				//Sorting sum of saled cars
				tmp = carSumsSales[i];
				carSumsSales[i] = carSumsSales[j];
				carSumsSales[j] = tmp;

				//Sorting of number of sales
				tmp = carCountSales[i];
				carCountSales[i] = carCountSales[j];
				carCountSales[j] = tmp;

				//Sorting of car models
				strcpy(c, carModels[i]);
				strcpy(carModels[i], carModels[j]);
				strcpy(carModels[j], c);
			
			}
		}
	}
}

//Change values in file "info.txt" after sales
void redactInfo() {

	int errorNumber; 
	sorter(); // sorting data in decending order

	FILE* fw = fopen("info.txt", "w");

	//Checking for errors with file "info.txt"
	if (fw == NULL) {
		errorNumber = errno;
		printf(" Error!\n ErrNo = %d", errorNumber);
		perror("\n Error Message:\n");
		printf(" Error opening %s, %s.", INFO , strerror(errorNumber));

	}
	//No problems with working with the file
	else {

		//car prices based on real values
		for (int i = 0; i < ARR_LEN; i++) {
			fprintf(fw, "%d\n", carPrices[i]);
		}

		//model types
		for (int i = 0; i < ARR_LEN; i++) {
			fprintf(fw, "%s\n", carModels[i]);
		}
		
		//initial stocks
		for (int i = 0; i < ARR_LEN; i++) {
			fprintf(fw, "%d\n", carStocks[i]);
		}
		
		//sum of sales
		for (int i = 0; i < ARR_LEN; i++) {
			fprintf(fw, "%d\n", carSumsSales[i]);
		}

		//number of cars sold
		for (int i = 0; i < ARR_LEN; i++) {
			fprintf(fw, "%d\n", carCountSales[i]);
		}

		fclose(fw);
	}
	
}

//outputs the car stocks
void menuOptionViewStocks() {

	sorter();

	for (int k = 0; k < ARR_LEN; k++) {

		printf("  %d.", k);
		printf("%s -- ", carModels[k]);
		printf("%d GBP -- ", carPrices[k]);
		printf("%d Remaining \n", carStocks[k]);
	}

}

//"Buy cars" page
int menuOptionBuyCars() {

	//write something...
	struct Customers newCustomer;

	// output cars data
	// ask customer for their choice
	// filtering for numbers only
	do {
		clrsys();
		menuOptionViewStocks();
		printf("  Choose the desired car by pressing one of the numbers: \n");
		if (scanf("%hd", &carsNeeded) != 1) {
			getchar();
			carsNeeded = -1;
		}
	} while (carsNeeded < 0 || carsNeeded > 9);

	// if there's no cars in stock, write "sorry message"
	if (carStocks[carsNeeded] == 0) {

		printf("We are sorry this car is out of stock.\n");
		return 0;
	}

	clrsys();

	//Give customer a choice for amount of cars he/she needs
	//Filter the value they type  (only numbers)
	do {
		clrsys();
		printf("This car costs %d GBP. How many do you need? ", carPrices[carsNeeded]);
		if (scanf("%hd", &stockNeeded) != 1) {
			getchar();
			stockNeeded = -1; 
		}

	} while (stockNeeded < 0); 


	//Case if customer needs more cars than available 
	//Filtering of values they type
	while (stockNeeded > carStocks[carsNeeded]) {
		clrsys();

		// "Sorry" message and giving second option
		do {
			printf("We are sorry, we do not possess the required amount of %s.\n", carModels[carsNeeded]);
			printf("Do you wish to purchase less? Answer '+' or '-': ");
			scanf("%c", &response);
		} while (response != '+' && response != '-');

		if (response == '+') {

			do
			{
				printf("How many do you need? ");
				if (scanf("%hd", &stockNeeded) != 1) {
					getchar();
					stockNeeded = -1;
				}
			} 
			while (stockNeeded < 0);
		}

		else {
			return 0;
		}
	}
	
	// asking and getting customer's name
	// Filtering: letters only
	// information about "isalpha" is from "Modern C", Jens Gustedt
	getchar();
	while (true) {
		bool flag = true;
		clrsys();
		printf("Please enter your full name: ");
		fgets(newCustomer.name, 50, stdin);
		//scanf("%s", newCustomer.name);
		for (int i = 0; i < strlen(newCustomer.name); i++) {
			if (newCustomer.name[0] != '\0' && newCustomer.name[0] != '\n') {
				if (!isalpha(newCustomer.name[i]) && newCustomer.name[i] != '\n' && newCustomer.name[i] != ' ') {
					flag = false;
					continue;
				}
				if (newCustomer.name[i] == '\n') {
					newCustomer.name[i] = '\0';
				}
			}
			else {
				flag = false;
			}
		}
		if (flag) {
			break;
		}
	}

	//Asking and getting customer's age
	//Filtering: numbers only
	//Detection if customer is old enough to purchase the car
	do
	{
		clrsys();
		printf("How old are you?  ");
		if (scanf("%hd", &newCustomer.age) != 1) {
			getchar();
			newCustomer.age = -1;
		}
	} while (newCustomer.age > MAX_AGE || newCustomer.age < 0);

	if (newCustomer.age < LEGAL_AGE) {
		printf("You are too young to legally purchase a car. We are sorry.");
		return 0;
	}
	
	// updating data
	newCustomer.carsNeded = carsNeeded;
	newCustomer.amount = stockNeeded;
	newCustomer.price = carPrices[carsNeeded] * newCustomer.amount;
	newCustomer.discountGiven = false;
	carStocks[carsNeeded] -= stockNeeded;

	// Checking discount condition
	if (newCustomer.amount != 0) {
		do {
			clrsys();
			printf("Was your previous car Lexus? Answer '+' or '-':  "); // Loyalty discount
			scanf(" %c", &response);

			if (response == '+') {
				newCustomer.discountGiven = true;
				printf("\nYou are eligible for a discount.\n");
			}

			else if (response == '-') {
				printf("\nSorry you are not eligible for a discount.\n");
			}

		} while (response != '+' && response != '-');

	}
	if (newCustomer.discountGiven == true) {
		newCustomer.price *= (1 - DISCOUNT_PERCENTAGE);
	}

	// updating data
	//"Thank you" message for customer
	carCountSales[carsNeeded] += newCustomer.amount;
	carSumsSales[carsNeeded] += newCustomer.price;
	

	if (newCustomer.discountGiven == true) {
		printf("\n\nThank You!\n");
		printf("You have bought %hd %s cars.\n", newCustomer.amount, carModels[carsNeeded]);
		printf("Total cost is %d GBP.\n", newCustomer.price);
		printf("Discount: % hd GDB\n\n", &newCustomer.discount);
		printf("We are glad that You chose us again! Get 5%% discount on your next purchase!\n");
	}
	else {
		printf("\n\nThank You!\n");
		printf("You have bought %hd %s cars.\n", newCustomer.amount, carModels[carsNeeded]);
		printf("Total cost is %d GBP.\n\n", newCustomer.price);
		printf("We are glad that You chose us! You have not got discount this time, but You will get 5%% discount on your next purchase!\n");

	}
	
	

	totalSales += totalPrice;

	int errorNumber;
	FILE* fp = fopen("data.txt", "a+");

	//Checking for mistakes with file "data.txt"
	if (fp == NULL) {
		errorNumber = errno;
		printf(" Error!\n ErrNo = %d", errorNumber);
		perror("\n Error Message:\n");
		printf(" Error opening %s, %s.", DATA, strerror(errorNumber));
	}

	//Writing data about sales in separate file "data.txt"
	else {
		fprintf(fp, "Model: %s, ", &carModels[carsNeeded]);
		fprintf(fp, "Name: %s, ", &newCustomer.name);
		fprintf(fp, "Age: %hd, ", newCustomer.age);
		if (newCustomer.discountGiven == true) {
			fprintf(fp, "Loyalty discount, ");
		}
		else {
			fprintf(fp, "First Lexus car, ");
		}

		fprintf(fp, "Amount: %hd, ", newCustomer.amount);
		fprintf(fp, "Price: %d, ", carPrices[carsNeeded]);
		fprintf(fp, "Total price: %d, ", newCustomer.price);

		if (newCustomer.discountGiven == true) {
			fprintf(fp, "Discount: %hd\n", &newCustomer.discount);
		}
		else {
			fprintf(fp, "No Discount Applied\n");
		}

		fclose(fp);

	}
	redactInfo();
	return 0;
}

//Sorting "View sales"  in descending order
//bubble sorting
void sorterSalesView() {
	int tmp; // temporary value
	char c[100];
	for (int i = 0; i < ARR_LEN - 1; i++) {

		for (int j = i + 1; j < ARR_LEN; j++) {

			if (carSumsSales[i] < carSumsSales[j]) {

				//Sorting of car stocks
				tmp = carStocks[i];
				carStocks[i] = carStocks[j];
				carStocks[j] = tmp;
				
				//Sorting of car prices
				tmp = carPrices[i];
				carPrices[i] = carPrices[j];
				carPrices[j] = tmp;

				//Sorting sum of saled cars
				tmp = carSumsSales[i];
				carSumsSales[i] = carSumsSales[j];
				carSumsSales[j] = tmp;

				//number of cars sold
				tmp = carCountSales[i];
				carCountSales[i] = carCountSales[j];
				carCountSales[j] = tmp;

				//Sorting of car models
				strcpy(c, carModels[i]);
				strcpy(carModels[i], carModels[j]);
				strcpy(carModels[j], c);
				
			}
		}
	}
}


// output of sales data 
void menuOptionViewSales() {

	sorterSalesView();

	for (int k = 0; k < ARR_LEN; k++) {
		printf("  %d.", k);
		printf("Model: %s\n", carModels[k]);
		printf("Price: %d GBP\n", carPrices[k]);
		printf("Remaining: %d\n", carStocks[k]);
		printf("Sold %d for the amount of %d GBP\n\n", carCountSales[k], carSumsSales[k]);
		printf("\nCustomers:\n");
		printf("______________________________________\n\n");

		// working with file "data.txt", detection of mistakes
		int flag = 1;
		int errorNumber;

		FILE* fp = fopen("data.txt", "r");
		if (fp == NULL) {
			errorNumber = errno;
			printf(" Error!\n ErrNo = %d", errorNumber);
			perror("\n Error Message:\n");
			printf(" Error opening %s, %s.", DATA, strerror(errorNumber));

		}
		else {
			while (!feof(fp)) {
				char str[200];
				fgets(str, 200, fp);
				if (strstr(str, carModels[k]) != NULL) {
					int j = 0;
					while (str[j] != '\0') {
						if (str[j] == ',') {
							printf("\n");
							j += 2;
						}
						else {
							printf("%c", str[j]);
							j++;
						}

					}
					printf("______________________________________\n\n");
					flag = 0;
				}
				int j;
				for (j = 0; j < 200; j++) {
					str[j] = '\0';
				}

			}
			if (flag) {
				printf("No customers!\n______________________________________\n\n");
			}
			fclose(fp);

		}
	}
}

void main() {
	arrayDeclar();
	do {
	
		menu();
		//Get user input
		userChoice = getchar();
	    // changes the pages through switch option
		switch (userChoice) {
			
			// user pressed 'a'
		case MENU_OPTION_VIEW_STOCK:
			clrsys();
			menuOptionViewStocks();
			break;

			//user pressed 'b'
		case MENU_OPTION_BUY_CAR:
			clrsys();
			menuOptionBuyCars();
			break;

			//user pressed 'c'
		case MENU_OPTION_VIEW_SALES:
			clrsys();
			menuOptionViewSales();
			break;

			//user pressed 'x'
		case MENU_OPTION_EXIT:
			clrsys();
			printf("Thank you for choosing Car Sales Inc.. We welome you again. Good Bye!");
			break;

			//pressed invalid option
		default:
			clrsys();
			printf("Please enter a valid option.");
		}
		if (userChoice == MENU_OPTION_EXIT) {
			printf("\n\nPress Enter to exit...");
		}
		else {
			printf("\n\nPress Enter to return to the Menu...");
		}
		getchar();
		getchar();
	} while (userChoice != MENU_OPTION_EXIT);
	clrsys();

	printf("\n\nHave a good day!\n\n");
}