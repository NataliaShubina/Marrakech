#pragma once

#define SAFEDEL(p) {if(p!=nullptr) delete p; p = nullptr;} 
#define SAFEDELARR(p) {if(p!=nullptr) delete[] p; p= nullptr;} 
#define SAFEDELARRUNKNOWNSIZE(p) {while(p){ delete p; p++;} p= nullptr;} 
#define SAFEDELARRSIZE(p, s) {for(int i=0; i<s; i++){ delete p[i];} delete [] p; p = nullptr;} 

#define NO_EFFECTS				0x00
#define BLACK_AND_WHITE			0x01
#define	BLUR					0x02
#define BLOOM					0x03
#define DEPTH_OF_FIELD			0X04
#define SEPIA					0X05
#define SOBEL_EDGE_DETECTION	0X06
#define SKY_BOX_TV				0x07

class Globals
{
public:
	static int screenWidth;
	static int screenHeight;
	static float m_time;
	static unsigned int currentEffect;
};