/* Lukas Sjögren
 * CAS: lusj0002
 * CS-användare: tm14lsn
 * 2016-12-20
 */
#include <stdio.h>


int main(){
	int menuSelection;						//Initiera variabel för val i meny.
	double currencyRate = 1.0;				//Initiera variabel för valutakurs för den utländska valutan i förhållande till SEK
	printf("Your shopping assistant\n");	//Skriv ut intro till användaren.
	
	
	do {	//Do-while-loop som innehåller programmets funktionalitet.
		printf("\n1. Set exchange rate in SEK (current rate: %.2f)", currencyRate);	//Skriv ut menyn för de olika alternativen som användaren har. Inkluderar aktuell valutakurs.
		printf("\n2. Read prices in the foreign currency");
		printf("\n3. End\n");
		printf("\nGive your choice (1 - 3): ");
		
		scanf("%d", &menuSelection);	//Läs in det alternativ användaren valde.
		printf("\n");
		
		
		if (menuSelection == 1) {			//Om valet är att sätta valutakurs, dvs val 1
			printf("Give exchange rate: ");	//Efterfråga valutakurs
			scanf("%lf", &currencyRate);	//Läs in valutakurs
		
		} else if (menuSelection == 2)	{//Om valet är att läsa in priserna för anvädares olika inköp, dvs val 2.
			double priceSum = 0;		//Variabel för den totala summan av varupriser.
			double price;				//Variabel för priser för varje individuell vara. Skrivs över vid varje angett pris.
			
			
			do {											//Loop för inmatning av varor.
				printf("Give price (finish with < 0): ");	//Efterfråga varupris av anvädaren. 
				scanf("%lf", &price);						//Läs in pris.
				
				if (price >= 0) {					//Om varupriset är positivt och därmed ett giltigt numeriskt värde...
					priceSum = priceSum + price;	//...addera varupriset till den totala penningasumman.
				
				} else {														//Om priset inte är giltigt, dvs negativt...
					printf("\nSum in foreign currency: %.2f", priceSum);		//...skriv ut summan av alla inmatade priser...
					printf("\nSum in SEK: %.2f\n", (priceSum*currencyRate));	//...och skriv ut summan konverterad till SEK enligt inmatad valutakurs.
				}
			} while (price >= 0);	//Loop avslutas om angivet pris är negativt.
		
		} else if (menuSelection == 3){		//Om användaren väljer att avsluta programmet...
			printf("End of program!\n\n");	//...skriv ut detta till användaren.
		} else {								//Om menyval inte är något av de existerande alternativen (1, 2 eller 3)...
			printf("Not a valid choice!\n");	//...informera användaren om detta.
		}
	} while (menuSelection != 3);	//Loop bryts om menyval för att avsluta program är valt.
}