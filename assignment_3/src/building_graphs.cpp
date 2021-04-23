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
#include <vector>
#include <map>

using namespace std;

template <class V>
class Vertex
{
public:
    V value;

    Vertex(V value)
    {
        this->value = value;
    }
};

template <class E, class V>
class Edge
{
public:
    Vertex<V> *begin;
    Vertex<V> *end;

    E weight;

    Edge(Vertex<V> *begin, Vertex<V> *end, E weight)
    {
        this->begin = begin;
        this->end = end;
        this->weight = weight;
    }
};

template <class E, class V>
class Graph_ADT
{
    virtual Vertex<V> *addVertex(V value) = 0;
    virtual void removeVertex(Vertex<V> vertex) = 0;
    virtual Edge<E, V> *addEdge(Vertex<V> *from, Vertex<V> *to, E weight) = 0;
    virtual void removeEdge(Edge<E, V> edge) = 0;
    virtual vector<Edge<E, V>> edgesFrom(Vertex<V> vertex) = 0;
    virtual vector<Edge<E, V>> edgesTo(Vertex<V> vertex) = 0;
    virtual Vertex<V> findVertex(V value) = 0;
    virtual Edge<E, V> findEdge(V from_value, V to_value) = 0;
    virtual bool hasEdge(Vertex<V> v, Vertex<V> u) = 0;
};

template <class E, class V>
class AdjacencyMatrixGraph : public Graph_ADT<E, V>
{
public:
    vector<vector<Edge<E, V> *>> matrix;
    map<Vertex<V> *, int> vertex_index;

    Vertex<V> *addVertex(V value)
    {
        // new vertex creating
        auto new_vertex = new Vertex(value);

        // matrix resizing
        matrix.resize(this->matrix.size() + 1);
        for (int i = 0; i < matrix.size(); ++i)
        {
            matrix[i].resize(this->matrix.size());
        }

        // insertion in map
        vertex_index.insert({new_vertex, this->matrix.size() - 1});

        return new_vertex;
    }

    void removeVertex(Vertex<V> vertex)
    {
    }

    Edge<E, V> *addEdge(Vertex<V> *from, Vertex<V> *to, E weight)
    {
        auto new_edge = new Edge<E, V>(from, to, weight);

        int index1 = vertex_index.at(from);
        int index2 = vertex_index.at(to);

        matrix[index1][index2] = new_edge;

        // TODO
        //? matrix[index2][index1] = weight; reverse or not?
    }

    void removeEdge(Edge<E, V> edge)
    {
    }

    vector<Edge<E, V>> edgesFrom(Vertex<V> vertex)
    {
    }

    vector<Edge<E, V>> edgesTo(Vertex<V> vertex)
    {
    }

    Vertex<V> findVertex(V value)
    {
    }

    Edge<E, V> findEdge(V from_value, V to_value)
    {
    }

    bool hasEdge(Vertex<V> v, Vertex<V> u)
    {
    }

    void printMatrix()
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printSize()
    {
        cout << matrix.size() << endl;
    }
};

int main(int argc, char const *argv[])
{
    auto matrix = AdjacencyMatrixGraph<int, string>();

    auto vertex1 = matrix.addVertex("govno1");
    matrix.printSize();
    matrix.printMatrix();
    auto vertex2 = matrix.addVertex("govno2");
    matrix.printSize();
    matrix.printMatrix();
    matrix.addEdge(vertex1, vertex2, 10);
    matrix.printSize();
    matrix.printMatrix();
    cout << matrix.matrix[0][1]->weight;

    return 0;
}
