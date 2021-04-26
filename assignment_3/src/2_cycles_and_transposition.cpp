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
#include <stack>
#include <algorithm>

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

    // vector for dfs
    vector<bool> used;

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

        // decreasing the index by 1 if the vertex has an index greater than the current
        for (auto &i : vertex_index)
        {
            if (i.second > index)
            {
                i.second -= 1;
            }
        }

        // removing from matrix row and column of current vertex
        matrix.erase(matrix.begin() + index);
        for (auto &i : matrix)
        {
            i.erase(i.begin() + index);
        }

        // removing from maps
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

    /**
     * @brief edge finding
     * 
     * @param from start vertex
     * @param to end vertex
     * @return Edge<E, V>* ref to edge 
     */
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

    /**
     * @brief acyclic graph or not checking 
     * 
     */
    vector<Vertex<V> *> isAcyclic()
    {
        // map with visited indexes
        auto visited = new map<Vertex<V> *, bool>();

        for (auto vertex_pair : vertex_index)
        {
            auto current_vertex = vertex_pair.first;
            auto answer = dfs(visited, current_vertex, {});

            if (answer.size() != 0)
            {
                return answer;
            }
        }

        return {};
    }

    /**
     * @brief make transposed adjacency matrix 
     * 
     */
    void transpose()
    {
        vector<Edge<E, V> *> edges_to_transpose;

        // swapping in adjacency matrix
        for (auto vertex_pair1 : vertex_index)
        {
            for (auto vertex_pair2 : vertex_index)
            {
                int i = vertex_pair1.second;
                int j = vertex_pair2.second;
                if (matrix[i][j] != nullptr)
                {
                    edges_to_transpose.push_back(matrix[i][j]);
                    matrix[i][j] = nullptr;
                }
            }
        }

        // swapping begin and end in edge
        for (auto edge : edges_to_transpose)
        {
            auto i = vertex_index[edge->begin];
            auto j = vertex_index[edge->end];

            auto temp = edge->begin;
            edge->begin = edge->end;
            edge->end = temp;

            matrix[j][i] = edge;
        }
    }

private:
    /**
     * @brief 
     * 
     * @param visited bool map with visited vertices
     * @param current current vertex
     * @param path path of cycle 
     * @return vector<Vertex<V> *> our path
     */
    vector<Vertex<V> *> dfs(map<Vertex<V> *, bool> *visited,
                            Vertex<V> *current, vector<Vertex<V> *> path)
    {

        // if already visited
        if (visited->find(current) != visited->end())
            return {};

        // mark it visited
        visited->insert({current, true});

        // check all edges which connected with current
        for (auto edge : edgesFrom(current))
        {
            auto next_vertex = edge->end;

            if (find(path.begin(), path.end(), next_vertex) != path.end())
            {
                // cycle searching
                vector<Vertex<V> *> cycle;
                path.push_back(current);

                while (path.back() != next_vertex)
                {
                    cycle.push_back(path.back());
                    path.pop_back();
                }
                cycle.push_back(next_vertex);

                reverse(cycle.begin(), cycle.end());

                return cycle;
            }

            if (visited->find(next_vertex) == visited->end())
            {
                auto tmp_path = path;
                tmp_path.push_back(current);

                auto result = dfs(visited, next_vertex, tmp_path);

                if (result.size() != 0)
                    return result;
            }
        }

        return {};
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
            auto ref = matrix.vertex_name[name];
            matrix.removeVertex(ref);
        }
        else if (instructions[0] == "ADD_EDGE")
        {
            string from = instructions[1];
            string to = instructions[2];
            int weight = stoi(instructions[3]);

            auto ref1 = matrix.vertex_name[from];
            auto ref2 = matrix.vertex_name[to];
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

            auto ref1 = matrix.vertex_name[from];
            auto ref2 = matrix.vertex_name[to];

            if (matrix.hasEdge(ref1, ref2))
            {
                cout << "TRUE" << endl;
            }
            else
            {
                cout << "FALSE" << endl;
            }
        }
        else if (instructions[0] == "TRANSPOSE")
        {
            matrix.transpose();
        }
        else if (instructions[0] == "IS_ACYCLIC")
        {

            auto result = matrix.isAcyclic();

            if (result.size() == 0)
            {
                cout
                    << "ACYCLIC" << endl;
            }
            else
            {
                int weight = 0;
                string answer = "";
                for (int i = 0; i < result.size() - 1; i++)
                {
                    auto v1 = result[i];
                    auto v2 = result[i + 1];
                    weight += matrix.findEdge(v1, v2)->weight;

                    answer = answer + " " + v1->value;
                }
                weight +=
                    matrix.findEdge(result[result.size() - 1], result[0])->weight;
                answer = answer + " " + result[result.size() - 1]->value;
                answer = to_string(weight) + answer;
                cout << answer << endl;
            }
        }
    }

    return 0;
}
