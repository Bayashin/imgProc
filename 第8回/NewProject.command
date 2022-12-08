#!/bin/zsh

echo -n "プロジェクト名を入力してください: "
read NAME

# cd ~/desktop/programs/opencv

mkdir $NAME

cp pleanProject/main.cpp $NAME
cp pleanProject/CMakeLists.txt $NAME

cd $NAME

cmake ./ -G Xcode

ls

# mkdir Debug
# cp ../pleanProject/twitter.jpg Debug

open main.xcodeproj
