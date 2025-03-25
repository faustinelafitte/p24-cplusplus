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
        g[from].push_back(std::make_pair(to, weight));
    }

    void printGraph()
    {
        for (const auto &[vertex, neighbors] : g)
        {
            std::cout << vertex << "->";
            for (const auto &[neighbor, weight] : neighbors)
            {
                std::cout << "(" << neighbor << "," << weight << ") ";
            }
            std::cout << std::endl;
        }
    }

    void dfs_rec_helper(const std::string &start, std::unordered_map<std::string, bool> &visited)
    {
        visited[start] = true;
        for (const auto &[neighbor, weight] : g[start])
        {
            if (!visited[neighbor])
            {
                std::cout << "Edge: " << start << "->" << neighbor << " (Weight: " << weight << ")" << std::endl;
                dfs_rec_helper(neighbor, visited);
            }
        }
    }

    void dfs_rec(const std::string &start)
    {
        std::unordered_map<std::string, bool> visited;
        for (const auto &[vertex, _] : g)
        {
            visited[vertex] = false;
        }
        dfs_rec_helper(start, visited);
    }

    void dfs_it(const std::string &start)
    {
        std::unordered_map<std::string, bool> visited;
        std::stack<std::string> stack;
        stack.push(start);

        while (!stack.empty())
        {
            std::string position = stack.top();
            stack.pop();

            if (!visited[position])
            {
                visited[position] = true;
                for (const auto &[neighbor, weight] : g[position])
                {
                    if (!visited[neighbor])
                    {
                        std::cout << "Edge: " << position << "->" << neighbor << " (Weight: " << weight << ")" << std::endl;
                        stack.push(neighbor);
                    }
                }
            }
        }
    }

    void bfs(const std::string &start)
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
                for (const auto &[neighbor, weight] : g[position])
                {
                    if (!visited[neighbor])
                    {
                        std::cout << "Edge: " << position << "->" << neighbor << " (Weight: " << weight << ")" << std::endl;
                        queue.push(neighbor);
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<double>> Floyd_Warshall() const
    {
        std::unordered_map<std::string, int> g_index;
        int index = 0;
        for (const auto &[vertex, neighbors] : g)
        {
            if (g_index.find(vertex) == g_index.end())
            {
                g_index[vertex] = index++;
            }
            for (const auto &[neighbor, _] : neighbors)
            {
                if (g_index.find(neighbor) == g_index.end())
                {
                    g_index[neighbor] = index++;
                }
            }
        }

        int n = g_index.size();
        std::vector<std::vector<double>> W(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));

        for (int i = 0; i < n; i++)
        {
            W[i][i] = 0;
        }

        for (const auto &[vertex, neighbors] : g)
        {
            int from = g_index[vertex];
            for (const auto &[neighbor, weight] : neighbors)
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
                    if (W[i][k] != std::numeric_limits<double>::infinity() && W[k][j] != std::numeric_limits<double>::infinity())
                    {
                        W[i][j] = std::min(W[i][j], W[i][k] + W[k][j]);
                    }
                }
            }
        }
        return W;
    }
};

int main()
{
    Graph g;
    g.addEdge("Paris", "Lyon", 100);
    g.addEdge("Paris", "Marseille", 150);
    g.addEdge("Lyon", "Nice", 80);
    g.addEdge("Marseille", "Nice", 70);
    g.addEdge("Nice", "Paris", 200);

    std::cout << "Graph representation:\n";
    g.printGraph();

    std::cout << "\nDFS (Recursive) starting from Paris:\n";
    g.dfs_rec("Paris");

    std::cout << "\nBFS starting from Paris:\n";
    g.bfs("Paris");

    std::cout << "\nFloyd-Warshall Algorithm:\n";
    auto distances = g.Floyd_Warshall();

    std::cout << "Shortest distances matrix:\n";
    for (const auto &row : distances)
    {
        for (double val : row)
        {
            if (val == std::numeric_limits<double>::infinity())
                std::cout << "INF ";
            else
                std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
