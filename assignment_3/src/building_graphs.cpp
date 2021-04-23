/**
 * @file building_graphs.cpp
 * @author Egor Vlasov (e.vlasov@innopolis.university)
 * @brief 
 * @date 2021-04-23
 * 
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <class T>
class Vertex
{
    T value;
};

template <class T>
class Edge
{
    Vertex<T> *start;
    Vertex<T> *end;

    T weight;
};

template <class T>
class Graph_ADT
{
    virtual Vertex<T> *addVertex(T value) = 0;
    virtual void removeVertex(Vertex<T> &vertex) = 0;
    virtual Edge<T> *addEdge(Vertex<T> from, Vertex<T> to, T weight) = 0;
    virtual void removeEdge(Edge<T> edge) = 0;
    virtual vector<Edge<T>> edgesFrom(Vertex<T> vertex) = 0;
    virtual vector<Edge<T>> edgesTo(Vertex<T> vertex) = 0;
    virtual Vertex<T> findVertex(T value) = 0;
    virtual Edge<T> findEdge(T from_value, T to_value) = 0;
    virtual bool hasEdge(Vertex<T> v, Vertex<T> u) = false;
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
