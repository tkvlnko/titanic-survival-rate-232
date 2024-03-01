#include "ortools/algorithms/knapsack_solver.h"
#include "titanic.h"

namespace operations_research {
void RunKnapsackExample(const stringMatrix& matrix) {
// Instantiate the solver.
  KnapsackSolver solver(
      KnapsackSolver::KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER,
      "KnapsackExample");

//int, size_t doesn't work
  std::vector<int64_t> values;
  std::vector<std::vector<int64_t>> weights;

  std::vector<int64_t> weightsVector;


for (size_t i = 1; i < matrix.size(); i++){
    weightsVector.push_back(std::stoi(matrix[i][CSV_FIELDS::Value]));
    weightsVector.push_back(std::stoi(matrix[i][CSV_FIELDS::Weight]));
}
  weights.push_back(weightsVector);

  std::vector<int64_t> capacities = {1000};



  solver.Init(values, weights, capacities);
  double computed_value = solver.Solve();

  // Print solution
  std::vector<int> packed_items;
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (solver.BestSolutionContains(i)) packed_items.push_back(i);
  }
  std::ostringstream packed_items_ss;
  std::copy(packed_items.begin(), packed_items.end() - 1,
            std::ostream_iterator<int>(packed_items_ss, ", "));
  packed_items_ss << packed_items.back();

  std::vector<int64_t> packed_weights;
  packed_weights.reserve(packed_items.size());
  for (const auto& it : packed_items) {
    packed_weights.push_back(weights[0][it]);
  }
  std::ostringstream packed_weights_ss;
  std::copy(packed_weights.begin(), packed_weights.end() - 1,
            std::ostream_iterator<int>(packed_weights_ss, ", "));
  packed_weights_ss << packed_weights.back();

  int64_t total_weights =
      std::accumulate(packed_weights.begin(), packed_weights.end(), int64_t{0});

  LOG(INFO) << "Total value: " << computed_value;
  LOG(INFO) << "Packed items: {" << packed_items_ss.str() << "}";
  LOG(INFO) << "Total weight: " << total_weights;
  LOG(INFO) << "Packed weights: {" << packed_weights_ss.str() << "}";
}
}
