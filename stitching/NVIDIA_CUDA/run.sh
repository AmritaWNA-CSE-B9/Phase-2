file='sift_warp_CUDA.cpp'
g++ -g $file -o out `pkg-config --cflags --libs opencv`
# gprof ./out 
./out 
rm ./out
