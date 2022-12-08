#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./kagoshima.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //1.変数の宣言
    int x,y;
    
    //変換前の画素値の最小値、最大値、変換後の画素値の最小値、最大値
    unsigned char Imin,Imax,Dmin,Dmax;
    
    //2.初期値の入力(Imax,Imin)
    Imax = 0;
    Imin = 255;
    
    //変換後の画素値の入力
    Dmin = 0;
    Dmax = 255;
    
    //3.画像(グレースケール）の読み込み
    cv::Mat src_img = cv::imread(FILE_NAME,0);
    if (src_img.empty()) {//入力失敗の場合
        fprintf(stderr, "File is not opened");
        return (-1);
    }
    
    //4.出力画像のメモリ確保（グレー）
    cv::Mat dst_img = cv::Mat(src_img.size(),CV_8UC1);
    
    //5.最小値、最大値の取得
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s = src_img.at<unsigned char>(y,x);
            //最小値の取得
            if (Imin > s) {
                Imin = s;
            }
            //最大値の取得
            if (Imax < s) {
                Imax = s;
            }
        }
    }
    
    fprintf(stderr, "Imin = %d\n,Imax = %d\n",Imin,Imax);
    
    //6,線形変換(入力画像、出力画像）
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値に取得
            unsigned char s = src_img.at<unsigned char>(y,x);
            s = (Dmax - Dmin) / (Imax - Imin) * (s - Imin) + Dmin;
            
            dst_img.at<unsigned char>(y,x) = s;
        }
    }
    
    //7.表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);//画像の小字
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//画像の表示
    cv::waitKey();//キー入力待ち
    
    return (0);
    
}
