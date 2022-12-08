#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./apple_grayscale.jpg"
#define WINDOW_NAME_INPTU "input"
#define WINDOW_NAME_OUTPUT "output"

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
    
    //3.フィルタの宣言と設計（入力と正規化）
    //フィルタa
//    double filter_h[] = {3.,3.,1.,-1.,2.,1.,0.,1.,1.};
//    double filter_h[] = {1./16.,2./26.,1./16.,2./16.,1./16.,2./16.,1./16.,2./26.,1./16.};
    double filter_h[] = {0.,0.,0.,-1.,0.,1,0.,0.,0.};
    ////配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(3,3,CV_64F,filter_h);
    //正規化(正規化しないと画素数が255を超えるため）
    cv::normalize(kernel, kernel, 1.0,0.0,cv::NORM_L1);
    //4.フィルタの計算
    cv::Mat tmp_img;   //一時的に格納する画像を用意
    cv::filter2D(src_img, tmp_img, CV_64F, kernel);
    cv::convertScaleAbs(tmp_img, dst_img);
    
    //5.出力
    cv::imshow(WINDOW_NAME_INPTU, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
