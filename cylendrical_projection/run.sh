g++ -I/usr/include/xtensor/ -I/usr/include/xtl/ -g ./genrate_cylendrical_videos.cpp -o out `pkg-config --cflags --libs opencv`
./out
rm ./out