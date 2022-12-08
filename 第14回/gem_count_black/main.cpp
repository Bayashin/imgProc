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

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,gray_img,dst_img,bin_img,tmp_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    cv::threshold(gray_img, bin_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);
    
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    tmp_img = bin_img.clone();
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    dst_img = src_img.clone();
    for (int i=0; i<contours.size(); i++) {
        float radius;
        cv::Point2f center;
        cv::minEnclosingCircle(contours[i], center, radius);
        cv::circle(dst_img, center, (int)radius, CV_RGB(255,0,0),2);
    }
    
    std::cout << "Black gem = " << contours.size() << std::endl;
    
    cv::imshow(WINDOW_NAME_INPUT, bin_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
