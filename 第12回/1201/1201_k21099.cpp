//
//  main.cpp
//  templateMatching4student
//
//  Created by sawano on 2015/07/05.
//  Modified by Tsukada  2021.07.06
//  Copyright (c) 2015年 AIT. All rights reserved.
//


#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "gazoDora.jpg"

//テンプレート画像
#define TEMPLATE_IMG_G "green.jpg"
#define TEMPLATE_IMG_R "red.jpg"
#define TEMPLATE_IMG_S "star.jpg"
#define TEMPLATE_IMG_Y "yellow.jpg"

#define SIZE (4)

//----------------------------


int main (int argc, const char * argv[])
{
    cv::Mat src_img, compare_img[4], result_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s; //類似度マップはfloat型
    
    //入力画像
    src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    
    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    //テンプレート画像
   cv::Mat template_img[] = {cv::imread(TEMPLATE_IMG_G, cv::IMREAD_COLOR),cv::imread(TEMPLATE_IMG_R, cv::IMREAD_COLOR),cv::imread(TEMPLATE_IMG_S, cv::IMREAD_COLOR),cv::imread(TEMPLATE_IMG_Y, cv::IMREAD_COLOR)};

    //類似度マップ (1チャンネル)
    for (int i=0; i<SIZE; i++) {
        compare_img[i] = cv::Mat(cv::Size(src_img.rows - template_img[i].rows + 1, src_img.cols - template_img[i].cols + 1), CV_32F, 1);
    }
    
    
    //結果画像
    result_img = cv::Mat(src_img.size(), CV_8UC1);
    result_img = src_img.clone(); //画像のコピー
    
    cv::Scalar color[] = {CV_RGB(0, 255, 0), CV_RGB(255, 0, 0), CV_RGB(255, 0, 255), CV_RGB(255, 255, 0)};
    
    //テンプレートマッチング
    fprintf(stderr, "テンプレートマッチングの開始\n");
    for (int i=0; i<SIZE; i++) {
        cv::matchTemplate(src_img, template_img[i], compare_img[i], cv::TM_SQDIFF_NORMED);
    }
    
       
    fprintf(stderr, "テンプレートマッチングの終了\n");
    
    
    //長方形の表示
    for (int i=0; i<SIZE; i++) {
        for(int y=0; y<compare_img[i].rows; y++) {
                    for(int x=0; x<compare_img[i].cols; x++) {
                        s = compare_img[i].at<float>(y, x); //float型で取得
                        if (s < 0.1) { //閾値以下//長方形の表示
                            cv::rectangle(result_img,cv::Point(x,y),cv::Point(x+template_img[i].cols,y+template_img[i].rows),color[i],6);
                        }
                    }
                }
    }
        
    
    //探索画像の描画
    cv::imshow("input", src_img); //入力画像
    cv::imshow("template1", template_img[0]); //テンプレート画像
    cv::imshow("template2", template_img[1]);
    cv::imshow("template3", template_img[2]);
    cv::imshow("template4", template_img[3]);
    cv::imshow("result", result_img); //結果画像
    //キー入力待ち
    cv::waitKey(0);

    
    return 0;
}
