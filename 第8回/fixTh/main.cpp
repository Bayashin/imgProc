#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./red_rectangle.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define TH (100)
#define HIGHVAL (255)
#define LOWVAL (0)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat gray_img;//画像の型と変数
    gray_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (gray_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    //二値画像のメモリ確保
    cv::Mat bin_img;
    bin_img = cv::Mat(gray_img.size(), CV_8UC1);
    
    //二値画像に変換
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            if (gray_img.at<uchar>(y,x) < TH) {
                bin_img.at<uchar>(y,x) = HIGHVAL;
            }else{
                bin_img.at<uchar>(y,x) = LOWVAL;
            }
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT, gray_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,bin_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
