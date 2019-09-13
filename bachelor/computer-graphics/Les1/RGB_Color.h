// RGB_Color.h: interface for the RGB_Color class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGB_COLOR_H__AF5C9450_480F_4D16_9CB0_C4563B547D70__INCLUDED_)
#define AFX_RGB_COLOR_H__AF5C9450_480F_4D16_9CB0_C4563B547D70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RGB_Color  
{
public:
	RGB_Color();
	RGB_Color(float R, float G, float B);
	virtual ~RGB_Color();

public:
	void RespectBoundaries();
	void SetRGB(float R, float G, float B);
	float r;
	float g;
	float b;
};

#endif // !defined(AFX_RGB_COLOR_H__AF5C9450_480F_4D16_9CB0_C4563B547D70__INCLUDED_)
