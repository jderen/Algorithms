#include "RandomGenerator.h"
#include "TravellingSalesian.h"
#include "Time.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <iomanip>
#include <ctime>

int main() {

    srand(time(NULL));
    int choice=0;
    TravellingSalesian *travellingSalesian = NULL;
    RandomGenerator randomGenerator;
    Time time;

    while(choice!=6){


        std::cout << "	    Asemtryczny problem komiwojażera Jakub Dereń 235791 :" << std::endl;
        std::cout << "1.	Wczytanie danych z pliku" << std::endl;
        std::cout << "2.	Wyświetlenie wczytanych danych" << std::endl;
        std::cout << "3.	Przegląd zupełny" << std::endl;
        std::cout << "4.	Metoda podziału i ograniczeń" << std::endl;
        std::cout << "5.	Wygenerowanie losowej macierzy" << std::endl;
        std::cout << "6.	Przegląd zupełny [Testy]" << std::endl;
        std::cout << "7.	Metoda podziału i ograniczeń [Testy]" << std::endl;
        std::cout << "8    Zakończ" << std::endl;
        std::cout << "     Podaj numer: " << std::endl;

        std::cin >> choice;
        std::cout<< std::endl;

        switch(choice) {
            default: {
                std::cout << "Podałeś niepoprawny znak" << std::endl;
            }
            case 1: {
                std::cout << "Podaj nazwę pliku do otwarcia (wymagane .txt)";
                std::string name = "";
                std::cin >> name;
                travellingSalesian = new TravellingSalesian(name);
                break;
            }
            case 2: {
                if (travellingSalesian != NULL)
                    travellingSalesian->showMatrix();
                else
                    std::cout << "Brak danych do wyswietlenia" << std::endl;
                break;
            }
            case 3: {
                if (travellingSalesian != NULL) {
                    travellingSalesian->bruteForce(true);
                }
                else
                    std::cout << "Brak danych do wykonania przeglądu zupełnego" << std::endl;
                break;
            }
            case 4: {
                if (travellingSalesian != NULL)
                    travellingSalesian->branchAndBound(true);
                else
                    std::cout << "Brak danych do wykonania metody podziału i ograniczeń" << std::endl;
                break;
            }

            case 5:{
                std::cout <<"Podaj liczbę miast: "<< std::endl;
                int number;
                std::cin >> number;
                randomGenerator.getTravellingSalesman(number);
                break;
            }
            case 6:{
                int cityNumbers;
                int howMany;
                std::cout<<"Podaj liczbe miast: "<<std::endl;
                std::cin>>cityNumbers;
                std::cout<<"Podaj liczbe powtorzen: "<<std::endl;
                std::cin>>howMany;
                std::cout<<"Czas wykonywania testu: "<<time.timeBruteForce(cityNumbers,howMany,randomGenerator,false)<<" us"<<std::endl;
                break;
            }
            case 7:{
                int cityNumbers;
                int howMany;
                std::cout<<"Podaj liczbe miast: "<<std::endl;
                std::cin>>cityNumbers;
                std::cout<<"Podaj liczbe powtorzen: "<<std::endl;
                std::cin>>howMany;
                std::cout<<"Czas wykonywania testu: "<<time.timeBranchAndBound(cityNumbers,howMany,randomGenerator,false)<<" us"<<std::endl;
                break;
            }
            case 8:{
                return 0;
            }
        }
    }
    return 0;
}
