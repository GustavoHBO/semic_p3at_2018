#ifndef ROUTE_H
#define ROUTE_H

class Route{
  int *way;     // This point will indicate the way.
  int size;  // Indicates the size of way.
  bool mutated; // Indicates whether the route has already mutated.
  float fitness; // Have the fitness of the route.

  public:

    bool isMuted;

    Route();
    Route(int size);
    ~Route();

    int *getWay();
    int getSize();
    float getFitness();

    void setSize(int size);
    void setFitness(float fitness);
};
#endif