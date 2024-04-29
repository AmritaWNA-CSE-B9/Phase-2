file='caliberation.cpp'
# file='caliberation1.cpp'
g++ -g $file -o out `pkg-config --cflags --libs opencv`
./out 
rm ./out
