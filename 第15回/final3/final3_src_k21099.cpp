#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./input1.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_BIN "bin"
#define COUNT (8)
#define TH (50)
#define MAX_VAL (255)
#define R_MIN (150)
#define G_MAX (100)
#define B_MAX (100)

int main(int argc, const char * argv[]) {
    //1.画像の入力
    cv::Mat src_img,gray_img,bin_img,dst_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    dst_img = src_img.clone();
    
    bin_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGRA2GRAY);
    
    //2.てんとう虫を判別して二値化
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            cv::Vec3b p = src_img.at<cv::Vec3b>(y,x);
            uchar s_b = gray_img.at<uchar>(y,x);
            if ((p[0] <= B_MAX && p[1] <= G_MAX && p[2] >= R_MIN) || s_b < TH) {
                bin_img.at<uchar>(y, x) = MAX_VAL;
            }
        }
    }
    
    //3.クロージング・オープニング
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1),COUNT);
    cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1),COUNT);
    cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1),COUNT);
    
    //4.輪郭を取得
    std::vector< std::vector< cv::Point > > contours;
    cv::findContours(bin_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    
    //5.面積の最大を取得
    int num =0;
    double S_tmp = 0;
    for (int i=0; i<contours.size(); i++) {
        double S = cv::contourArea(contours[i]);
        if (S_tmp < S) {
            S_tmp = S;
            num = i;
        }
    }
    
    //6.てんとう虫の周りに四角を表示
    cv::rectangle(dst_img, cv::boundingRect(contours[num]), CV_RGB(0, 0, 0), 3);
    
    //7.画像の表示
    cv::imshow(WINDOW_NAME_BIN, dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
