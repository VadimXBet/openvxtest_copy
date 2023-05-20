#include <filesystem>
#include <stdexcept>
#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <kernels.h>
#include <detail/types.h>
#include <detail/momentsStruct.h>

#include "idemo.hpp"

class demo_moments : public idemo
{
public:
    demo_moments() : idemo("moments")
    {
    }

    void prepare(const std::filesystem::path& resource_dir) override
    {
        auto path = resource_dir / std::filesystem::path("Solvay_conference_1927.png");
        if (!std::filesystem::exists(path))
            throw std::invalid_argument("Cannot find file " + path.string());

        src_ = cv::imread(path.string(), cv::IMREAD_GRAYSCALE);
    }

    void execute_opencv() override
    {
        opencv_moments = cv::moments(src_, false);
        std::cout << std::endl << "=====OpenCV realization=====" << "\n\n";
        std::cout << "space moments:" << "\n";
        std::cout << "m00 = " << opencv_moments.m00 << "\n";
        std::cout << "m01 = " << opencv_moments.m01 << "\n";
        std::cout << "m10 = " << opencv_moments.m10 << "\n";
        std::cout << "m11 = " << opencv_moments.m11 << "\n";
        std::cout << "m02 = " << opencv_moments.m02 << "\n";
        std::cout << "m20 = " << opencv_moments.m20 << "\n";
        std::cout << "m30 = " << opencv_moments.m30 << "\n";
        std::cout << "m03 = " << opencv_moments.m03 << "\n";
        std::cout << "m12 = " << opencv_moments.m12 << "\n";
        std::cout << "m21 = " << opencv_moments.m21 << "\n\n";

        std::cout << "central moments:" << "\n";
        std::cout << "mu11 = " << opencv_moments.mu11 << "\n";
        std::cout << "mu02 = " << opencv_moments.mu02 << "\n";
        std::cout << "mu20 = " << opencv_moments.mu20 << "\n";
        std::cout << "mu30 = " << opencv_moments.mu30 << "\n";
        std::cout << "mu03 = " << opencv_moments.mu03 << "\n";
        std::cout << "mu12 = " << opencv_moments.mu12 << "\n";
        std::cout << "mu21 = " << opencv_moments.mu21 << "\n\n";


        std::cout << "normalized central moments:" << "\n";
        std::cout << "nu11 = " << opencv_moments.nu11 << "\n";
        std::cout << "nu02 = " << opencv_moments.nu02 << "\n";
        std::cout << "nu20 = " << opencv_moments.nu20 << "\n";
        std::cout << "nu30 = " << opencv_moments.nu30 << "\n";
        std::cout << "nu03 = " << opencv_moments.nu03 << "\n";
        std::cout << "nu12 = " << opencv_moments.nu12 << "\n";
        std::cout << "nu21 = " << opencv_moments.nu21 << "\n\n";
    }

