cd ./pano_res/
ffmpeg -v verbose -r 30 -i "pano_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Pano_res.mp4

