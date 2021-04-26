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

/**
 * @brief vertex class
 * 
 * @tparam V type of vertex value
 */
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

/**
 * @brief edge class
 * 
 * @tparam E type of edge weight
 * @tparam V type of vertex value
 */
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

/**
 * @brief interface of graph
 * 
 * @tparam E type of edge weight
 * @tparam V type of vertex value
 */
template <class E, class V>
class Graph_ADT
{
    virtual Vertex<V> *addVertex(V value) = 0;
    virtual void removeVertex(Vertex<V> *vertex) = 0;
    virtual Edge<E, V> *addEdge(Vertex<V> *from, Vertex<V> *to, E weight) = 0;
    virtual void removeEdge(Edge<E, V> *edge) = 0;
    virtual vector<Edge<E, V> *> edgesFrom(Vertex<V> *vertex) = 0;
    virtual vector<Edge<E, V> *> edgesTo(Vertex<V> *vertex) = 0;
    virtual Vertex<V> *findVertex(V value) = 0;
    virtual Edge<E, V> *findEdge(V from_value, V to_value) = 0;
    virtual bool hasEdge(Vertex<V> *v, Vertex<V> *u) = 0;
};

/**
 * @brief graph class
 * 
 * @tparam E type of edge weight
 * @tparam V type of vertex value
 */
template <class E, class V>
class AdjacencyMatrixGraph : public Graph_ADT<E, V>
{
public:
    // Adjacency Matrix
    vector<vector<Edge<E, V> *>> matrix;

    // map {ref_to_vertex : index in matrix}
    map<Vertex<V> *, int> vertex_index;

    // map {name : ref}
    map<string, Vertex<V> *> vertex_name;

    /**
     * @brief new vertex adding
     * 
     * @param value name of vertex
     * @return Vertex<V>* ref to vertex
     */
    Vertex<V> *addVertex(V value)
    {
        // new vertex creating
        auto new_vertex = new Vertex(value);

        // matrix resizing
        matrix.resize(matrix.size() + 1);
        for (int i = 0; i < matrix.size(); ++i)
        {
            matrix[i].resize(matrix.size());
        }

        // insertion in map
        vertex_index.insert({new_vertex, matrix.size() - 1});
        vertex_name.insert({new_vertex->value, new_vertex});

        return new_vertex;
    }

    /**
     * @brief vertex removing
     * 
     * @param vertex ref to vertex
     */
    void removeVertex(Vertex<V> *vertex)
    {
        int index = vertex_index[vertex];
        for (auto &i : vertex_index)
        {
            if (i.second > index)
            {
                i.second -= 1;
            }
        }

        matrix.erase(matrix.begin() + index);
        for (auto &i : matrix)
        {
            i.erase(i.begin() + index);
        }

        vertex_index.erase(vertex);
        vertex_name.erase(vertex->value);
    }

    /**
     * @brief new edge adding
     * 
     * @param from ref to "from" vertex
     * @param to ref to "to" vertex
     * @param weight value of edge
     * @return Edge<E, V>* ref to new edge
     */
    Edge<E, V> *addEdge(Vertex<V> *from, Vertex<V> *to, E weight)
    {
        auto new_edge = new Edge<E, V>(from, to, weight);

        int index1 = vertex_index[from];
        int index2 = vertex_index[to];

        matrix[index1][index2] = new_edge;

        return matrix[index1][index2];
    }

    /**
     * @brief edge removing
     * 
     * @param edge ref to edge
     */
    void removeEdge(Edge<E, V> *edge)
    {
        int index1 = vertex_index[edge->begin];
        int index2 = vertex_index[edge->end];

        matrix[index1][index2] = nullptr;
    }

    /**
     * @brief returns all vertices which starts from vertex
     * 
     * @param vertex ref to vertex
     * @return vector<Edge<E, V> *> vector of all edges
     */
    vector<Edge<E, V> *> edgesFrom(Vertex<V> *vertex)
    {
        vector<Edge<E, V> *> res;
        int index = vertex_index[vertex];

        for (auto vertex_pair : vertex_index)
        {
            if (matrix[index][vertex_pair.second] != nullptr)
            {
                res.push_back(matrix[index][vertex_pair.second]);
            }
        }

        // for (int i = 0; i < matrix.size(); i++)
        // {
        //     if (matrix[index][i] != nullptr)
        //         res.push_back(matrix[index][i]);
        // }

        return res;
    }

