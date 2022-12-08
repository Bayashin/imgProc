#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./red_green_rectangle.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT_RED "output_red"
#define WINDOW_NAME_OUTPUT_GREEN "output_green"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    //グレイスケール画像のメモリ
    cv::Mat gry_r_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat gry_g_img = cv::Mat(src_img.size(), CV_8UC1);
    
    //単色画像のメモリ確保
    cv::Mat bin_r_img = cv::Mat(src_img.size(), CV_8UC3);
    cv::Mat bin_g_img = cv::Mat(src_img.size(), CV_8UC3);

    //1.画像の画素を取得し、赤、緑の単色画像を作成
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //画素値の取得
            cv::Vec3d s_r = src_img.at<cv::Vec3b>(y,x);
            cv::Vec3d s_g = src_img.at<cv::Vec3b>(y,x);
            
            //単色の画像作成
            s_r[0]=0;
            s_r[1]=0;
            s_r[2]=s_r[2];
            
            s_g[0]=0;
            s_g[1]=s_g[1];
            s_g[2]=0;
            
            bin_r_img.at<cv::Vec3b>(y,x) = s_r;
            bin_g_img.at<cv::Vec3b>(y,x) = s_g;
        }
    }
    
    //2.単色画像から輝度画像を作成
    cv::cvtColor(bin_r_img, gry_r_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(bin_g_img, gry_g_img, cv::COLOR_BGR2GRAY);
    
    //3.輝度画像から判別分析法により二値化
    cv::threshold(gry_g_img, bin_r_img, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::threshold(gry_r_img, bin_g_img, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT_RED,bin_r_img);
    cv::imshow(WINDOW_NAME_OUTPUT_GREEN, bin_g_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
