file='sift_warp_CPU.cpp'
g++ -g $file -o out `pkg-config --cflags --libs opencv`
./out 
rm ./out
