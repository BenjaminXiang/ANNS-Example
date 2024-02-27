add_executable(search_hnsw search_hnsw.cpp)
target_link_libraries(search_hnsw hnswlib utils)

add_executable(omp_test omp_test.cpp)
target_link_libraries(omp_test OpenMP::OpenMP_CXX)