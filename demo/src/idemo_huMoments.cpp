#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <kernels.h>
#include <detail/types.h>
#include <detail/momentsStruct.h>

#include "idemo.hpp"

class demo_huMoments : public idemo
{
public:
    demo_huMoments() : idemo("hu moments")
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
        cv::Moments opencv_moments = cv::moments(src_, false);
        cv::HuMoments(opencv_moments, opencv_huMoments);
        std::cout << std::endl << "=====OpenCV realization=====" << std::endl << std::endl;
        for (int i = 0; i < opencv_huMoments.size(); ++i)
            std::cout << "h[" << i << "] = " << opencv_huMoments[i] << "\n";
        std::cout << "\n";
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

        openvx_huMoments.resize(arraySize);

        _vx_array huMoments_openvx = {
            &(openvx_huMoments[0]),
            arraySize,
            VX_TYPE_FLOAT32
        };

        findMoments(&input, &openvx_moments);
        findHuMoments(&openvx_moments, &huMoments_openvx);

        std::cout << "=====OpenVX realization=====\n\n";
        for (int i = 0; i < openvx_huMoments.size(); ++i)
            std::cout << "h[" << i << "] = " << openvx_huMoments[i] << "\n";
        std::cout << "\n";
    }

    void make_diff() override
    {
        std::cout << "Difference between openCV and openVX" << "\n";
        for (int i = 0; i < openvx_huMoments.size(); ++i)
            std::cout << "h[" << i << "] :  " << openvx_huMoments[i] - opencv_huMoments[i] << "\n";
    }

private:

    cv::Mat src_;
    uint32_t arraySize = 7;
    std::vector<double> opencv_huMoments;
    _momentsStruct openvx_moments;
    std::vector<double> openvx_huMoments;
};

static demo_huMoments demo_huMoments_instance;