    /**
     * @brief returns all vertices which ends in vertex
     * 
     * @param vertex ref to vertex
     * @return vector<Edge<E, V> *> vector of all edges
     */
    vector<Edge<E, V> *> edgesTo(Vertex<V> *vertex)
    {
        vector<Edge<E, V> *> res;
        int index = vertex_index[vertex];

        for (int i = 0; i < matrix.size(); i++)
        {
            res.push_back(matrix[i][index]);
        }

        return res;
    }

    /**
     * @brief vertex finding
     * 
     * @param value name of vertex
     * @return Vertex<V>* ref to vertex
     */
    Vertex<V> *findVertex(V value)
    {
        for (auto i : vertex_index)
        {
            if (i.first->value == value)
            {
                return i.first;
            }
        }
        return 0;
    }

    /**
     * @brief edge finding
     * 
     * @param from_value name of start vertex
     * @param to_value name of end vertex
     * @return Edge<E, V>* ref to edge
     */
    Edge<E, V> *findEdge(V from_value, V to_value)
    {
        int index1 = vertex_index[vertex_name[from_value]];
        int index2 = vertex_index[vertex_name[to_value]];

        return matrix[index1][index2];
    }

    Edge<E, V> *findEdge(Vertex<V> *from, Vertex<V> *to)
    {

        int index1 = vertex_index[from];
        int index2 = vertex_index[to];

        return matrix[index1][index2];
    }

    /**
     * @brief check is there edge
     * 
     * @param v ref to first vertex
     * @param u ref to second vertex
     * @return true if yes
     * @return false if not
     */
    bool hasEdge(Vertex<V> *v, Vertex<V> *u)
    {
        int index1 = vertex_index[v];
        int index2 = vertex_index[u];

        return matrix[index1][index2] ? true : false;
    }

    /**
     * @brief prints matrix
     * 
     */
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
};

/**
 * @brief input parsing
 * 
 * @param line one line of input
 * @return vector<string> line splited in words
 */
vector<string> parse(string line)
{
    vector<string> res;
    string token = "";
    for (auto i : line)
    {

        if (i == ' ')
        {
            res.push_back(token);
            token = "";
        }
        else
        {
            token += i;
        }
    }
    res.push_back(token);

    return res;
}

int main(int argc, char const *argv[])
{
    auto matrix = AdjacencyMatrixGraph<int, string>();

    string line = " ";

    // parsing
    while (!line.empty())
    {
        getline(cin, line);
        auto instructions = parse(line);
        if (instructions[0] == "ADD_VERTEX")
        {
            string name = instructions[1];
            matrix.addVertex(name);
        }
        else if (instructions[0] == "REMOVE_VERTEX")
        {
            string name = instructions[1];
            auto ref = matrix.vertex_name.at(name);
            matrix.removeVertex(ref);
        }
        else if (instructions[0] == "ADD_EDGE")
        {
            string from = instructions[1];
            string to = instructions[2];
            int weight = stoi(instructions[3]);

            auto ref1 = matrix.vertex_name.at(from);
            auto ref2 = matrix.vertex_name.at(to);
            matrix.addEdge(ref1, ref2, weight);
        }
        else if (instructions[0] == "REMOVE_EDGE")
        {
            string from = instructions[1];
            string to = instructions[2];

            matrix.removeEdge(matrix.findEdge(from, to));
        }
        else if (instructions[0] == "HAS_EDGE")
        {
            string from = instructions[1];
            string to = instructions[2];

            auto ref1 = matrix.vertex_name.at(from);
            auto ref2 = matrix.vertex_name.at(to);

            if (matrix.hasEdge(ref1, ref2))
            {
                cout << "TRUE" << endl;
            }
            else
            {
                cout << "FALSE" << endl;
            }
        }
    }
    return 0;
}
