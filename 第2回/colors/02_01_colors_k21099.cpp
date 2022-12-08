//
//  02_01_colors_k21099.cpp
//  
//
//  Created by k21099kk on 2022/04/20.
//

#include <iostream>
//OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル（サイズは小さめが良い）
#define FILE_NAME "./aquarium.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    int x,y;
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME);
    if(src_img.empty()) { //入力失敗の場合
        return (-1);
    }
    
    //出力メモリの確保
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
    
    //画像の走査
    int cols = src_img.cols/6;
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            //画素値の取得
            cv::Vec3b s = src_img.at<cv::Vec3b>(y,x);
            if(x<cols){
                s[0]=0;
                s[1]=0;
                s[2]=0;
            }else if(x>=cols && x<cols*2){
                s[0]=0;
                s[1]=0;
                s[2]=s[2];
            }else if(x>=cols*2 && x<cols*3){
                s[0]=s[0];
                s[1]=0;
                s[2]=0;
            }else if(x>=cols*3 && x<cols*4){
                s[0]=0;
                s[1]=s[1];
                s[2]=0;
            }else if(x>=cols*4 && x<cols*5){
                s[0]=255;
                s[1]=255;
                s[2]=255;
            }else if(x>=cols*5 && x<src_img.cols){
                s[0] = s[0];
                s[1] = s[1];
                s[2] = s[2];
            }
            dst_img.at<cv::Vec3b>(y,x) = s;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); //画像の表示
    cv::waitKey(); //キー入力待ち(止める）
    
    return 0;
}

