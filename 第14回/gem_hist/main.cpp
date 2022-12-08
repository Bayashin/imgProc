#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./gem1.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,gray_img,dst_img;//画像の型と変数
    int hist[COLOR_MAX];
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    for(int i = 0; i<COLOR_MAX; i++) {
        hist[i] = 0;
    }
    for (int y= 0; y<gray_img.rows; y++) {
        for (int x = 0; x<gray_img.cols; x++) {
            uchar s = gray_img.at<uchar>(y,x);
            hist[(int)s]++;
        }
    }
    for(int i=0; i<COLOR_MAX; i++){
        printf("%d\n",hist[i]);
    }
    
//    cv::Canny(gray_img, dst_img, 100, 200);
    
    cv::imshow(WINDOW_NAME_INPUT, gray_img);  //画像の表示
//    cv::imshow(WINDOW_NAME_OUTPUT,dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
