/* Lukas Sjögren
 * CAS: lusj0002
 * CS-användare: 
 * 2016-10-
 */
#include <stdio.h>
#include <float.h>

//Intervallet av antal tillåtna domare. MIN_JUDGES bör ej underskrida 3 då algoritmen då inte fungerar, men MAX_JUDGES kan vara upp till INT_MAX.
#define MIN_JUDGES 3
#define MAX_JUDGES 10

void printIntro(){
	//printIntro() skriver ut information åt användaren. Uppdelad på flera print-satser för läsligare kod.
	printf("Program information\n");
	printf("The program reads in the number of judges and the score from each judge.\n");
	printf("Then it calculates the average score without regard to the lowest and \n");
	printf("highest judge score. Finally it prints the results (the highest, the \n");
	printf("lowest and the final average score).\n");
}

int getJudgeNo(){
	//getJudgeNo() ber anvädaren att mata in antal domare och loopar tills ett godkänt antal anges. Ej säkrad mot ickenumeriska inmatningar.
	int judgeNo = 0;
	do {
		printf("Number of judges (min %d and max %d judges)? ", MIN_JUDGES, MAX_JUDGES);
		scanf("%d", &judgeNo);
	} while ( ( judgeNo < MIN_JUDGES ) || ( judgeNo > MAX_JUDGES ) );
	return judgeNo;
}

void getScores(int judgeNo, double scores[]){
	//getScores() efterfrågar, och tar emot, inmatning av de poäng domarna ger. Poängen skrivs till pekaren scores[]. 
	for (int n = 0; n < judgeNo; n++){
		printf("Score from judge %d? ", (n + 1) );
		scanf("%lf", &scores[n]);
	}
}

void printScores(int judgeNo, double scores[]){
	//printScores() skriver ut alla domare och deras korresponderande poäng. 
	printf("Loaded scores:\n");
	for (int n = 0; n < judgeNo; n++){
		printf("Judge %d: %.1lf\n", (n + 1), scores[n] );
	}
}

void getResults(int judgeNo, double scores[], double *min, double *max, double *avg){
	//getResults() beräknar den hösta poängen, den lägsta poängen, och det medelvärde som ges utan de hösta och lägsta poängen.
	
	double sum = 0;		//sum deklareras som den totala poängsumman
	
	// Ger minimum och maximum det första elementets värde för att if-satserna i kommande for-loop ska fungera konsekvent.
	*min = scores[0];
	*max = scores[0];
	
	for (int n = 0; n < judgeNo; n++){
		//I loop adderas den n:te elementet i poängarrayen till summan,
		sum = sum + scores[n];
		
		//om elementet är större än tidigare element så lagras elementets värde som nytt poängmaximum i pekare
		if (scores[n] > *max){
			*max = scores[n];
		}
		
		//och om elementet är mindre än tidigare element så lagras elementets värde som nytt poängminimum i pekare.
		if (scores[n] < *min){
			*min = scores[n];
		}
	}
	
	//Den justerade snittpoängen ges till pekare *avg genom att subrahera minimum och maximum från totalsumman och dividera med antal domare sans de två extremvärdena.
	*avg = (sum - (*min + *max)) / (judgeNo - 2);
}

void printResults(double min, double max, double avg){
	//printResults() skriver ut högsta poäng, lägsta poäng och justerad snittpoäng. 
	//(Jag är medveten om att parametrarna inte behöver vara pekare, men det kändes trevligt med tanke på uppgiftens tema)
	printf("Final result:\n");
	printf("Highest judge score: %.1lf\n", max);
	printf("Lowest judge score: %.1lf\n", min);
	printf("Final average score: %.1lf\n", avg);
}

int main() {
	
	printIntro(); //Introduktionstext skrivs ut.
	printf("\n"); //Radbrytning. Kändes inte helt relevant i i någon av funktionerna. Att sätta dem i main() kändes ovanligt nog mer modulärt.
	
	int judgeNo= getJudgeNo();	//Antal domare läses in från användare.
	printf("\n");
	
	double scores[judgeNo];	//Array för poäng skapas där varje element korresponderar mot en domare.
	
	double averageScore, maxScore, minScore;	//Variabler för högsta, lägsta och snittpoäng initieras. 
																	//Högsta och lägsta får värdet +-DBL_MAX för att alla inmatade poäng ska kunna 
																	//beräknas även om poängskala går mot miljoner eller tillåter negativa poäng.
	
	getScores(judgeNo, scores);	//Användaren matar in poängen för varje enskild domare.
	printf("\n");
	
	printScores(judgeNo, scores);	//Poängen för varje enskild domare skrivs ut individuellt.
	printf("\n");
	
	getResults(judgeNo, scores, &minScore, &maxScore, &averageScore);	//Beräkningar på högsta, lägsta och justerade snittpoäng görs.
	
	printResults(minScore, maxScore, averageScore);	//Skriver ut högsta, lägsta och justerade snittpoäng.
	
	getchar();	//Av någon anledning ger enbart en getchar() ingen paus.
	getchar();	//Potentiellt att det ligger kvar något i bufferten?
	
	return 0;
}