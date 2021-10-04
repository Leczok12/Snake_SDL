#pragma once
#include <fstream>
#include <iostream>
#include "UM_Bar.h"

using namespace std;

class AutoSet
{
public:
	AutoSet()
	{

	}
	~AutoSet()
	{

	}

	void Read(UM_Bar*volume, UM_Bar* speed, int &sound)
	{
		fstream AutoSet;
		AutoSet.open("AutoSet.log", ios::in);
		if (AutoSet.good() == false)
		{
			volume->setValue(100);
			speed->setValue(3);
			sound = 0;
		}
		else
		{
			int volumeR,speedR;
			AutoSet >> volumeR >> speedR >> sound;
			volume->setValue(volumeR);
			speed->setValue(speedR);
		};
		AutoSet.close();
	}

	void Write(int volume,int speed, int sound)
	{
		ofstream AutoSet;
		AutoSet.open("AutoSet.log", ofstream::out | ofstream::trunc);
		
		AutoSet << volume << endl << speed <<endl<<sound;
		AutoSet.close();
	}
private:
};