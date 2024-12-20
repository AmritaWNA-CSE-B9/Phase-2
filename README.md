Paper Link : [Click Here](https://ieeexplore.ieee.org/abstract/document/10593115)
# Phase-2
This project is a skew tolerant video stitching application, which stitches up pre-recorded videos upto 360 degree.

# Modules in the project

## Camera caliberation


For estimating the focal length in pixels, camera calibration is done, this can
be obtained by the checker board experiment. in this experiment a checker board is then printed out and
the picture of it from different angels are taken. 
![image](https://github.com/Karthik-PM/Phase-2/assets/72903849/12ea9ad2-c683-4d86-ab16-1494b9d5a0bf)

this can be take by running the **run.sh file in the take_pics folder** in the camera caliberation module.

Form that the result is obtained by running the **run.sh script in the camera_caliberation folder**.

## Cylinderical projection


This program is used to project the input videos onto a cylinder, this is done by specifying the **input videos in  genrate_cylendrical_videos.cpp** file and then **executing it though the run.sh** script, once the projection is done, then **run the cvid.sh file to get the exported videos**.

## Stitching Module.
![design_2](https://github.com/user-attachments/assets/fb30811a-0b9d-40a1-8ced-54ce3e86a651)

This consists of two modules, CPU and NVIDIA CUDA folder, the input cylendrically warped videos are specified into the sift_warp.cpp file, and the perform the stitching by executing its run.sh program, once the program is finished, the compiled video frames can be merged to a video by executing the script **compile_videos.sh**. If there is a need to extract the **FPS trend of the stitched videos then, a plot can be obtained by running the** **export_stats.py** file.


![CUDA drawio](https://github.com/user-attachments/assets/2454f63f-d90b-45f6-a656-9b431a5adde0)
Allocating warping process inside an NVIDIA GPU.

## Mask Adder
This module is used to project the stitched video to get an immersive view in occulus, the program projects the video into a bigger mask so that, when uploaded into occulus, the result gives a proper immersive view when projected into a sphere. 
The program is executed by **specifying the video file in the maskaAdder.cpp and executing the run.sh file**, this program extracts frames and saves the result into a folder, i**f the output panaroma is above 8K resolution, then resize the video by running the scrpit resize.sh**, which resizes the video and preserves its aspect ratio. then the **final view can be extracted by running the compile_video.sh script**.


## Result and Analysis

There is No drop in FPS when the warping process is given to NVIDIA graphics card, the results have be displayed as shown below.
FPS Trend in CPU:

![CPU_FPS_trend](https://github.com/user-attachments/assets/9c4e481d-9051-46c2-859d-153ab875283f)

FPS Trend in CUDA:

![CUDA_FPS_trend](https://github.com/user-attachments/assets/48bb0d45-8ecb-4c6b-ab46-f3aa384d6e41)




