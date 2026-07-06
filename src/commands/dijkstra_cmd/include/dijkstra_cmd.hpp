#pragma once
#include <queue>
#include <algorithm>

#include "i_command.hpp"

class dijkstra_cmd final : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            const auto& source_id = args.front();
            const size_t INF = std::numeric_limits<size_t>::max();
            std::unordered_map<std::string, size_t> dist;           // хеш-мапа расстояний
            std::unordered_map<std::string, bool> visited;          // хещ-мапа посещенных вершин

            auto vertices = graph.get_vertices();
            for (const auto& [id, vertex] : vertices) {
                dist[id] = INF;
                visited[id] = false;
            } // на старте расстояние до всех вершин = INF, и все вершины считаются не посещенными
            dist[source_id] = 0; // расстояние до стартовой = 0

            using pair = std::pair<size_t, std::string>; // size_t - расстояние от старта до вершины, string - id этой вершины
            std::priority_queue<pair, std::vector<pair>, std::greater<>> pq;
            pq.emplace(0, source_id);

            while (!pq.empty()) {
                auto [current_dist, current_id] = pq.top();
                pq.pop();   // на топе всегда находится ребро с наименьшим весом

                if (visited[current_id]) { // если была посещена - пропускаем
                    continue;
                }
                visited[current_id] = true;

                const auto& vertex = vertices[current_id];
                const auto& outgoing_edges = vertex.get_outgoing_edges();

                for (const auto& [neighbor_id, edge] : outgoing_edges) { // проходимся по всем соседям
                    if (visited[neighbor_id]) {
                        continue;
                    }
                    size_t weight = edge.get_weight();
                    size_t new_dist = current_dist + weight; // новое расстояние до вершины
                    if (new_dist < dist[neighbor_id]) {
                        dist[neighbor_id] = new_dist;
                        pq.emplace(new_dist, neighbor_id);
                    }
                }
            }
            std::vector<std::pair<size_t, std::string>> results; // для сортировки вершин
            for (const auto& [id, distance] : dist) {
                if (distance != INF && distance > 0) {
                    results.emplace_back(distance, id);
                }
            }
            std::sort(results.begin(), results.end());
            std::string result_answer;
            for (const auto& [distance, id] : results) {
                result_answer += id + " " + std::to_string(distance) + "\n";
            }
            if (!result_answer.empty()) {
                result_answer.pop_back();
            }
            return result_answer;
        }


        bool validate_args(const std::vector<std::string> &args) override {
            bool broken_arguments = args.size() != 1 || std::isdigit(args[0].front());
            return !broken_arguments;
        }
};
