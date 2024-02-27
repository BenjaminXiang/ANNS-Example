#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <format>

#include <cassert>
#include <cmath>
#include <unistd.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

namespace utils {
void read_fvecs(
    const std::string& filename, 
    float*& data, 
    std::size_t& num,
    std::size_t& dim);

} // namespace utils