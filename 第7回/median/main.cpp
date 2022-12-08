#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./apple_grayscale.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define FILTER_SIZWE (19) //フィルタサイズ（3以上の奇数)

int main(int argc, const char * argv[]) {
    //画像をグレースケールで入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::Mat median_img;//出力画像の宣言
    
    //メディアンフィルタ（入力,出力,フィルタサイズ)
    cv::medianBlur(src_img, median_img, FILTER_SIZWE);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, median_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
