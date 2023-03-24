#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "color.hpp"
#include "path_image.hpp"
#include "path.hpp"

int main() {
    // these functions were used to test runtime errors during creation of the program
    ElevationDataset test = ElevationDataset("./example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);
    GrayscaleImage gray_pic = GrayscaleImage(test);
    PathImage image = PathImage(gray_pic, test);
}
