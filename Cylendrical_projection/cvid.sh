# cd ./panores/
# ffmpeg -r 30 -i "pano_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Right_cyl.mp4

# cd ./output_frames/back/

# cd Mid
# ffmpeg -r 30 -i "Mid_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Mid_cyl.mp4
# cp -r ./Mid_cyl ../../
# cd ../Left

# ffmpeg -r 30 -i "Left_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Left_cyl.mp4
# cp -r ./Left_cyl ../../

# cd ../Right

# cp -r ./Right_cyl ../../
# ffmpeg -r 30 -i "Right_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Right_cyl.mp4

cd ./output_frames/side/

cd Left
ffmpeg -r 30 -i "Left_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Left_cyl.mp4
cp -r ./Left_cyl.mp4 ../../
cd ../Right

ffmpeg -r 30 -i "Right_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p Right_cyl.mp4
cp -r ./Right_cyl.mp4 ../../

