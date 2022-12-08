#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./GUNDAM.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME "tmp"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    //出力画像の変数宣言(グレースケール）
    cv::Mat tmp_img;
    cv::Mat dst_img;
    //グレースケール化
    cv::cvtColor(src_img, tmp_img, cv::COLOR_BGR2GRAY);
    
    double filter_h[] = {-1.,-1.,-1.,0.,0.,0.,1.,1.,1.};
        ////配列をフィルタ行列kernelに変換
        cv::Mat kernel = cv::Mat(3,3,CV_64F,filter_h);
        //4.フィルタの計算
        cv::Mat tmp2_img;   //一時的に格納する画像を用意
        cv::filter2D(tmp_img, tmp2_img, CV_64F, kernel);
        cv::convertScaleAbs(tmp2_img, dst_img);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
//    cv::imshow(WINDOW_NAME, tmp2_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
