#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include "windows.h"
#include "codesLIB.h"

#define PatternNum 18
#define PatternChars 12

using namespace std;

/*   DEFINISCO PROBABILITA' CHE ESCA UN VALORE SOTTOFORMA DI INT IN PERCENTUALE   */
int NumPerc[12] = {
        44, 33, 33, 11,
        33, 11, 55, 44,
        22, 22, 33, 44
};

/*   CREO UN ARRAY CHE OSPITERA' UN SECONDO ARRAY GENERATO CASUALMENTE   */
int secondPatternGroup[18][12];

/*   DEFINISCO ARRAY DI CARATTERI E NUMERI PER LE FUNZIONE CHE ANDRANNO A GENERARE I CODICI   */
char  a[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char b[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char c[] = {"0123456789"};

/*   DEFINISCO I PATTERN GIA' STUDIATI SOTTO FORMA DI MATRICE DI BIT   */
int patterns[18][12] = {
        0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0,
        1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
        0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1
};

/*   DEFINISCO UN ARRAY PER CONTENERE I VALORI SU CUI STO LAVORANDO   */
int currentPattern[12];

/*   VALORE RANDOM %   */
bool PercentValue[100];

//PROTOTIPI DI FUNZIONE
void showMenu();
void getPattern();
void generateRand();
void readPatternArray();
int revealPattern();
int checkPattern();
int generateFromCol(int colNumber);
int generateFromNum(int colNumber, int rowNumber);
string currentdate();


int main() {
    srand(time(NULL));
    
    int amount = 1, i = 0;

	cout << endl;
	system("cls");
	
	
	/*****************************************************************************/
	string date_ = currentdate();
    string date = date_;
	
	string mydir;
    string mydir2;
    mydir = "Results";
    mkdir(mydir.c_str());
    mydir2 = "Results//" + date;
    mkdir(mydir2.c_str());
    
    fstream codici;
	string path = "Results//" + date + "//PSN CODES.txt";
    codici.open(path.c_str(),  ios::out);
    /*****************************************************************************/
	
    /*   TRASFORMO IL CONTENUTO DELLA MATRICE PATTERN E LA STAMPO A VIDEO INSIEME AL SET DI PATTERN GENERATI   */
    readPatternArray();
    
    /*   STAMPO A VIDEO IL MENU DI SCELTA CON LE OPZIONI   */
    showMenu();

    getPattern();
    checkPattern();
    cout << endl;

    return 1;
}


int revealPattern() {
    int i = 0, tempN = 0;
    char tempC;
    
    fstream codici;

    for(; i < 12; i++) {
        if(i == 4 || i == 8) {
            cout << "-";
        }
        if(currentPattern[i] == 0) {
            tempN = rand() % 10;
            cout << tempN;
            codici << tempN;
        } else {
            tempC = (rand() % 26) + 65;
            cout << tempC;
            codici << tempC;
        }
    }
    cout << endl;
    codici << endl;
}

int checkPattern() {
    int i = 0, j = 0, corresponding = 0;
    //cout << "______Corresponding Check______" << endl;

    for (i = 0; i < PatternNum; ++i) {
        for (j = 0; j < PatternChars; ++j) {
            if(currentPattern[j] == patterns[i][j]) {
                corresponding += 1;
                //cout << corresponding << endl;
            }
        }
    }
    //cout << corresponding << endl;
    return corresponding;
}

string currentdate()
{
    /*   Utilizzo la libreria 'time.h' per farmi dire l'ora dal sistema (lavora in ticks)   */
    time_t t = time(0);
    tm* now = localtime(&t);		// Prendo l'address di t perchè dovrebbe essere riservato

    /*   Inizializzo le variabili che mi servono   */
    char* date;
    int year, month, day;

    /*   Uso una funzione di libreria con un metodo imparato a scuola per agire sulle classi degli header ("now->" risulta molto simile a "this->")   */
    year = (now->tm_year + 1900);
    month = (now->tm_mon + 1);
    day = now->tm_mday;

    /*   "sprintf" funziona come un printf ma salva il contenuto generato in una stringa, quella passata nel primo parametro   */
    sprintf(date, "%d-%d-%d", day, month, year);


    return date;
}

void readPatternArray() {
	int i = 0, j = 0, k = 0, l = 0;
	
	//cout << "Importing Pattern's Database..." << '\n' << endl;
	cout << '\t'<< '\t' << "Current Database: " << '\t' << '\t' << "Generated Database: " << '\n' << endl;
	
	
	for(i = 0; i < 18; i++) {
		cout << '\t';
		
		cout << "    |    ";
		
		cout << l << ")" << '\t';
		
		for(k = 0; k < 12; k++) {
			if(k == 4 || k == 8) {
           		cout << "-";
	        }
	        if(patterns[i][k] == 0) {
	            cout << "0";
	        } else {
	            cout << "X";
	        }
		}
		
		cout << "    |    ";
		
		
		cout << l << ")" << '\t';
		//l++;
		
		for(j = 0; j < 12; j++) {
			if((j == 4) || (j == 8)) {
				cout << "-";
			}
			
			if(rand() % 2 == 0) {
				secondPatternGroup[i][j] = 0;
				cout << "0";
			} else {
				secondPatternGroup[i][j] = 1;
				cout << "X";
			}
			
			//cout << secondPatternGroup[i][j];			
		}
		
		l++;
		cout << endl;
	}
}


/********************************
 *		   	GENERATERAND		*
 *								*
 *CREO UN SECONDO SET DI PATTERN*
 ********************************/

void generateRand() {
	int i = 0, j = 0, k = 0;
	
	for(i = 0; i < 18; i++) {
		for(j = 0; j < 12; j++) {
			if(rand() % 2 == 0) {
				secondPatternGroup[i][j] = 0;
			} else {
				secondPatternGroup[i][j] = 1;
			}
			
			cout << secondPatternGroup[i][j];			
		}
		
		cout << endl;
	}
}


/********************************
 *		   	SHOWMENU			*
 *								*
 *		MOSTRO IL MENU IN LOOP	*
 ********************************/

void showMenu() {
	int select = 0, colNum = 0, rowNum = 0, patternNum = 0;
	cout << "         " << "----------------------------------------------------------------" << endl;
	cout << "1) Generate a new Set of Patterns." << endl;
	cout << "2) Select a Column." << endl;
	cout << "3) Select a Pattern." << endl;
	
	cin >> select;
	switch (select) {
		case 1:
			system("cls");
			getPattern();
			readPatternArray();
			showMenu();
			
			break;
			
		case 2:															/*   select column   */
			cout << "Insert column number (0 = LEFT, 1 = RIGHT): ";
			cin >> colNum;
			
			generateFromCol(colNum);
			
			break;
			
		case 3:															/*   select pattern   */
			cout << "Insert column number (0 = LEFT, 1 = RIGHT): ";
			cin >> colNum;
			cout << "Insert row number: ";
			cin >> rowNum;
			
			generateFromNum(colNum, rowNum);
			
			break;
	}
}


/********************************
 *			GETPATTERN			*
 *								*
 *	CREO NUOVO PATTERN SULLA %	*
 *			IN NUMPERC			*
 ********************************/

void getPattern() {
    srand(time(NULL));

    int i = 0, j = 0, cont = 0;

        for(; i < 100; i++) {
            if(rand() % 2 == 0 && NumPerc[j] > 0) {
                PercentValue[i] = true;
                NumPerc[j]--;
                cont++;
                //cout << cont << ": " << "0" << endl;
            } else {
                PercentValue[i] = false;
                //cout << "X" << endl;
            }
        }

        for(int k = 0; k <= 12; k++) {
            int tempNum = 0;
            tempNum =(rand() % 100 + 1);

            if(PercentValue[tempNum] == true) {
                currentPattern[k] = 0;
            } else {
                currentPattern[k] = 1;
            }
        }

}


int generateFromCol(int colNum) {
	int i = 0;
	int j = 0, tempN = 0;
	char tempC;
	int amount = 0;
	int cont = 0;
	
	cout << "Insert amount of codes: ";
	cin >> amount;
	
	fstream codici;
	string date_ = currentdate();
    string date = date_;
    
	string path = "Results//" + date + "//PSN CODES.txt";
    codici.open(path.c_str(),  ios::out);
    
	clock_t t1, t2;
	t1 = clock();

	if(colNum == 0) {
		do {
			cont++;
			for(i = 0; i < 12; i++) {
				currentPattern[i] = patterns[i][j];
			}
		
		    for(i = 0; i < 12; i++) {
		        if(i == 4 || i == 8) {
		            //cout << "-";
		            codici << "-";
		        }
		        if(currentPattern[i] == 0) {
		            tempN = rand() % 10;
		            //cout << tempN;
					codici << tempN;
		        } else {
		            tempC = (rand() % 26) + 65;
		            //cout << tempC;
		            codici << tempC;
		        }
		    }
		    //cout << endl;
		    codici << endl;
		    
		    if(cont >= 18) {
		    	cont = 0;
			}
			j++;
			
		} while(j < amount);
			
	} else {
		do {
			cont++;
			for(i = 0; i < 12; i++) {
				currentPattern[i] = secondPatternGroup[i][j];
			}
		
		    for(i = 0; i < 12; i++) {
		        if(i == 4 || i == 8) {
		            cout << "-";
		            codici << "-";
		        }
		        if(currentPattern[i] == 0) {
		            tempN = rand() % 10;
		            cout << tempN;
		            codici << tempN;
		        } else {
		            tempC = (rand() % 26) + 65;
		            cout << tempC;
		            codici << tempC;
		        }
		    }
		    cout << endl;
		    codici << endl;
		    
		    if(cont >= 18) {
		    	cont = 0;
			}
			j++;
			
		} while(j < amount);	
	}
	
	t2 = clock();
	cout << "Codes generated in : " << (t2-t1) / ((double)CLOCKS_PER_SEC) << "sec" << endl;
	
}

int generateFromNum(int colNumber, int rowNumber) {
	int rowCont = 0, i = 0, j = 0, k = 0, amount = 0, cont = 0, tempN = 0;
	char tempC;
	
	cout << "Insert amount of codes: ";
	cin >> amount;
	cout << endl;
	
	string date_ = currentdate();
    string date = date_;
    
    fstream codici;
	string path = "Results//" + date + "//PSN CODES.txt";
    codici.open(path.c_str(),  ios::out);
	
	clock_t t1, t2;
	t1 = clock();
	
	if(colNumber == 0) {
		for(k = 0; k < 12; k++) {
			if(k == 4 || k == 8) {
           		//cout << "-";
	        }
	        if(patterns[rowNumber][k] == 0) {
	            //cout << "0";
	            currentPattern[k] = 0;
	        } else {
	            //cout << "X";
	            currentPattern[k] = 1;
	        }
		}
		
		i++;
	} else {
		for(k = 0; k < 12; k++) {
			if(k == 4 || k == 8) {
           		//cout << "-";
	        }
	        if(secondPatternGroup[rowNumber][k] == 0) {
	            //cout << "0";
	            currentPattern[k] = 0;
	        } else {
	            //cout << "X";
	            currentPattern[k] = 1;
	        }
		}
		
		i++;
	}
	
	do {
		cont++;
	
	    for(i = 0; i < 12; i++) {
	        if(i == 4 || i == 8) {
	            cout << "-";
	            codici << "-";
	        }
	        if(currentPattern[i] == 0) {
	            tempN = rand() % 10;
	            cout << tempN;
	            codici << tempN;
	        } else {
	            tempC = (rand() % 26) + 65;
	            cout << tempC;
	            codici << tempC;
	        }
	    }
	    
	    cout << endl;
	    codici << endl;
	    
	    if(cont >= 18) {
	    	cont = 0;
		}
		
		j++;
			
	} while(j < amount);
	
	t2 = clock();
	cout << "Codes generated in : " << (t2-t1) / ((double)CLOCKS_PER_SEC) << "sec" << endl;
}
