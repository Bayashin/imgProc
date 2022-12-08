#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./ptile.jpg"
#define WINDOW_NAME_INPUT "intput"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat gray_img;//画像の型と変数
    gray_img = cv::imread(FILE_NAME,0); //画像の読み込み
    if (gray_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);    
    }
    
    //二値画像のメモリ確保
    cv::Mat bin_img;
    bin_img = cv::Mat(gray_img.size(), CV_8UC1);
    
    //閾値を求める
    //面積を求める
    int area=0;
    int hist[COLOR_MAX];
    for (int i=0; i<COLOR_MAX; i++) {
                hist[i]=0;
            }
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            area++;
            //画素値の取得
            unsigned char s = gray_img.at<unsigned char>(y,x);
            //画素値の計算
            hist[s]++;
        }
    }
    //比率を求める
    double p = 1.0/(4.0+1.0);
    int t=0,s_sum=0;
    for (int i=0; i<COLOR_MAX; i++) {
        s_sum += hist[i];
        //0〜iの輝度値の合計を出力
        printf("%d %d\n",i,s_sum);
        if ((area - (p*area))<=s_sum) {
            t = i;
            break;
        }
    }
    printf("\n %f\n",area-p*area);
    printf("全体の面積：%d\n 対象の面積：%f\n 閾値：%d\n",area,p*area,t);
    
    //二値画像に変換
    cv::threshold(gray_img, bin_img, t, 255, cv::THRESH_BINARY);
    
    cv::imshow(WINDOW_NAME_INPUT, gray_img);  //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT,bin_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return (0);
    
}
