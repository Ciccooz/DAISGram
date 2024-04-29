# DAISGram
Repository for DAISGram project A.A. 2020-2021
## Library - BMP
To test the proper functioning of the library (libbmp) you need to
run the command `make testbmp` and then`. /test_bmplib`.

If all went well, it should generate a chessboard.

![Checkboard](https://github.com/Ciccooz/DAISGram/blob/main/checkboard.bmp)

Image | Brighten (+20) | Brighten (+100) | Grayscale
------------ | ------------- | ------------- |-------------
![DAIS](https://github.com/Ciccooz/DAISGram/blob/main/images/dais.bmp) | ![DAIS+20](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_brighten_20.bmp) | ![DAIS+100](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_brighten_100.bmp) | ![DAIS_GRAYSCALE](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_gray.bmp)

Image | Smooth (h=3) | Smooth (h=5) | Smooth (h=7)
------------ | ------------- | ------------- | -------------
![DAIS](https://github.com/Ciccooz/DAISGram/blob/main/images/dais.bmp) | ![DAIS_SMOOTH3](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_smooth_3.bmp) | ![DAIS_SMOOTH5](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_smooth_5.bmp) | ![DAIS_SMOOTH7](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_smooth_7.bmp)

Image | Sharp | Edge | Warhol
------------ | ------------- | ------------- | -------------
![DAIS](https://github.com/Ciccooz/DAISGram/blob/main/images/dais.bmp) | ![DAIS_SHARP](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_sharp.bmp) | ![DAIS_EDGE](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_edge.bmp) | ![DAIS_WARHOL](https://github.com/Ciccooz/DAISGram/blob/main/results/dais_warhol.bmp) |

Image A | Image B | Blend alpha=0 | alpha=0.25 | alpha=0.5 | alpha=0.75 | alpha=1.00
------------ | ------------- | ------------- | ------------- | ------------- | ------------- | -------------
![BLEND_A](https://github.com/Ciccooz/DAISGram/blob/main/images/blend/blend_a.bmp) | ![BLEND_B](https://github.com/Ciccooz/DAISGram/blob/main/images/blend/blend_b.bmp) | ![BLEND0](https://github.com/Ciccooz/DAISGram/blob/main/results/blend/blend_0.00.bmp) | ![BLEND25](https://github.com/Ciccooz/DAISGram/blob/main/results/blend/blend_0.25.bmp) | ![BLEND50](https://github.com/Ciccooz/DAISGram/blob/main/results/blend/blend_0.50.bmp) | ![BLEND75](https://github.com/Ciccooz/DAISGram/blob/main/results/blend/blend_0.75.bmp) | ![BLEND100](https://github.com/Ciccooz/DAISGram/blob/main/results/blend/blend_1.00.bmp)

## Green Screen
Close-Up Piano | Background | GreenScreen
------------ | ------------- | -------------
![PIANO](https://github.com/Ciccooz/DAISGram/blob/main/images/greenscreen/gs_2.bmp) | ![BACKGROUND](https://github.com/Ciccooz/DAISGram/blob/main/images/greenscreen/gs_2_bkg.bmp) | ![GREENSCREEN](https://github.com/Ciccooz/DAISGram/blob/main/results/greenscreen/dais_matrix.bmp)

 ## Histogram equalization
 Original Image | Equalization
------------ | -------------
![HILL](https://github.com/Ciccooz/DAISGram/blob/main/images/equalize/hill.bmp) | ![EQUALIZE](https://github.com/Ciccooz/DAISGram/blob/main/results/hill_equalize.bmp)