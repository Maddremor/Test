#include <stdio.h>

//Om någon undrar varför jag har lämnat in uppgiften femitelva gånger: det tog evigheter att få rätt antal radbrytningar.

int main(){
	int menuSelection;
	double currencyRate = 1.0;
	printf("Your shopping assistant\n");
	
	//1.Så länge användaren inte valt att avsluta programmet, upprepa följande:
	do {
		//1.1.Skriv ut menyn och läs in val
		printf("\n1. Set exchange rate in SEK (current rate: %.2f)", currencyRate);
		printf("\n2. Read prices in the foreign currency");
		printf("\n3. End\n");
		printf("\nGive your choice (1 - 3): ");
		scanf("%d", &menuSelection);
		printf("\n");
		
		//1.2.Om valet är att sätta valutakurs
		if (menuSelection == 1) {
			printf("Give exchange rate: ");
			//1.2.1.Sätt valutakurs
			scanf("%lf", &currencyRate);
		
		//1.3.Om valet är att läsa in priser
		} else if (menuSelection == 2) {
			double priceSum = 0;
			double price;
			
			//1.3.1.Så länge användaren inte vill avsluta inmatningen
			do {
				//1.3.1.1.Efterfråga pris eller klar med inmatning, samt om det är ett giltigt pris
				printf("Give price (finish with < 0): ");
				scanf("%lf", &price);
				if (price >= 0) {
					
					//1.3.1.2.Uppdatera summan
					priceSum = priceSum + price;
				} else {
					
					//1.3.2.Skriv ut summan i lokal valuta och i svenska kronor
					printf("\nSum in foreign currency: %.2f", priceSum);
					printf("\nSum in SEK: %.2f\n", (priceSum*currencyRate));
				}
			} while (price >= 0);
		
		//1.4.Om ogiltigt val
		} else if (menuSelection == 3){
			//2Avsluta programmet
			printf("End of program!\n\n");
		} else {
			//1.4.1.Skriv ut att det var ett ogiltigt val
			printf("Not a valid choice!\n");
		}
	} while (menuSelection != 3);
}
