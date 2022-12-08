#include <iostream>
#include <math.h>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//テンプレート画像
#define TEMPLATE_NUM (8)

#define WINDOW_TEST1 ("test1")
#define WINDOW_TEST2 ("test2")
#define WINDOW_NAME ("output")

int main(int argc, const char * argv[]) {
    cv::Mat hsv_I_img,hsv_J_img,tmp_img,dst_img,dst_1_img,dst_2_img;

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
    //list[i] = [template_img[i]に右の画像の番号,色値の差の絶対値の合計]
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
        //4.1色値の差の総和が3000を超えている場合
        if (list[i][1] > 3000) {
            list[i][0] = -1; list[i][1] = -1;
        }
        //4.3:list[i][1]が3000を超えていないが一番右に位置するtemplate_img[i]を特定
        for (int j=0; j<TEMPLATE_NUM; j++) {
            //4.3.1:スキップ
            if(j==i) continue;
            //4.3.2:同じ画像を次の画像に指定していて、かつ色値の差の絶対値の総和がlist[i]の方が大きい場合
            if (list[i][0] == list[j][0] && list[i][1] - list[j][1] > 0 && list[i][0] != -1) {
                list[i][0] = -1; list[i][1] = -1;
            }
        }
    }

    //5.template画像を横に並べる
    //5.1:横の並びを格納する配列（-1,右→左の画像）
    int num[5];
    //5.2:回回す
    for (int i=0; i<2; i++) {
        //5.2.1:numの初期化
        int n=0;
        for (int j=0; j<5; j++) {
            num[j] = 0;
            if (j==0) num[j] = -1;
        }
        //5.2.2:右の画像から順に取得
        for (int j=0; j<4; j++) {
            //5.2.2.1:テンプレート画像を順に見ていく
            for (int k=0; k<TEMPLATE_NUM; k++) {
                //5.2.2.1.1:template_img[num[n]]の左の画像が見つかった時
                if (list[k][0] == num[n]) {
                    n++;
                    num[n] = k;
                    list[k][0] = 100; list[k][1] = 100;
                    break;
                }
            }
        }
        
        //5.3:上段、下段の画像をそれぞれ取得
        tmp_img = template_img[num[4]].clone();
        for (int k=3; k>0; k--) {
            cv::hconcat(tmp_img, template_img[num[k]], tmp_img);
        }
        switch (i) {
            case 0:
                dst_1_img = tmp_img.clone(); break;
            default:
                dst_2_img = tmp_img.clone(); break;
        }
    }
    
    //6.dst_1_imgとdst_2_imgのどちらが上段なのかを判断
    int difference[2]  = {0,0};
    //6.1:i=0 ->tmp_1が上、i=1 ->tmp_2が上の時の色値の差の絶対値の総和
    for (int i=0; i<2; i++) {
        cv::Mat tmp_1_img,tmp_2_img;
        tmp_1_img = dst_1_img.clone();
        tmp_2_img = dst_2_img.clone();
        if (i == 1){
            tmp_1_img = dst_2_img.clone();
            tmp_2_img = dst_1_img.clone();
        }
        //6.1.1:色変換(GBR -> HSV)
        cv::cvtColor(tmp_1_img, hsv_I_img, cv::COLOR_BGR2HSV);
        cv::cvtColor(tmp_2_img, hsv_J_img, cv::COLOR_BGR2HSV);
        //6.1.2:色値の差の絶対値の総和を求める
        int diff=0;
        int Y = tmp_1_img.rows - 1;
        for (int x=0; x<tmp_1_img.cols; x++) {
            int sI = tmp_1_img.at<cv::Vec3b>(Y,x)[0];
            int sJ = tmp_2_img.at<cv::Vec3b>(0,x)[0];
            diff += fabs(sI-sJ);
        }
        difference[i] = diff;
    }
    //6.2:色値の差の絶対値の総和が小さい方が正しい組み合わせ
    if (difference[0] < difference[1]) {
        cv::vconcat(dst_1_img, dst_2_img, dst_img);
    }else {
        cv::vconcat(dst_2_img, dst_1_img, dst_img);
    }
    
    //7.結果の出力
    cv::imshow(WINDOW_NAME, dst_img);
    cv::waitKey();
    
    return (0);
}
