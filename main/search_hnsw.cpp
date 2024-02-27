#include "hnswlib/hnswlib.h"
#include "utils/io_utils.h"
#include "utils/timer.h"
#include <cstddef>
#include <format>
#include <chrono>
#include <queue>

int main(int argc, char** argv) {
  const std::string kDataPath  = argv[1];
  const std::string kQueryPath = argv[2];
  const std::string kSpaceType = argv[3];

  const unsigned kM = atoi(argv[4]);
  const unsigned kEfConstruction = atoi(argv[5]);
  const unsigned kEfSearch = atoi(argv[6]);
  const unsigned kTopK = atoi(argv[7]);

  float* data;
  std::size_t data_num, data_dim;
  utils::read_fvecs(kDataPath, data, data_num, data_dim);
  float* query;
  std::size_t query_num, query_dim; 
  utils::read_fvecs(kQueryPath, query, query_num, query_dim);

  hnswlib::SpaceInterface<float>* space;
  if (kSpaceType == "l2") {
    space = new hnswlib::L2Space(data_dim);
  } else if (kSpaceType == "ip") {
    space = new hnswlib::InnerProductSpace(data_dim);
  } else {
    std::cerr << "Invalid space type: " << kSpaceType << std::endl;
    return -1;
  }

  hnswlib::HierarchicalNSW<float> hnsw(space, data_num, kM, kEfConstruction);

// Build Index
  hnsw.addPoint(data, 0);
#pragma omp parallel for
  for (std::size_t i = 1; i < data_num; ++i) {
    hnsw.addPoint(data + i * data_dim, i);
  }

// Search
  std::vector<std::priority_queue<std::pair<float, hnswlib::labeltype>>> hnsw_res(query_num);
  hnsw.setEf(kEfSearch);
  for (std::size_t i=0; i<query_num; ++i) {
    hnsw_res[i] = hnsw.searchKnn(query + i * query_dim, kTopK);
  }

  return 0;
}