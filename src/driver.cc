#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "color.hpp"
#include "path_image.hpp"
#include "path.hpp"

int main() {
    ElevationDataset test = ElevationDataset("./example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);

    GrayscaleImage gray_pic = GrayscaleImage(test);
    PathImage demolished = PathImage(gray_pic, test);
}