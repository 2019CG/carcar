//
//  Background.cpp
//  CGProject
//
//  Created by LI Hongyi on 2019/12/15.
//  Copyright © 2019 LI Hongyi. All rights reserved.
//
#pragma warning(suppress : 4996)
#include "Background.hpp"


unsigned int texture[4];

unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;	// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
	unsigned char* bitmapImage;		// bitmap图像数据
	int	imageIdx = 0;		// 图像位置索引
	unsigned char	tempRGB;	// 交换变量

								// 以“二进制+读”模式打开文件filename 
	//filePtr = fopen(filename, "rb");
	errno_t err;
	err = fopen_s(&filePtr, filename, "r");
	if (filePtr == NULL) return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	else
	{
		fprintf(stderr, "Loading Successfully\n");
	}

	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0;
		imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}

void texload(int i, char* filename)
{

	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
	unsigned char* bitmapData;                                       // 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0, 	    //mipmap层次(通常为，表示最上层) 
		GL_RGB,	//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2 
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2 
		0, //边框(0=无边框, 1=有边框) 
		GL_RGB,	//bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的类型
		bitmapData);	//bitmap数据指针  
}

void Binit()
{
	/*Color Indentify (Can be modified)*/
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glGenTextures(3, texture);
	
	/*The path here should be changed to yours.*/
	char text1[50] = "Crack.bmp";
	glEnable(GL_TEXTURE_2D);
	texload(0, text1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CreateBackground(void) {

	//Color of background
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/*草地*/
	int dir[4][2] = { {1,1},{1,0},{0,0},{0,1} };
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	int Step = 5;
	
	for (size_t i = 0; i < 6800/Step; i++)
	{
		for (size_t j = 0; j < 3800/Step; j++)
		{
			glPushMatrix();
			glBegin(GL_POLYGON);
			glColor3f(0.13, 0.54, 0.13);
			int X = -3400 + Step * i;
			int Y = -1900 + Step * j;
			glTexCoord2iv(dir[2]);
			glVertex3d(X, Y, 0);
			glTexCoord2iv(dir[0]);
			glVertex3d(X + Step, Y, 0);
			glTexCoord2iv(dir[1]);
			glVertex3d(X + Step, Y + Step, 0);
			glTexCoord2iv(dir[3]);
			glVertex3d(X, Y + Step, 0);
			glEnd();
			glPopMatrix();
		}

	}
	
	
	glDisable(GL_TEXTURE_2D);

	/*赛道*/
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3d(-1100, 1200, 0);
	glVertex3d(2400, 1200, 0);
	glVertex3d(2400, 700, 0);
	glVertex3d(-1100, 700, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-1800, -1400, 0);
	glVertex3d(2400, -1400, 0);
	glVertex3d(2400, -900, 0);
	glVertex3d(-1800, -900, 0);
	glEnd();

	/*模拟的车辆*/
	/*
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3d(0, 1050, 0);
	glVertex3d(400, 1050, 0);
	glVertex3d(400, 850, 0);
	glVertex3d(0, 850, 0);
	glEnd();*/

	/*道路（转盘）*/
	float PI = 3.1425;
	float R = 1200;
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	for (int i = 0; i < 100; i++)
	{
		glVertex3f(-2100 + R * cos(2 * PI * i / 100), 600 + R * sin(2 * PI * i / 100), 0);   //定义顶点
	}
	glEnd();

	R = 600;
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		glVertex3f(-2100 + R * cos(2 * PI * i / 100), 600 + R * sin(2 * PI * i / 100), 0);   //定义顶点
	}
	glEnd();

	/*弯道1*/
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	for (int i = 0; i <= 50; i++)
	{
		glVertex3f(2400 + 900 * cos(-2 * PI * i / 100 + 1.57), -100 + 1300 * sin(-2 * PI * i / 100 + 1.57), 0);   //定义顶点
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.13, 0.54, 0.13);
	for (int i = 0; i <= 50; i++)
	{
		glVertex3f(2400 + 300 * cos(2 * PI * i / 100 - 1.57), -100 + 800 * sin(2 * PI * i / 100 - 1.57), 0);   //定义顶点
	}
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (size_t i = 0; i < 600/Step; i++)
	{
		for (size_t j = 0; j < 1600/Step; j++)
		{
			int X = 2100 + Step * i;
			int Y = -900 + Step * j;
			if ((X - 2400) * (X - 2400) * 1.0 / 90000 + (Y + 100) * (Y + 100) * 1.0 / 640000 < 1)
			{
				glPushMatrix();
				glBegin(GL_POLYGON);
				glColor3f(0.13, 0.54, 0.13);
				glTexCoord2iv(dir[2]);
				glVertex3d(X, Y, 0);
				glTexCoord2iv(dir[0]);
				glVertex3d(X + Step, Y, 0);
				glTexCoord2iv(dir[1]);
				glVertex3d(X + Step, Y + Step, 0);
				glTexCoord2iv(dir[3]);
				glVertex3d(X, Y + Step, 0);
				glEnd();
				glPopMatrix();
			}
			
		}
	}
	glDisable(GL_TEXTURE_2D);

	/*弯道2*/
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3d(-1800, -900, 0);
	for (int i = 0; i <= 25; i++)
	{
		glVertex3f(-1800 + 500 * cos(2 * PI * i / 100 + PI), -900 + 500 * sin(2 * PI * i / 100 + PI), 0);   //定义顶点
	}
	glEnd();

	/*连接直道2*/
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3d(-1800, -900, 0);
	glVertex3d(-2300, -900, 0);
	glVertex3d(-2300, 0, 0);
	glVertex3d(-1800, 0, 0);
	glEnd();

}