    void execute_openvx() override
    {
        _vx_image input = {
            src_.data,
            uint32_t(src_.cols),
            uint32_t(src_.rows),
            VX_DF_IMAGE_U8,
            VX_COLOR_SPACE_DEFAULT
        };

        findMoments(&input, &openvx_moments);

        std::cout << "\n" << "=====OpenVX realization=====" << "\n\n";
        std::cout << "space moments:" << "\n";
        std::cout << "m00 = " << openvx_moments.m00 << "\n";
        std::cout << "m01 = " << openvx_moments.m01 << "\n";
        std::cout << "m10 = " << openvx_moments.m10 << "\n";
        std::cout << "m11 = " << openvx_moments.m11 << "\n";
        std::cout << "m02 = " << openvx_moments.m02 << "\n";
        std::cout << "m20 = " << openvx_moments.m20 << "\n";
        std::cout << "m30 = " << openvx_moments.m30 << "\n";
        std::cout << "m03 = " << openvx_moments.m03 << "\n";
        std::cout << "m12 = " << openvx_moments.m12 << "\n";
        std::cout << "m21 = " << openvx_moments.m21 << "\n\n";

        std::cout << "central moments:" << "\n";
        std::cout << "mu11 = " << openvx_moments.mu11 << "\n";
        std::cout << "mu02 = " << openvx_moments.mu02 << "\n";
        std::cout << "mu20 = " << openvx_moments.mu20 << "\n";
        std::cout << "mu30 = " << openvx_moments.mu30 << "\n";
        std::cout << "mu03 = " << openvx_moments.mu03 << "\n";
        std::cout << "mu12 = " << openvx_moments.mu12 << "\n";
        std::cout << "mu21 = " << openvx_moments.mu21 << "\n\n";


        std::cout << "normalized central moments:" << "\n";
        std::cout << "nu11 = " << openvx_moments.nu11 << "\n";
        std::cout << "nu02 = " << openvx_moments.nu02 << "\n";
        std::cout << "nu20 = " << openvx_moments.nu20 << "\n";
        std::cout << "nu30 = " << openvx_moments.nu30 << "\n";
        std::cout << "nu03 = " << openvx_moments.nu03 << "\n";
        std::cout << "nu12 = " << openvx_moments.nu12 << "\n";
        std::cout << "nu21 = " << openvx_moments.nu21 << "\n\n";
    }

    void make_diff() override
    {
        std::cout << "Difference between openCV and openVX" << "\n";

        std::cout << "m00: " << opencv_moments.m00 - openvx_moments.m00 << "\n";
        std::cout << "m01: " << opencv_moments.m01 - openvx_moments.m01 << "\n";
        std::cout << "m10: " << opencv_moments.m10 - openvx_moments.m10 << "\n";
        std::cout << "m11: " << opencv_moments.m11 - openvx_moments.m11 << "\n";
        std::cout << "m20: " << opencv_moments.m20 - openvx_moments.m20 << "\n";
        std::cout << "m02: " << opencv_moments.m02 - openvx_moments.m02 << "\n";
        std::cout << "m30: " << opencv_moments.m30 - openvx_moments.m30 << "\n";
        std::cout << "m03: " << opencv_moments.m03 - openvx_moments.m03 << "\n";
        std::cout << "m12: " << opencv_moments.m12 - openvx_moments.m12 << "\n";
        std::cout << "m21: " << opencv_moments.m21 - openvx_moments.m21 << "\n";

        std::cout << "mu20: " << opencv_moments.mu20 - openvx_moments.mu20 << "\n";
        std::cout << "mu02: " << opencv_moments.mu02 - openvx_moments.mu02 << "\n";
        std::cout << "mu11: " << opencv_moments.mu11 - openvx_moments.mu11 << "\n";
        std::cout << "mu30: " << opencv_moments.mu30 - openvx_moments.mu30 << "\n";
        std::cout << "mu03: " << opencv_moments.mu03 - openvx_moments.mu03 << "\n";
        std::cout << "mu21: " << opencv_moments.mu21 - openvx_moments.mu21 << "\n";
        std::cout << "mu12: " << opencv_moments.mu12 - openvx_moments.mu12 << "\n";

        std::cout << "nu20: " << opencv_moments.nu20 - openvx_moments.nu20 << "\n";
        std::cout << "nu02: " << opencv_moments.nu02 - openvx_moments.nu02 << "\n";
        std::cout << "nu11: " << opencv_moments.nu11 - openvx_moments.nu11 << "\n";
        std::cout << "nu30: " << opencv_moments.nu30 - openvx_moments.nu30 << "\n";
        std::cout << "nu03: " << opencv_moments.nu03 - openvx_moments.nu03 << "\n";
        std::cout << "nu12: " << opencv_moments.nu12 - openvx_moments.nu12 << "\n";
        std::cout << "nu21: " << opencv_moments.nu21 - openvx_moments.nu21 << "\n";
    }

private:

    cv::Mat src_;
    cv::Moments opencv_moments;
    _momentsStruct openvx_moments;
};

static demo_moments demo_moments_instance;
