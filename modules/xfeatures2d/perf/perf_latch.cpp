#include "perf_precomp.hpp"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
using namespace perf;
using std::tr1::make_tuple;
using std::tr1::get;

typedef perf::TestBaseWithParam<std::string> latch;

#define LATCH_IMAGES \
    "cv/detectors_descriptors_evaluation/images_datasets/leuven/img1.png",\
    "stitching/a3.png"

PERF_TEST_P(latch, extract, testing::Values(LATCH_IMAGES))
{
    string filename = getDataPath(GetParam());
    Mat frame = imread(filename, IMREAD_GRAYSCALE);
    ASSERT_FALSE(frame.empty()) << "Unable to load source image " << filename;

    Mat mask;
    declare.in(frame).time(90);

    Ptr<SURF> detector = SURF::create();
    vector<KeyPoint> points;
    detector->detect(frame, points, mask);

    Ptr<LATCH> descriptor = LATCH::create();
    vector<uchar> descriptors;
    TEST_CYCLE() descriptor->compute(frame, points, descriptors);

    SANITY_CHECK(descriptors, 1e-4);
}
