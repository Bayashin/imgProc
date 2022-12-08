#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME1 "./input1.jpg"
#define FILE_NAMW2 "./input2.jpg"
#define ALPHA (0.3)//透過度
#define WINDOW_NAME_INPUT1 "input1"
#define WINDOW_NAME_INPUT2 "input2"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME1,0); //画像1
    cv::Mat src_img2 = cv::imread(FILE_NAMW2,0); //画像2
    if (src_img1.empty() || src_img2.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    cv::Mat result_img = cv::Mat(src_img1.size(),CV_8UC1);//合成画像
    int x,y;
    
    //合成画像の出力
    for (y=0; y<src_img1.rows; y++) {
        for (x=0; x<src_img2.cols; x++) {
            //画素値の取得(double型)
            double s1 = (double)src_img1.at<unsigned char>(y,x);
            double s2 = (double)src_img2.at<unsigned char>(y,x);
            int s_result = ALPHA * s1 + (1.0-ALPHA) * s2;
            result_img.at<unsigned char>(y,x) = (unsigned char)s_result;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT1, src_img1);  //画像の表示
    cv::imshow(WINDOW_NAME_INPUT2, src_img2);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
