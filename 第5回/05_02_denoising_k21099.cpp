#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./dot_gray_rectangle.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define FILTER_SIZE (40)
#define COLOR_MAX (256)


int main(int argc, const char * argv[]) {
    
    int hist[COLOR_MAX];
    
    //1.画像をグレイスケールで入力
    cv::Mat src_img;//画像の型と変数
    src_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    //2.出力画像の宣言(処理4で自動的にメモリ確保される）
    cv::Mat blur_img;
    //3.フィルタの宣言と設計（入力と正規化）
    //フィルタa
    int filesize = FILTER_SIZE*FILTER_SIZE;
    double filter_h[filesize];
    for (int i=0; i<filesize; i++) {
        filter_h[i] = 1.0/filesize;
    }printf("\n");
    ////配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(FILTER_SIZE,FILTER_SIZE,CV_32F,filter_h);
    //正規化(正規化しないと画素数が255を超えるため）
    cv::normalize(kernel, kernel, 1.0,0.0,cv::NORM_L1);
    //4.フィルタの計算
    cv::filter2D(src_img, blur_img, -1, kernel);
    
    for (int i=0; i<COLOR_MAX; i++) {
                hist[i]=0;
            }

        for (int y=0; y<src_img.rows; y++) {
               for (int x=0; x<src_img.cols; x++) {
                   //画素値の取得
                   unsigned char s = blur_img.at<unsigned char>(y,x);
                   //画素値の計算
                   hist[s]++;
               }
           }

        for (int i=0; i<COLOR_MAX; i++) {
                printf("%d %d\n",i,hist[i]);
            }
    
    cv::Mat dst_img = cv::Mat(blur_img.size(),CV_8UC1);
    
    for (int y=0; y<src_img.rows; y++) {
                for (int x=0; x<src_img.cols; x++) {
                    unsigned char s = blur_img.at<unsigned char>(y,x);
                    if (s<77) {
                        s=255;
                    }else{
                        s=0;
                    }
                    dst_img.at<unsigned char>(y,x) = s;
                }
        }
    
    //5.出力
    cv::imshow(WINDOW_NAME_INPUT, src_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return (0);

}
