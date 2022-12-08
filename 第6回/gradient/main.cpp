#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./sakadati.jpg"
#define WINDOW_NAME_INPTU "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //1.画像をグレイスケールで入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    //グレースケール化
    cv::Mat gry_img;
    cv::cvtColor(src_img, gry_img, cv::COLOR_BGR2GRAY);
    
    //2.出力画像の宣言(処理4で自動的にメモリ確保される）
    cv::Mat dst_img;

    //3.フィルタの宣言と設計（入力と正規化）
    //フィルタ
    double filter_hH[] = {0.,-1.,0.,0.,0.,0.,0.,1.,0.};
    double filter_hV[] = {0.,0.,0.,-1.,0.,1.,0.,0.,0.};
    ////配列をフィルタ行列kernelに変換（縦）
    cv::Mat kernel_H = cv::Mat(3,3,CV_64F,filter_hH);
    //4.フィルタの計算(縦）
    cv::Mat H_img;   //一時的に格納する画像を用意
    cv::filter2D(gry_img, H_img, CV_64F, kernel_H);
    
    ////配列をフィルタ行列kernelに変換（横）
    cv::Mat kernel_V = cv::Mat(3,3,CV_64F,filter_hV);
    //4.フィルタの計算(横）
    cv::Mat V_img;   //一時的に格納する画像を用意
    cv::filter2D(gry_img, V_img, CV_64F, kernel_V);
    
    double h,v;
    cv::Mat G_img = cv::Mat(src_img.size(),CV_64F);
    for (int y=0; y<H_img.rows; y++) {
                for (int x=0; x<H_img.cols; x++) {
                    h = H_img.at<double_t>(y, x);
                    v = V_img.at<double_t>(y, x);
                    double gradient =sqrt(h * h + v * v);
                    G_img.at<double_t>(y, x)=gradient;
                }
        }
    
    //表示用に値を変換
    cv::convertScaleAbs(G_img, dst_img);

    //5.出力
    cv::imshow(WINDOW_NAME_INPTU, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)

    return (0);

}
