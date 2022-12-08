#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./gem1.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define TH (20)
#define MAX_VAL (255)
#define COUNT (15)
#define R_MIN (0)
#define R_MAX (50)
#define G_MIN (50)
#define G_MAX (100)
#define HUE_MIN (20.0)
#define HUE_MAX (60.0)
#define SAT_MIN (100.0)
#define SAT_MAX (200.0)

cv::Mat CloseOpen(cv::Mat bin_img){
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    return bin_img;
}

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,dst_img;//画像の型と変数
    cv::Mat gray_img,hsv_img,tmp_img;
    cv::Mat bin_black_img,bin_green_img,bin_gold_img;
    cv::Vec3b p;
    
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    dst_img = src_img.clone();
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    
    //黒曜石━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    cv::threshold(gray_img, bin_black_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);
    
    tmp_img = CloseOpen(bin_black_img).clone();
    
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    for (int i=0; i<contours.size(); i++) {
        float radius;
        cv::Rect center = cv::boundingRect(contours[i]);
        cv::rectangle(dst_img, center, CV_RGB(255,0,0),2);
    }
    
    std::cout << "Black gem = " << contours.size() << std::endl;
    
    //トルコ石━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    bin_green_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            p = src_img.at<cv::Vec3b>(y, x);
            if (p[1] >= G_MIN && p[1] <= G_MAX && p[2] >= R_MIN && p[2] <=R_MAX) {
                bin_green_img.at<uchar>(y,x) = MAX_VAL;
            }
        }
    }
    
    tmp_img = CloseOpen(bin_green_img).clone();
    
    contours.clear();
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    for (int i=0; i<contours.size(); i++) {
        cv::drawContours(dst_img, contours, i, CV_RGB(0, 255, 0), -1);
    }

    std::cout << "Green gem = " << contours.size() << std::endl;
    
    //黄金━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    bin_gold_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    
    for (int y=0; y<src_img.rows; y++) {
           for (int x=0; x<src_img.cols; x++) {
               p = hsv_img.at<cv::Vec3b>(y,x);
               if (p[0] >= HUE_MIN && p[0] <= HUE_MAX && p[1] >= SAT_MIN && p[1] <= SAT_MAX) {
                   bin_gold_img.at<uchar>(y,x) =MAX_VAL;
               }
           }
       }
    
    tmp_img = CloseOpen(bin_gold_img).clone();
    
    contours.clear();
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    for (int i=0; i<contours.size(); i++) {
            float radius;
            cv::Point2f center;
            cv::minEnclosingCircle(contours[i], center, radius);
            cv::circle(dst_img, center, (int)radius, CV_RGB(255,255,255),2);
        }
    
    std::cout << "Golden gem = " << contours.size() << std::endl;
    
    //表示━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
