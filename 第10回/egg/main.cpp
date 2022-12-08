#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./challenge.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,tmp_img,dst_img,gray_img;//画像の型と変数
//    int hist[COLOR_MAX];
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
//    for (int i=0; i<COLOR_MAX; i++) {
//                hist[i]=0;
//            }
//
//        for (int y=0; y<src_img.rows; y++) {
//               for (int x=0; x<src_img.cols; x++) {
//                   //画素値の取得
//                   unsigned char s = src_img.at<unsigned char>(y,x);
//                   //画素値の計算
//                   hist[s]++;
//               }
//           }
//
//    for (int i=0; i<COLOR_MAX; i++) {
//                printf("%d %d\n",i,hist[i]);
//            }
    
    int bin_th = 210;
    
    
    std::vector<std::vector<cv::Point>> contours;

    cv::cvtColor(src_img, gray_img, cv::COLOR_RGB2GRAY);

    cv::threshold(gray_img, dst_img, bin_th, 255, cv::THRESH_BINARY);

    tmp_img = dst_img.clone();

    cv::findContours(dst_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    int num = 0;
    for (int i=0; i<contours.size(); i++) {
        double L = cv::arcLength(contours[i], true);
        double S = cv::contourArea(contours[i]);//面積
        if ( S >= 50) {
            num++;
        }
    }

    printf("%d\n",num);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
