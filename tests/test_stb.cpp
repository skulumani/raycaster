#include "gtest/gtest.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

TEST(TestSTB, JPGWrite) {
    int width = 512;
    int height = 512;

    std::uint8_t image[width * height * 3];
    for (size_t ii = 0; ii < width * height; ii++) {
        image[ii * 3 + 0] = (int)(255 * 1);
        image[ii * 3 + 1] = (int)(255 * 0);
        image[ii * 3 + 2] = (int)(255 * 0);
    }

    int success = stbi_write_jpg("out.jpg",width, height, 3, image, 95);

    ASSERT_EQ(success, 1);
}
