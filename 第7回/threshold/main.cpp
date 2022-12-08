#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME1 "./input1.jpg"
#define FILE_NAMW2 "./input2.jpg"
#define THRESHOLD (20) //閾値
#define WINDOW_NAME_INPUT1 "input1"
#define WINDOW_NAME_INPUT2 "input2"
#define WINDOW_NAME_SUB "sub"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像をグレースケールで入力
    cv::Mat src_img1 = cv::imread(FILE_NAME1,0); //画像1
    cv::Mat src_img2 = cv::imread(FILE_NAMW2,0); //画像2
    if (src_img1.empty() || src_img2.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    cv::Mat sub_img = cv::Mat(src_img1.size(),CV_8UC1);//差分画像
    cv::Mat result_img = cv::Mat(src_img1.size(),CV_8UC1);//合成画像
    int x,y;
    
    //合成画像の出力
    for (y=0; y<src_img1.rows; y++) {
        for (x=0; x<src_img2.cols; x++) {
            //画素値の取得(double型)
            int s1 = (int)src_img1.at<unsigned char>(y,x);
            int s2 = (int)src_img2.at<unsigned char>(y,x);
            int s_result = abs(s1 - s2); //差分
            sub_img.at<unsigned char>(y,x) = s_result; //差分画像に出力
            
            if (s_result > THRESHOLD) {//閾値処理
                s_result = 255;
            }else{
                s_result = 0;
            }
            result_img.at<unsigned char>(y,x) = s_result;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT1, src_img1);  //画像の表示
    cv::imshow(WINDOW_NAME_INPUT2, src_img2);
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
