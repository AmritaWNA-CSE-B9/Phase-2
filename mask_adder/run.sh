file='./maskAdder.cpp'
g++ -g $file -o out `pkg-config --cflags --libs opencv`
# gprof ./out 
./out 
rm ./out
