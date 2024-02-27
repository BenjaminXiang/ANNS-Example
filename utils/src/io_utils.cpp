#include "utils/io_utils.h"

namespace utils {

void read_fvecs(
  const std::string& filename, 
  float*& data, 
  std::size_t& num,
  std::size_t& dim)
{
  std::cout << std::format("load data from {}", filename) << std::endl;
  std::ifstream in(filename, std::ios::binary);
  if(!in.is_open()) {
    std::cout<<"open file error"<<std::endl;
    exit(-1);
  }
  unsigned t_dim;
  in.read((char*)&t_dim, 4);
  dim = t_dim;
  in.seekg(0,std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  num = (unsigned)(fsize / (dim+1) / 4);
  std::cout << std::format("data dimension: {}, data number: {}", dim, num) << std::endl;

  data = new float[num * dim * sizeof(float)];

  in.seekg(0, std::ios::beg);
  for(size_t i = 0; i < num; i++){
    in.seekg(4, std::ios::cur);
    in.read((char*)(data+i*dim), dim*4);
  }
  in.close();
}

} // utils