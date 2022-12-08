#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./labeling.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,gray_img,bin_img,tmp_img,dst_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    std::vector<std::vector<cv::Point>> contours;
    
    cv::Scalar color[] = {
        CV_RGB(0, 0, 0),
        CV_RGB(0, 255, 0),
        CV_RGB(0, 0, 255),
        CV_RGB(255, 0, 255),
    };
    
    dst_img = src_img.clone();
    
    cv::cvtColor(src_img, gray_img, cv::COLOR_RGB2GRAY);
    
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);
    
    tmp_img = bin_img.clone();
    
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    for (int i=0; i<contours.size(); i++) {
        cv::drawContours(dst_img, contours, i, color[i%4], cv::FILLED);
    }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT,dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
