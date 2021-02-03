#pragma once

#include <maya/MPxNode.h>
#include <math.h>
#include <iostream>
#include <maya/MMatrix.h> 
#include <maya/MBoundingBox.h>
#include <maya/MFloatPointArray.h>
#include <maya/M3dView.h>

#include <maya/MFnNumericAttribute.h>

#include <GL/glew.h>


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

	virtual void		draw(M3dView&, const MDagPath&, M3dView::DisplayStyle, M3dView::DisplayStatus);
	virtual bool        isBounded() const;
	virtual bool        isTransparent() const;
	virtual MBoundingBox boundingBox() const;
	void drawDisc(float radius, int divisions, bool filled);

	static  MTypeId      id;

	static  MObject		aOutValue;
	static  MObject		aMatrixGL;
	static  MObject		aInValueX;
	static  MObject		aInValueZ;
	static  MObject		aMagnitude;
	static  MObject		aGeoPositionX;
	static  MObject		aGeoPositionZ;
	static  MObject		aVariance;
};

#endif