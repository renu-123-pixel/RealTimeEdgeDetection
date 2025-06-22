#include <jni.h>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat intArrayToMat(jint* pixels, int width, int height) {
    Mat rgba(height, width, CV_8UC4, pixels);
    Mat bgr;
    cvtColor(rgba, bgr, COLOR_RGBA2BGR);
    return bgr;
}

extern "C"
JNIEXPORT jbyteArray JNICALL Java_com_examplefourthjuly_realtimeedgedetection_NativeProcessor_processFrame(
        JNIEnv* env, jobject, jintArray pixels_, jint width, jint height) {

    jint* pixels = env->GetIntArrayElements(pixels_, nullptr);
    Mat bgr = intArrayToMat(pixels, width, height);
    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    Mat gray;
    cvtColor(bgr, gray, COLOR_BGR2GRAY);

    Mat edges;
    Canny(gray, edges, 100, 200);

    dilate(edges, edges, Mat(), Point(-1, -1), 1);  // 1 = how thick to make edges


    jbyteArray result = env->NewByteArray(edges.total());
    env->SetByteArrayRegion(result, 0, edges.total(), reinterpret_cast<jbyte*>(edges.data));
    return result;
}
