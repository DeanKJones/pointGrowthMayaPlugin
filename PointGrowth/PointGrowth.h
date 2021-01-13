#pragma once

#include <maya/MPxNode.h>
#include <math.h>
#include <iostream>
#include <maya/MMatrix.h> 
#include <maya/MVector.h>

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnGeometryFilter.h>


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

	//const   MStatus		getOutputGeometry(MObjectArray& geomList);
	//MPlugArray;

	static  MTypeId      id;

	static  MObject		aOutValue;
	static  MObject		aInValue;
	static  MObject		aMagnitude;
	static  MObject		aGeoPosition;
	static  MObject		aVariance;
};

#endif