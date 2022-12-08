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
#define TARGET_IMG_FILE "bg.jpg"

//テンプレート画像
#define TEMPLATE_IMG_FILE "face.jpg"

//----------------------------


int main (int argc, const char * argv[])
{
    cv::Mat target_img, template_img, compare_img, result_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s; //類似度マップはfloat型
    
    //入力画像
    target_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    
    if (target_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    //テンプレート画像
    template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_COLOR);
    
    
    //類似度マップ (1チャンネル)
    compare_img = cv::Mat(cv::Size(target_img.rows - template_img.rows + 1, target_img.cols - template_img.cols + 1), CV_32F, 1);
    
    //結果画像
    result_img = cv::Mat(target_img.size(), CV_8UC1);
    result_img = target_img.clone(); //画像のコピー
    
    //ここまでが初期化 (前処理)
    //------------------------------------------------------------
    
    
    //テンプレートマッチング
    fprintf(stderr, "テンプレートマッチングの開始\n");

    cv::matchTemplate(target_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
       
    fprintf(stderr, "テンプレートマッチングの終了\n");
    
    //類似度マップの最小値最大値の計算
   
    cv::minMaxLoc(compare_img, &min_val, &max_val,&min_loc, &max_loc);

    //長方形の表示
    
 
    
    cv::rectangle(result_img,min_loc,cv::Point(min_loc.x+template_img.cols,min_loc.y + template_img.rows),CV_RGB(255,0,0),3);

    fprintf(stderr,"%d,%d\n",min_loc.x,min_loc.y);
    
    //探索画像の描画
    cv::imshow("input", target_img); //入力画像
    cv::imshow("template", template_img); //テンプレート画像
    cv::imshow("result", result_img); //結果画像
    //キー入力待ち
    cv::waitKey(0);

    
    return 0;
}
