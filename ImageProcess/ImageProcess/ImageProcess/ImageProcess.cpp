#include <bitset>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>
//#include <WinGDI.h>

#define numRows 30
#define numCols 100


//void BMPHeader(std::ostream &out, int rows, int cols){
//	
//	DWORD dwSizeInBytes = rows*cols*3; // when your matrix contains RGB data)
//
//    // fill in the headers
//    BITMAPFILEHEADER bmfh;
//	bmfh.bfType = 0x4D42; // 'BM'
//	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSizeInBytes;
//	bmfh.bfReserved1 = 0;
//	bmfh.bfReserved2 = 0;
//	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//
//	BITMAPINFOHEADER bmih;
//	bmih.biSize = sizeof(BITMAPINFOHEADER);
//	bmih.biWidth = cols;
//	bmih.biHeight = rows;
//	bmih.biPlanes = 1;
//	bmih.biBitCount = 24;
//	bmih.biCompression = BI_RGB;
//	bmih.biSizeImage = 0;
//	bmih.biXPelsPerMeter = 0;
//	bmih.biYPelsPerMeter = 0;
//	bmih.biClrUsed = 0;
//	bmih.biClrImportant = 0;
//
//	out.write(&bmfh, sizeof(bmfh));
//    out.write(&bmih, sizeof(bmih));
//}

struct Pixel{
	char r;
	char g;
	char b;
	std::string str(){
		std::stringstream ss;
		//ss<<"B"<<std::bitset<8>(r)<<",B"<<std::bitset<8>(g)<<",B"<<std::bitset<8>(b);
		/*uint8_t red = r;
		uint8_t green = g;
		uint8_t blue = b;
		ss<<red<<","<<green<<","<<blue;
		return ss.str();
		*/
		char S[12];
		int n = sprintf(S,"%d,%d,%d",(unsigned char)r,(unsigned char)g,(unsigned char)b);
		std::string s(S);
		return s;
	}
};
/*
Convert from row-major order to column major order
Since our pov sphere requires column major order format
*/
Pixel* row2col(Pixel* image, int rows, int cols){
	Pixel* newImage = (Pixel*) malloc(rows*cols*sizeof(Pixel));
	for(int i = 0 ; i<rows;i++){
		for(int j = 0; j<cols; j++){
			//std::cout<<"i "<<i<<" j "<<j<<" j*cols+i "<<(j*cols+i)<<" j+i*rows"<<(j+i*rows)<<std::endl;
			newImage[j*rows+i].r = image[j+i*cols].r;
			newImage[j*rows+i].g = image[j+i*cols].g;
			newImage[j*rows+i].b = image[j+i*cols].b;
		}
	}
	return newImage;
	//image = newImage;
}

int main(){
	int numPixels = numRows*numCols;
	int numBytes = numRows*numCols*3;
	int header = 54;  //end of bmp header

	std::ifstream file_in("smily7.bmp",std::ifstream::binary);
	std::cout<<"Found file"<<std::endl;
	std::ofstream out("test.h",std::ifstream::binary);
	char* bmpfile = (char*)malloc((numBytes+header)*sizeof(char));
	//char* image = (char*)malloc(numBytes*sizeof(char));
	
	file_in.read(bmpfile,numBytes);
	file_in.close();
	//Fill in pixel vector
	Pixel* image = (Pixel*) malloc(numPixels*sizeof(Pixel));
	int byteCount = header;
	for(int i = 0 ; i<numPixels; i++){
		image[i].r = bmpfile[byteCount++];
    	image[i].g = bmpfile[byteCount++];
    	image[i].b = bmpfile[byteCount++];
	}

	/*for(int i = 0 ; i<numBytes ; i++){
		out<<image[i];
	}
*/
	//Write header in row major order format
	//out<<"prog_uint8_t Image["<<numRows<<"]["<<numCols<<"] PROGMEM = {"<<std::endl;
	//for(int i = 0; i<numRows; i++){
	//	out<<"{";
	//	for(int j = 0; j<numCols-1; j++){
	//		out<<"B"<<image[i*numCols+j].str()<<",";
	//	}
	//	out<<"B"<<image[i*numCols+(numCols-1)].str()<<"},"<<std::endl;
	//}
	//out<<"};"<<std::endl;
	//out.close();

	//Write header in column major order format
	image = row2col(image,numRows,numCols);
	int rows = numCols;
	int cols = numRows;
	out<<"#include <avr/pgmspace.h>"<<std::endl;
	out<<"prog_uint8_t Image["<<rows<<"]["<<cols*3<<"] PROGMEM = {"<<std::endl;
	//Crashes at element 6700
	std::cout<<"rows: "<<rows<<" cols: "<<cols<<std::endl;
	for(int i = 0 ; i <rows ; i++){
		out<<"{";
		for(int j = 0 ; j<cols-1 ;j++){
			//std::cout<<(j+i*rows)<<std::endl;
			//out<<"B"<<image[j+i*cols].r<<",";
			//out<<"B"<<image[j+i*cols].g<<",";
			//out<<"B"<<image[j+i*cols].b<<",";
			out<<image[j+i*cols].str()<<",";
			
		}
		if(i==rows-1){
			out<<image[(cols-1)+i*cols].str()<<"}"<<std::endl;
		}else{
			out<<image[(cols-1)+i*cols].str()<<"},"<<std::endl;
		}
	}
	out<<"};"<<std::endl;
	out.close();
	
	free(image);
	
	return 0;
}