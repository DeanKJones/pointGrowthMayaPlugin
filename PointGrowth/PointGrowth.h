#pragma once

#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <math.h>

#ifndef POINTGROWTHNODE_H
#define POINTGROWTHNODE_H

class PointGrowthNode : public MPxNode
{
public:
	PointGrowthNode();
	virtual				~PointGrowthNode();
	static void* creator();

	virtual MStatus		compute(const MPlug& plug, MDataBlock& data);
	static MStatus	    initialize();

	static MTypeId      id;

	static MObject		aOutValue;
	static MObject		aInValue;
	static MObject		aMagnitude;
	static MObject		aMean;
	static MObject		aVariance;
};

#endif