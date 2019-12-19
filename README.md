# Yolo_label


## WHAT IS THIS?!
 Reinventing The Wheel?!!!!
 
 ![1_hfyjxxcfingbcyzcgksaiq](https://user-images.githubusercontent.com/35001605/47629997-b47aa200-db81-11e8-8873-71ae653563e0.png)

 In the world, there are many good image-labeling tools for object detection. -e.g. , ([Yolo_mark](https://github.com/AlexeyAB/Yolo_mark), [BBox-Label-Tool](https://github.com/puzzledqs/BBox-Label-Tool), [labelImg](https://github.com/tzutalin/labelImg)). 
 
But... I've reinvented one...
 
## WHY DID YOU REINVENT THE WHEEL? ARE YOU STUPID?

 When I used the pre-existing programs to annotate a training set for YOLO V3, I was sooooooooooo bored...
 
 So I thought why it is so boring??

 And I found an answer.
 
 The answer is that pre-existing programs are not **sensitive**.
 
 So I decided to make a **sensitive** image-labeling tool for object detection.
 
 ## SHOW ME YOUR SENSITIVE IMAGE-LABELING TOOL!!

 It's the **SENSITIVE** image-labeling tool for object detection!
 
![image](https://user-images.githubusercontent.com/35001605/47644151-bd369c80-dbb0-11e8-9505-d7ada78911c2.png)

![ezgif-5-85c0613befb3](https://user-images.githubusercontent.com/35001605/47693025-3d094900-dc3b-11e8-9d96-ea2f7e37cf7a.gif)

![ezgif-5-c57fe634145b](https://user-images.githubusercontent.com/35001605/47693028-3f6ba300-dc3b-11e8-9e22-70c448d59398.gif)

 ## HMM... I SAW THIS DESIGN SOMEWHERE
  I refer to [the website of Joseph Redmon](https://pjreddie.com/darknet/
) who invented the [YOLO](https://www.youtube.com/watch?v=MPU2HistivI).

  ![redmon2](https://user-images.githubusercontent.com/35001605/47635529-a1270100-db98-11e8-8c03-1dcea7c77d1d.PNG)
# TUTORIAL / USAGE

0. Download this project

**For Windows**

0.1 Download [this](https://drive.google.com/open?id=1MJyMcqRKhiNPzJkRPQ2CmGePK9XddBNP)

0.2 Unzip

0.3 Run YoloLabel.exe

![download_guide](https://user-images.githubusercontent.com/35001605/48674490-4168b800-eb90-11e8-83fb-8ef7b5fd1040.PNG)


1. Put your .jpg, .png -images into a directory
(In this tutorial I will use the Kangarooo and the Raccoon Images. These images are in the 'Samples' folder.)

![dataset](https://user-images.githubusercontent.com/35001605/47704306-8e7afd80-dc66-11e8-9f28-13010bd2d825.PNG)

2. Put the names of the objects, each name on a separate line and save the file( .txt, .names).

![objnames](https://user-images.githubusercontent.com/35001605/47704259-75724c80-dc66-11e8-9ed1-2f84d0240ebc.PNG)

3. Run Yolo Label!

![image](https://user-images.githubusercontent.com/35001605/47644151-bd369c80-dbb0-11e8-9505-d7ada78911c2.png)

4. Click the button 'Open Files' and open the folder with the images and the file('*'.names or '*'.txt) with the names of the objects.

 ![image](https://user-images.githubusercontent.com/35001605/47694149-d20e4100-dc3f-11e8-9d97-fba87a6e1b5a.png)

5. And... Label!... Welcome to Hell... I really hate this work in the world.

This program has adopted a different labeling method from other programs that adopt **"drag and drop"** method.

To minimize wrist strain when labeling, I adopted the method **"twice left button click"** method more convenient than 

**"drag and drop"** method.

**drag and drop**

![draganddrop](https://user-images.githubusercontent.com/35001605/48674135-6fe49400-eb8c-11e8-963c-c343867b7565.gif)


**twice left button click**

![twiceleftbuttonclickmethod](https://user-images.githubusercontent.com/35001605/48674136-71ae5780-eb8c-11e8-8d8f-8cb511009491.gif)


![ezgif-5-805073516651](https://user-images.githubusercontent.com/35001605/47698872-5bc80980-dc54-11e8-8984-e3e1230eccaf.gif)

6. End

![endimage](https://user-images.githubusercontent.com/35001605/47704336-a6528180-dc66-11e8-8551-3ecb612b7353.PNG)

## SHORTCUTS

| Key | Action |
|---|:---:|
| `A` | Save and Prev Image  |
| `D,  Space` | Save and Next Image |
| `S` | Next Label <br> ![ezgif-5-f7ee77cd24c3](https://user-images.githubusercontent.com/35001605/47703190-d3049a00-dc62-11e8-846f-5bd91e98bdbc.gif)  |
| `W` | Prev Label <br> ![ezgif-5-ee915c66dad8](https://user-images.githubusercontent.com/35001605/47703191-d39d3080-dc62-11e8-800b-986ec214b80c.gif)  |
| `Ctrl + S` | Save |
| `Ctrl + C` | Delete all existing bounding boxes in the image |

| Mouse | Action |
|---|:---:|
| `Right Click` | Delete Focused Bounding Box in the image <br> ![ezgif-5-8d0fb51bec75](https://user-images.githubusercontent.com/35001605/47706913-c20d5600-dc6d-11e8-8a5c-47065f6a6416.gif) |
| `Wheel Down` | Save and Next Image  |
| `Wheel Up` | Save and Prev Image |

## Button Events

### Remove

![ezgif-2-90fb8205437e](https://user-images.githubusercontent.com/35001605/49983945-fbddb600-ffa8-11e8-9672-f7b71e4e603b.gif)

## ETC

You can access all image by moving horizontal slider bar. But when you control horizontal slider bar, the last processed image will not be saved automatically. So if you want not to lose your work, you should save before moving the horizontal slider bar.

![ezgif-5-53abf38b3387](https://user-images.githubusercontent.com/35001605/47708528-97bd9780-dc71-11e8-94f1-5ee23776d5fe.gif)

# CONCLUSIONS
I've reinvented the wheel.
![dont-reinvent-the-wheel](https://user-images.githubusercontent.com/35001605/47709289-46160c80-dc73-11e8-8ef6-6af3a3c52403.jpg)

# Thank You!

[Image extracting from Videos](http://nickswimsfast.blogspot.com/2019/11/image-extracting-from-videos.html)

# TO DO LISTS
Upload binary file for easy usage for windows and ubuntu

filename sorting by index

deployment for ubuntu

Image zoom
