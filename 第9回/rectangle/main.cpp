//
//  contour4student.cpp
//
//
//  Created by Masashi Morimoto on 2022/06/07.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

//ファイル
#define FILE_NAME "sample.jpg"
#define FILE_NAME_2 "sample_rotate.jpg"
//ウィンドウ名
#define WINDOW_NAME_OUTPUT_2 "output2"
#define WINDOW_NAME_OUTPUT "output"

//二値化しきい値
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_1_img,src_2_img, gray_1_img,gray_2_img, bin_1_img,bin_2_img, tmp_1_img,tmp_2_img, dst_1_img, dst_2_img;
    
    //2. 輪郭の座標リストの宣言 (New!)
    std::vector< std::vector< cv::Point > > contours_1;
    std::vector< std::vector< cv::Point > > contours_2;
    
    //3. 画像の入力 (カラーで入力)
    src_1_img = cv::imread(FILE_NAME);
    if (src_1_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    src_2_img = cv::imread(FILE_NAME_2);
    if (src_2_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を出力画像にコピー (New!)
    dst_1_img = src_1_img.clone();
    dst_2_img = src_2_img.clone();
    
    //5. グレースケール化
    cv::cvtColor(src_1_img, gray_1_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(src_2_img, gray_2_img, cv::COLOR_BGR2GRAY);
    
    //6. 二値化 (固定しきい値で実装．しきい値: 100)
    cv::threshold(gray_1_img, bin_1_img, BIN_TH, 255, cv::THRESH_BINARY_INV);
    cv::threshold(gray_2_img, bin_2_img, BIN_TH, 255, cv::THRESH_BINARY_INV);
    
    //二値画像コピー (New!)
    tmp_1_img = bin_1_img.clone();
    tmp_2_img = bin_2_img.clone();
    
    //7. 輪郭追跡 (New!)
    cv::findContours(tmp_1_img, contours_1, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    cv::findContours(tmp_2_img, contours_2, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    //8. 輪郭の描画 (New!)
    for (int i=0; i<contours_1.size(); i++) {
        //領域特微量の取得
        double L = cv::arcLength(contours_1[i], true);//周囲長
        double S = cv::contourArea(contours_1[i]);//面積
        //外接長方形の取得
        cv::Rect bb = cv::boundingRect(contours_1[i]);
//        外接長方形の描画
//        cv::rectangle(dst_img, bb, CV_RGB(255, 0, 255), 1);
//        //外接長方形描画後の輪郭の座標リストの宣言
//        std::vector< std::vector< cv::Point > > contours_r;
        //外接長方形の面積
        double S_r = (bb.width-1) * (bb.height-1)-2;
        if (S == S_r) {
            cv::drawContours(dst_1_img, contours_1, i, CV_RGB(255, 0, 255),-1);
//            printf("%f %f\n",S, S_r);
//            printf("%d\n",i);
            break;
        };
    }
    
    //8. 輪郭の描画 (New!)
    for (int i=0; i<contours_2.size(); i++) {
        //領域特微量の取得
        double L = cv::arcLength(contours_2[i], true);//周囲長
        double S = cv::contourArea(contours_2[i]);//面積
        //外接長方形の取得
        cv::Rect bb = cv::boundingRect(contours_2[i]);
//        外接長方形の描画
//        cv::rectangle(dst_img, bb, CV_RGB(255, 0, 255), 1);
//        //外接長方形描画後の輪郭の座標リストの宣言
//        std::vector< std::vector< cv::Point > > contours_r;
        //外接長方形の面積
        double S_r = (bb.width-1) * (bb.height-1)-2;
        if (S == S_r) {
            cv::drawContours(dst_2_img, contours_2, i, CV_RGB(255, 0, 255),-1);
//            printf("%f %f\n",S, S_r);
//            printf("%d\n",i);
            break;
        };
    }
    //9. 表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_1_img);
    cv::imshow(WINDOW_NAME_OUTPUT_2, dst_2_img);
    cv::waitKey();
        
    return 0;
}

