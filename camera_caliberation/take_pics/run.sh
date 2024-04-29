# g++ -I/usr/include/xtensor/ -I/usr/include/xtl/ -g caliberation.cpp -o out `pkg-config --cflags --libs opencv`
g++ -I/usr/include/xtensor/ -I/usr/include/xtl/ -g takepics.cpp -o out `pkg-config --cflags --libs opencv`
# gdb ./out
./out
rm ./out
