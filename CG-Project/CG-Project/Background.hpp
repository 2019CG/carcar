//
//  Background.hpp
//  CGProject
//
//  Created by LI Hongyi on 2019/12/15.
//  Copyright © 2019 LI Hongyi. All rights reserved.
//

#ifndef Background_hpp
#define Background_hpp

#include <gl/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <cmath>

#pragma warning(suppress : 4996)
#define BITMAP_ID 0x4D42
void Binit();
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader);
void texload(int i, char* filename);
void CreateBackground(void);

#endif /* Background_hpp */


