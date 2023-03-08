#include "grayscale_image.hpp"
#include <cmath>
#include <fstream>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) : width_{dataset.Width()}, height_{dataset.Height()} {
    std::vector<std::vector<Color>> image;
    for (const std::vector<int>& row_data : dataset.GetData()) {
        std::vector<Color> row_image;
        for (double col_data : row_data) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                row_image.push_back(Color(0, 0, 0));
            } else {
                int shade_color = (int) std::round((col_data - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
                row_image.push_back(Color(shade_color, shade_color, shade_color));
            }
        }
        image.push_back(row_image);
    }
    image_ = image;
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) : width_{width}, height_{height} {
    ElevationDataset dataset = ElevationDataset(filename, width, height);

    std::vector<std::vector<Color>> image;
    for (const std::vector<int>& row_data : dataset.GetData()) {
        std::vector<Color> row_image;
        for (double col_data : row_data) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                row_image.push_back(Color(0, 0, 0));
            } else {
                int shade_color = (int) std::round((col_data - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
                row_image.push_back(Color(shade_color, shade_color, shade_color));
            }
        }
        image.push_back(row_image);
    }
    image_ = image;
}

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{std::string (name)}; 
    if (!ofs.is_open()) {
        throw std::runtime_error("Output file failed to open");
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;

    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            int current_color = image_.at(row).at(col).Red();
            ofs << current_color << " " << current_color << " " << current_color << " ";
        }
        ofs << std::endl;
    }
}