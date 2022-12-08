#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "input1.jpg"

//テンプレート画像
#define TEMPLATE_NUM (8)
#define TEMPLATE_IMG_0 "template-0.jpg"
#define TEMPLATE_IMG_1 "template-1.jpg"
#define TEMPLATE_IMG_2 "template-2.jpg"
#define TEMPLATE_IMG_3 "template-3.jpg"
#define TEMPLATE_IMG_4 "template-4.jpg"
#define TEMPLATE_IMG_5 "template-5.jpg"
#define TEMPLATE_IMG_6 "template-6.jpg"
#define TEMPLATE_IMG_7 "template-7.jpg"


//----------------------------


int main (int argc, const char * argv[])
{
    cv::Mat target_img, compare_img;
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    float s; //類似度マップはfloat型
    
    //1.入力画像の取得
    target_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
    if (target_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    //2.テンプレート画像を配列で取得
    cv::Mat template_img[TEMPLATE_NUM];
    char buf[256];
    for (int i=0; i<TEMPLATE_NUM; i++) {
        sprintf(buf, "template-%d.jpg", i);
        template_img[i] = cv::imread(buf);
        if (template_img[i].empty()) {
            fprintf(stderr, "%s cannot be opened.", buf);
            return 0; }
    }
    
    //3.8回繰り返す
    for (int i=0; i<TEMPLATE_NUM; i++) {
        //3.1:類似度マップ (1チャンネル)の作成
        compare_img = cv::Mat(cv::Size(target_img.rows - template_img[i].rows + 1, target_img.cols - template_img[i].cols + 1), CV_32F, 1);
        
        //3.2:テンプレートマッチング
        cv::matchTemplate(target_img, template_img[i], compare_img, cv::TM_SQDIFF_NORMED);
           
        //3.3:類似度マップの最小値最大値の計算
        cv::minMaxLoc(compare_img, &min_val, &max_val,&min_loc, &max_loc);

        //3.4:templateのあてはまる場所の左上の座標を出力
        fprintf(stderr,"%d: %d,%d\n",i,min_loc.x,min_loc.y);
    }
    
    return 0;
}
