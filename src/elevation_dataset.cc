#include "elevation_dataset.hpp"
#include <fstream>
#include <limits>
#include <string>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) : width_{width}, height_{height} {
    std::ifstream ifs{filename};
    if(!(ifs.is_open())) {
        throw std::invalid_argument("File not found: " + filename);
    }
    std::vector<std::vector<int>> data(height_);
    int max = std::numeric_limits<int>::min();
    int min = std::numeric_limits<int>::max();
    int value = 0;
    for (size_t row = 0; row < height_; row++) {
        std::vector<int> one_row;
        for (size_t col = 0; col < width_; col++) {
            ifs >> value;
            if (ifs.fail()) {
                throw std::runtime_error("Not enough data OR format error");
            }
            one_row.push_back(value);
            if (value > max) { max = value; }
            if (value < min) { min = value; }
        }
        data.at(row) = one_row;
    }
    if (ifs >> value) {
        throw std::runtime_error("Too Much Data");
    }
    if (data.at(0).size() != width_) {
        throw std::runtime_error("Incorrect data dimentions: Width");
    }
    if (data.size() != height_) {
        throw std::runtime_error("Incorrect data dimentions: Height");
    }
    data_ = data;
    max_ele_ = max;
    min_ele_ = min;
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
    return data_;
}