#include "path_image.hpp"
#include <limits>
#include <stdexcept>
#include <fstream>

PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset) : width_{dataset.Width()}, height_{dataset.Height()} {
    const Color kRed = Color(252, 25, 63);
    const Color kGreen = Color(31, 253, 13);
    path_image_ = image.GetImage();
    unsigned int min_ele_change = std::numeric_limits<unsigned int>::max();
    size_t idx_min_ele_change = -1;
    for (size_t row = 0; row < dataset.Height(); row++) {
        Path current = Path(dataset.Width(), row);
        current.SetLoc(0, row);
        path_image_.at(row).at(0) = kRed;
        size_t row_to_parse = row;
        for (size_t col = 1; col < dataset.Width(); col++) {
            unsigned int top_diff = std::numeric_limits<unsigned int>::max();
            if (row_to_parse != 0) { top_diff = abs(dataset.DatumAt(row_to_parse, col - 1) - dataset.DatumAt(row_to_parse - 1, col)); }
            unsigned int mid_diff = abs(dataset.DatumAt(row_to_parse, col - 1) - dataset.DatumAt(row_to_parse, col));
            unsigned int bot_diff = std::numeric_limits<unsigned int>::max();
            if (row_to_parse != dataset.Height() - 1) { bot_diff = abs(dataset.DatumAt(row_to_parse, col - 1) - dataset.DatumAt(row_to_parse + 1, col)); }
            unsigned int min = mid_diff;
            size_t min_idx = row_to_parse;
            if (min > bot_diff) { min = bot_diff; min_idx = row_to_parse + 1; }
            if (min > top_diff) {
                min = top_diff;
                min_idx = row_to_parse - 1;
            }
            current.SetLoc(col, min_idx);
            path_image_.at(min_idx).at(col) = kRed;
            current.IncEleChange(min);
            row_to_parse = min_idx;
            }
        if (current.EleChange() < min_ele_change) {
            min_ele_change = current.EleChange();
            idx_min_ele_change = current.StartingRow();
        }
        paths_.push_back(current);
    }
    for (size_t col = 0; col < dataset.Width(); col++) {
        size_t row = paths_.at(idx_min_ele_change).GetPath().at(col);
        path_image_.at(row).at(col) = kGreen;
    }  
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const { return path_image_; }

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{std::string (name)}; 
    if (!ofs.is_open()) {
        throw std::runtime_error("Output file failed to open");
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;

    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            Color current_color = path_image_.at(row).at(col);
            ofs << current_color.Red() << " " << current_color.Green() << " " << current_color.Blue() << " ";
        }
        ofs << std::endl;
    }
} 