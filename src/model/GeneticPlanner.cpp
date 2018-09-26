#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

#include "./../headers/GeneticPlanner.hpp"
#include "./../headers/Route.hpp"

GeneticPlanner::GeneticPlanner(){
    srand(time(NULL));
}

GeneticPlanner::~GeneticPlanner(){
    //Delete que instance
}

int GeneticPlanner::randomInt(int minValue, int minMax){
    return (rand()%(minMax-minValue)) + minValue;
}

vector<Route*> GeneticPlanner::genRandomPopulation(){
    std::vector<Route*> population;
    Route *route;
    for(int i = 0; i < TAMANHOPOPULACAOINICIAL; i++){
        route = new Route(TAMANHOMAXIMOVETOR);
        for(int j = 0; j < TAMANHOMAXIMOVETOR-1; j+=2){
            route->getWay()[j] = randomInt(-TAMANHOMAXIMOMOVIMENTACAO, TAMANHOMAXIMOMOVIMENTACAO);
            route->getWay()[j+1] = randomInt(-TAMANHOMAXIMOGIRO, TAMANHOMAXIMOGIRO);
        }
        population.push_back(route);
    }
    return population;
}

void GeneticPlanner::fitness(vector<Route*> population){
    float fitness = 0;
    int distance = 0;
    int *way;
    Route *route;
    for(int i = 0; i < population.size(); i++){
        route = population.at(i);
        way = route->getWay();
        for (int j = 0; j < route->getSize(); j++){
            if(j%2==0)
                distance += abs(way[j]);
        }
        route->setFitness((distance*0.4)-(route->getSize()*0.6));
    }
}

void GeneticPlanner::mutation(vector<Route*> *population){
    Route *route;
    for(int i = 0; i < (TAMANHOPOPULACAO*TAXAMUTACOES)/100; i++){
        int j = randomInt(0, TAMANHOPOPULACAO-1);
        route = population->at(j);
        if(route->getWay()[1] == 0){
            for(int k = 0; k < (TAXAMUTACAOINDIVIDUO*route->getWay()[0])/100; k++){
                int gene = randomInt(2, route->getWay()[0]);
                if(gene%2 == 0){
                    route->getWay()[gene] = route->getWay()[gene] + randomInt(-TAXAMUTACAOMOVIMENTO, TAXAMUTACAOMOVIMENTO);
                } else{
                    route->getWay()[gene] = route->getWay()[gene] + randomInt(-TAMANHOMAXIMOMUTACAOGIRO, TAMANHOMAXIMOMUTACAOGIRO);
                }
            }
        }
    }
}