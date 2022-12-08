#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./gem1.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define R_MIN (0)
#define R_MAX (50)
#define G_MIN (50)
#define G_MAX (100)
#define MAX_VAL (255)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,dst_img;//画像の型と変数
    cv::Vec3b p;
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            p = src_img.at<cv::Vec3b>(y,x);
            if (p[1] >= G_MIN && p[1] <= G_MAX && p[2] >= R_MIN && p[2] <= R_MAX) {
                dst_img.at<uchar>(y,x) =MAX_VAL;
            }
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
