#pragma once

#include <maya/MPxNode.h>
#include <math.h>
#include <iostream>
#include <maya/MMatrix.h> 

#include <maya/MFnNumericAttribute.h>




#ifndef POINTGROWTHNODE_H
#define POINTGROWTHNODE_H

class PointGrowthNode : public MPxNode
{
public:
						PointGrowthNode();
	virtual				~PointGrowthNode();
	static void*		creator();

	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);
	static  MStatus	    initialize();

	static  MTypeId      id;

	static  MObject		aOutValue;
	static  MObject		aInValueX;
	static  MObject		aInValueY;
	static  MObject		aInValueZ;
	static  MObject		aMagnitude;
	static  MObject		aGeoPositionX;
	static  MObject		aGeoPositionY;
	static  MObject		aGeoPositionZ;
	static  MObject		aVariance;
};

#endif