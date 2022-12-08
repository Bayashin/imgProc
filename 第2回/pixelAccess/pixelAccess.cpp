//
//  pixelAccess.cpp
//  
//
//  Created by k21099kk on 2022/04/20.
//

#include <iostream>
//OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル（サイズは小さめが良い）
#define FILE_NAME "./aquarium.jpg"
#define WINDOW_NAME "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img; //画像の方と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if(src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::imshow(WINDOW_NAME, src_img); //画像の表示
    cv::waitKey(30); //キー入力待ち(止める）
    
    fprintf(stderr, "width=%d, height=%d\n",src_img.cols, src_img.rows);
    int x,y;
    while (1){
        scanf("%d %d", &x,&y);
        if (x<0 || y<0) { //負の値の場合
            fprintf(stderr, "終了です\n");
            break;//終了
        }
        if (src_img.cols <= x || src_img.rows <= y){//大きさを超えた場合
            fprintf(stderr, "画面外です\n");
            continue;
        }
        cv::Vec3b val = src_img.at<cv::Vec3b>(y,x);
        printf("%d, %d: (%d, %d, %d)\n",x,y,val[2],val[1],val[0]);
    }
    
    return 0;
}
