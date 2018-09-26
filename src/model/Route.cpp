#include "./../headers/Route.hpp"

Route::Route(){
    this->size = 0;
    this->mutated = false;
}

Route::Route(int size){
    this->size = size;
    this->way = new int[size];
    this->mutated = false;
}

Route::~Route(){
    // Delete the instance.
}

int *Route::getWay(){
    return this->way;
}

int Route::getSize(){
    return this->size;
}

void Route::setSize(int size){
    this->size = size;
}

void Route::setFitness(float fitness){
    this->fitness = fitness;
}