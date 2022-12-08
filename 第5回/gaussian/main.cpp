#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./apple_grayscale.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (5)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    //2.出力画像の宣言、メモリ確保はGaussianBlurが実施
    cv::Mat dst_img;
    
    //3.ガウシアンフィルタ
    cv::GaussianBlur(src_img, dst_img, cv::Size(FILTER_SIZE, FILTER_SIZE), 0);
    
    //4.表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
