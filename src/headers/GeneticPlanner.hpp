#ifndef GENETICPLANNER_H
#define GENETICPLANNER_H

#include "Route.hpp"

using namespace std;

class GeneticPlanner{

    public:
        static const int TAMANHOMAXIMOVETOR = 100;
        static const int TAMANHOMINIMOVETOR = 30;
        static const int TAMANHOMAXIMOMOVIMENTACAO = 300;
        static const int TAMANHOMAXIMOGIRO = 180;

        static const int TAMANHOMAXIMOMUTACAOMOVIMENTO = 10;
        static const int TAMANHOMAXIMOMUTACAOGIRO = 2;

        static const int TAMANHOPOPULACAOINICIAL = 100;
        static const int TAMANHOPOPULACAO = 100;

        static const int TAXAMUTACOES = 50;
        static const int TAXAMUTACAOINDIVIDUO = 40;
        static const int TAXAMUTACAOMOVIMENTO = 1;

        GeneticPlanner();
        ~GeneticPlanner();

        vector<Route*> genRandomPopulation();

        void mutation(vector<Route*> *population);

        int randomInt(int minValue, int maxValue);
        void fitness(vector<Route*> population);
};
#endif