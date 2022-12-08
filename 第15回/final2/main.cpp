#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./input1.jpg"
#define WINDOW_NAME_INPTU "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //1.画像をカラーで入力し、グレイスケール化
    cv::Mat src_img,gray_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //2.出力画像の宣言(処理4で自動的にメモリ確保される）
    cv::Mat tmp_img;//一時的な画像
    cv::Mat dst_img;//結果画像

    
    //3.ソーベルフィルタ
    cv::Sobel(gray_img, tmp_img, CV_32F, 1, 0);
    
    //4.適切な出力画像に変換
    cv::convertScaleAbs(tmp_img,dst_img);
   
    //5.出力
    cv::imshow(WINDOW_NAME_INPTU, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
