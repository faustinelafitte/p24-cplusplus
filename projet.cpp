#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <limits>
#include <string>

class Graph
{
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> g;

public:
    void addEdge(std::string from, std::string to, double weight)
    {
        g[from].push_back(make_pair(to, weight));
    }

    void printGraph()
    {
        for (auto [vertex, neighbors] : g)
        {
            std::cout << vertex << "->";
            for (auto [neighbor, weight] : neighbors)
            {
                std::cout << "(" << neighbor << "," << weight << ")";
            }
            std::cout << std::endl;
        }
    }

    auto end()
    {
        return g.end();
    }

    auto begin()
    {
        return g.begin();
    }

    void dfs_rec(std::string start)
    {
        std::unordered_map<std::string, int> visited;
        for (auto &[vertex, weight] : g)
        {
            visited[vertex] = 0; // Initialiser tous les noeuds comme non visités
        }
        visited[start] = 1;
        for (auto [neighbor, weight] : g[start])
        {
            if (visited[neighbor] == 0)
            {
                std::cout << "Edge:" << start << "->" << neighbor << "(Weight:" << weight << ")" << std::endl;
                dfs_rec(neighbor);
            }
        }
    }

    void dfs_it(std::string start)
    {
        std::unordered_map<std::string, int> visited;
        std::stack<std::string> stack;
        stack.push(start);

        while (!stack.empty())
        {
            std::string position = stack.top();
            stack.pop();

            if (visited[position] == 0)
            {
                visited[position] = 1;

                for (auto [neighbor, weight] : g[position])
                {
                    if (visited[neighbor] == 0)
                    {
                        std::cout << "Edge:" << position << "->" << neighbor << "(Weight:" << weight << ")" << std::endl;
                        stack.push(neighbor);
                    }
                }
            }
        }
    }

    void bfs(std::string start)
    {
        std::unordered_map<std::string, bool> visited;
        std::queue<std::string> queue;
        queue.push(start);

        while (!queue.empty())
        {
            std::string position = queue.front();
            queue.pop();

            if (!visited[position])
            {
                visited[position] = true;

                for (auto [neighbor, weight] : g[position])
                {
                    if (!visited[neighbor])
                    {
                        std::cout << "Edge:" << position << "->" << neighbor << "(Weight:" << weight << ")" << std::endl;
                        queue.push(neighbor);
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> Flody_Warshall(Graph g)
    {
        // Étape 1 : Associer chaque sommet à un index entier
        std::unordered_map<std::string, int> g_index;
        int index = 0;
        for (auto &[vertex, neighbors] : g)
        {
            if (g_index.find(vertex) == g_index.end())
            {
                g_index[vertex] = index++;
            }
            for (auto [neighbor, weight] : neighbors)
            {
                if (g_index.find(neighbor) == g_index.end())
                {
                    g_index[neighbor] = index++;
                }
            }
        }

        int n = g_index.size();

        // Étape 2 : Initialiser la matrice avec des valeurs par défaut
        std::vector<std::vector<int>> W(n, std::vector<int>(n, std::numeric_limits<double>::infinity()));
        for (int i = 0; i < n; i++)
        {
            W[i][i] = 0; // Distance à soi-même est 0
        }

        // Étape 3 : Remplir la matrice avec les poids des arêtes
        for (auto &[vertex, neighbors] : g)
        {
            int from = g_index[vertex];
            for (auto &[neighbor, weight] : neighbors)
            {
                int to = g_index[neighbor];
                W[from][to] = weight;
            }
        }

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    W[i][j] = std::min(W[i][j], W[i][k] + W[k][j]);
                }
            }
        }
        return W;
    }
};

int main()
{
    Graph g;
    // plutôt dictionnaire
    g.addEdge("Paris", "Lyon", 100);
    g.addEdge("Paris", "Marseille", 150);
    g.addEdge("Lyon", "Nice", 80);
    g.addEdge("Marseille", "Nice", 70);
    g.addEdge("Nice", "Paris", 200);
    g.printGraph();
    g.dfs_rec("Paris");
    g.bfs("Paris");
    return 0;
}