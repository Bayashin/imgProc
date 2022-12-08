#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./image1.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    int i,x,y;
    
    //画像の入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::Mat dst_img = cv::Mat(src_img.size(),CV_8UC1);
    
    for (y=0; y<src_img.rows; y++) {
            for (x=0; x<src_img.cols; x++) {
                unsigned char s = src_img.at<unsigned char>(y,x);
                if (s<120) {
                    s=255;
                }else{
                    s=0;
                }
                dst_img.at<unsigned char>(y,x) = s;
            }
    }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
