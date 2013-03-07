#include "Detector.hpp"
#include <stdio.h>

int main()
{
	const char * imagefile = "../tools/gray_img.raw";
	const char * cascadefile = "../haar_alt.txt";
	FILE *fin, *fout;
	unsigned int w, h;
	unsigned char* data;
	unsigned long i, size;
	
	fin = fopen(imagefile, "rb");
	assert(fin);
	fscanf(fin, "%d %d\n", &w, &h);
	printf("%d X %d\n", w, h);
	size = w*h;
	data = (unsigned char*)malloc(size*sizeof(unsigned char));
	fread(data, size, 1, fin);
	fclose(fin);
	
	Image image(w,h);
	for(i=0; i<size; i++)
	{
		image.data[i] = (unsigned int)data[i];
	}
	free(data);
	
	Detector detect(cascadefile);
	vector<Rectangle> obj = detect.getFaces(image, 1, 1.25f, 0.1f);
	fout = fopen("result.txt", "w");
	for(i=0; i<obj.size(); i++)
	{
		fprintf(fout, "%d %d %d %d\n", obj[i].x, obj[i].y, obj[i].width, obj[i].height);
		printf("%d %d %d %d\n", obj[i].x, obj[i].y, obj[i].width, obj[i].height);
	}
	fclose(fout);
	
	return 0;
}
