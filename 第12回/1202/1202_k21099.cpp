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
#define TEMPLATE_IMG_FILE "red.jpg"

//----------------------------


int main (int argc, const char * argv[])
{
    cv::Mat src_img, template_img, compare_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s; //類似度マップはfloat型
    
    //入力画像
    src_img = cv::imread(TARGET_IMG_FILE, 0);
    
    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    //テンプレート画像
    template_img = cv::imread(TEMPLATE_IMG_FILE, 0);
    
    
    //類似度マップ (1チャンネル)
    compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
    
    //テンプレートマッチング
    fprintf(stderr, "テンプレートマッチングの開始\n");

    cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
       
    fprintf(stderr, "テンプレートマッチングの終了\n");
    
    
    
    //探索画像の描画
    cv::imshow("input", src_img); //入力画像
    cv::imshow("template", template_img); //テンプレート画像
    cv::imshow("result", compare_img); //結果画像
    //キー入力待ち
    cv::waitKey(0);

    
    return 0;
}
