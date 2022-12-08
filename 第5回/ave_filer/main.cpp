#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./apple_grayscale.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_OUTPUT2 "output2"

int main(int argc, const char * argv[]) {
    //1.画像をグレイスケールで入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    //2.出力画像の宣言(処理4で自動的にメモリ確保される）
    cv::Mat dst_img;
    cv::Mat dst2_img;

    //3.フィルタの宣言と設計（入力と正規化）
    //フィルタa
    double filer_h[] = {1/9.,1/9.,1/9.,1/9.,1/9.,1/9.,1/9.,1/9.,1/9.};
    //フィルタb
    double filer_h1[] = {1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.,1/25.};
    ////配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(3,3,CV_32F,filer_h);
    cv::Mat kernel1 = cv::Mat(5,5,CV_32F,filer_h1);
    //正規化(正規化しないと画素数が255を超えるため）
    cv::normalize(kernel, kernel, 1.0,0.0,cv::NORM_L1);
    cv::normalize(kernel1, kernel1, 1.0,0.0,cv::NORM_L1);
    //4.フィルタの計算
    cv::filter2D(src_img, dst_img, -1, kernel);
    cv::filter2D(src_img, dst2_img, -1, kernel1);
    //5.出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::imshow(WINDOW_NAME_OUTPUT2, dst2_img);
    cv::waitKeyEx();
    
    return (0);
    
}
