#pragma once
#include <queue>

#include "i_command.hpp"

class dijkstra_cmd : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            const auto& source_id = args.front();
            const size_t INF = std::numeric_limits<size_t>::max();
            std::unordered_map<std::string, size_t> dist;
            std::unordered_map<std::string, bool> visited
            ;
            auto vertices = graph.get_vertices();
            for (const auto& [id, vertex] : vertices) {
                dist[id] = INF;
                visited[id] = false;
            }
            dist[source_id] = 0;

            using pair = std::pair<size_t, std::string>;
            std::priority_queue<pair, std::vector<pair>, std::greater<>> pq;
            pq.emplace(0, source_id);

            while (!pq.empty()) {
                auto [current_dist, current_id] = pq.top();
                pq.pop();

                if (visited[current_id])
                    continue;
                visited[current_id] = true;

                const auto& vertex = vertices[current_id];
                const auto& outgoing_edges = vertex.get_outgoing_edges();

                for (const auto& [neighbor_id, edge] : outgoing_edges) {
                    if (visited[neighbor_id])
                        continue;
                    size_t weight = edge.get_weight();
                    size_t new_dist = current_dist + weight;
                    if (new_dist < dist[neighbor_id]) {
                        dist[neighbor_id] = new_dist;
                        pq.emplace(new_dist, neighbor_id);
                    }
                }
            }
            std::multimap<size_t, std::string> sorted_order;
            for (const auto& [id, distance] : dist) {
                if (distance != INF && distance > 0)
                    sorted_order.emplace(distance, id);
            }
            std::string result_answer;
            for (const auto& [distance, id] : sorted_order) {
                result_answer += id + " " + std::to_string(distance) + "\n";
            }
            if (!result_answer.empty())
                result_answer.pop_back();
            return result_answer;
        }


        bool validate_args(const std::vector<std::string> &args) override {
            if (args.size() != 1 || std::isdigit(args[0].front())) {
                return false;
            }
            return true;
        }
};
