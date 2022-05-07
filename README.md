# image-filter
The program only runs on 24-bit bitmap (.bmp) image files. There are 5 options to use; blurring the image, grayscaling, reflecting the image horizontally, finding edges with sobel and finally finding edges with pixel value difference. Each function has their own respective flags to use with terminal to define which filter is going to be used. The flags are (in order) "-b, -g, -r, -e, -c". After making filter.c file with 'Makefile' run the file with terminal as shown in the example below:
./filter -[flag of function to use] [inputimage.bmp] [outputimage.bmp]
