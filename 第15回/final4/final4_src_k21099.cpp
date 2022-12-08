#include <iostream>
#include <math.h>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//テンプレート画像
#define TEMPLATE_NUM (8)

int main(int argc, const char * argv[]) {
    cv::Mat hsv_I_img,hsv_J_img,tmp_img;

    //1.テンプレート画像を配列で取得
    cv::Mat template_img[TEMPLATE_NUM];
    char buf[256];
    for (int i=0; i<TEMPLATE_NUM; i++) {
        sprintf(buf, "template-%d.jpg", i);
        template_img[i] = cv::imread(buf);
        if (template_img[i].empty()) {
            fprintf(stderr, "%s cannot be opened.", buf);
            return 0;
        }
    }
    
    int X = template_img[0].cols-1;
    int list[TEMPLATE_NUM][2];
    
    //2.listの初期化
    for (int i=0; i<TEMPLATE_NUM; i++) {
        list[i][0] = -1; list[i][1] = 180*template_img[0].rows;
    }
    
    //3.template_img[i]の一つ右の画像を特定
    for (int i=0; i<TEMPLATE_NUM; i++) {
        //3.1:色変換(GBR -> HSV)
        cv::cvtColor(template_img[i], hsv_I_img, cv::COLOR_BGR2HSV);
        for (int j=0; j<TEMPLATE_NUM; j++) {
            //3.2:スキップ
            if (j==i) continue;
            //3.3:色変換(GBR -> HSV)
            cv::cvtColor(template_img[j], hsv_J_img, cv::COLOR_BGR2HSV);
            //3.4:色値の差の絶対値の総和を求める
            int difference=0;
            for (int y=0; y<template_img[0].rows; y++) {
                int sI = hsv_I_img.at<cv::Vec3b>(y,X)[0];
                int sJ = hsv_J_img.at<cv::Vec3b>(y,0)[0];
                difference += fabs(sI-sJ);
            }
            //3.5:現在格納されている値よりdifferenceが小さければ入れ替え
            if (list[i][1] > difference) {
                list[i][0] = j; list[i][1] = difference;
            }
        }
    }
    
    //4.一番右の画像を特定
    for (int i=0; i<TEMPLATE_NUM; i++) {
        //4.1色値の差の総和が5000を超えている場合
        if (list[i][1] > 3000) {
            list[i][0] = -1; list[i][1] = -1;
        }
        //4.3:list[i][1]が5000を超えていないが一番右に位置するtemplate_img[i]を特定
        for (int j=0; j<TEMPLATE_NUM; j++) {
            //4.3.1:スキップ
            if(j==i) continue;
            //4.3.2:同じ画像を次の画像に指定していて、かつ色値の差の絶対値の総和がlist[i]の方が大きい場合
            if (list[i][0] == list[j][0] && list[i][1] - list[j][1] > 0 && list[i][0] != -1) {
                list[i][0] = -1; list[i][1] = -1;
            }
        }
    }
    
    //5.結果の出力
    for (int i=0; i<TEMPLATE_NUM; i++) printf("%d -> %d\n",i,list[i][0]);
    
    return (0);
}
