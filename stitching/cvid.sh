cd ./mask_output/
# resize image
# ffmpeg -r 30 -i "output_image_%d.png" -vf scale=1920:1080 output.mp4

# extract videos from incomming images
ffmpeg -r 30 -i "output_image_%d.png" -c:v libx264 -crf 20 -pix_fmt yuv420p output_final.mp4
# ffmpeg -r 30 -i "output_image_%d.png" -c:v h264_nvenc -preset slow -crf 20 -pix_fmt yuv420p output_final.mp4
