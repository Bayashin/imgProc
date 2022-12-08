#include <iostream>
#include <opencv2/opencv.hpp>
//#define FILE_NAME "./Debug/red_rectangle.jpg"
#define FILE_NAME "./red_rectangle.jpg"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
   //1.変数の宣言
    int i,x,y;//アクセス用の変数
    
    int hist[COLOR_MAX];//ヒストグラム用の配列
    
    //2.画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME,0);
    if (src_img.empty()) {//入力失敗の場合
        fprintf(stderr, "File is not opend\n");
        return (-1);
    }
    
    //3.ヒストグラム用配列の初期化
    for (int i=0; i<COLOR_MAX; i++) {
        hist[i]=0;
    }
    
    //4.ヒストグラムの作成
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            //画素値の取得
            unsigned char s = src_img.at<unsigned char>(y,x);
            //画素値の計算
            hist[s]++;
        }
    }
    
    //5,出力(Numbers or Excel用に印字)
    for (int i=0; i<COLOR_MAX; i++) {
        printf("%d %d\n",i,hist[i]);
    }
    
    return (0);
    
}
