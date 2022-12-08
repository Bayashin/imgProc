#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./a_img.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    cv::Mat bin_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    //画像の二値化
    cv::threshold(src_img, bin_img, 100, 255, cv::THRESH_BINARY_INV);
    
    
    //傍聴
    for (int i=0; i<10; i++) {
        //傍聴
        cv::dilate(bin_img, dst_img, cv::Mat(), cv::Point(-1,-1),i);
        cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//表示
        cv::waitKey();//キー入力待ち
    }
    
    //収縮
    for (int i=0; i<10; i++) {
        //収縮
        cv::erode(dst_img, bin_img, cv::Mat(), cv::Point(-1,-1),i);
        cv::imshow(WINDOW_NAME_OUTPUT, bin_img);//表示
        cv::waitKey();//キー入力待ち
    }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,bin_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
