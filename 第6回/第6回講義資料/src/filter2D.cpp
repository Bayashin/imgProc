//
//  filter2D.cpp
//  
//
//  Created by Masashi Morimoto on 2022/05/17.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "apple_grayscale.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //1. 画像をグレースケールで入力
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    //2. 出力画像変数の宣言 (処理4で自動的にメモリ確保される)
    cv::Mat dst_img;
   //3. フィルタの宣言と設計 (入力と正規化)
    //フィルタh
    double filter_h[] = { 3., 3., 1.,
                         -1., 2., 1.,
                          0., 1., 1.};

    ////配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(3, 3, CV_32F, filter_h);
    //正規化 (正規化しないと画素値が255を超えるため)
    cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
   
    //4. フィルタの計算
    cv::filter2D(src_img, tmp_img, CV_32F, kernel);
   
    //5. 出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);//画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}

