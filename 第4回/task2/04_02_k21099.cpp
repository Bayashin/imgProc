#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./image2.jpg"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    int i,x,y;
    int hist[COLOR_MAX];
    
    //画像の入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    for (int i=0; i<COLOR_MAX; i++) {
            hist[i]=0;
        }
    
    for (int y=0; y<src_img.rows; y++) {
           for (int x=0; x<src_img.cols; x++) {
               //画素値の取得
               unsigned char s = src_img.at<unsigned char>(y,x);
               //画素値の計算
               hist[s]++;
           }
       }
    
    int area=0;
    for (int i=0; i<121; i++) {
        area += hist[i];
    }
    
    printf("%d\n",area);
    
    return (0);
}
