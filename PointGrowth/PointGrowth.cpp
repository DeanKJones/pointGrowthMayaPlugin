#include "PointGrowth.h"
#include <math.h>

MTypeId     PointGrowthNode::id(0x00000451);
MObject		PointGrowthNode::aOutValue;
MObject		PointGrowthNode::aInValue;
MObject		PointGrowthNode::aMagnitude;
MObject		PointGrowthNode::aGeoPosition;
MObject		PointGrowthNode::aVariance;

PointGrowthNode::PointGrowthNode()
{
}

PointGrowthNode::~PointGrowthNode()
{
}

void* PointGrowthNode::creator()
{
	return new PointGrowthNode();
}

MStatus PointGrowthNode::initialize()
{

	/// --- Create 3Float inputs --- ///
	/*
	  MFnNumericData numericData;
      MObject obj = numericData.create( MFnNumericData::k3Float, &returnStatus );
      CHECK_MSTATUS( returnStatus );

      returnStatus = numericData.setData( (float)2.5, (float)8.7, (float)2.3345 );
      CHECK_MSTATUS( returnStatus );

      outputData.set( obj );
	  */

	MStatus status;
	MFnNumericAttribute nAttr;
	MFnMatrixAttribute mAttr;

	aOutValue = nAttr.create("outValue", "outValue", MFnNumericData::kFloat);
	nAttr.setWritable(false);
	nAttr.setStorable(false);
	addAttribute(aOutValue);

	aInValue = mAttr.create("inValue", "inValue");
	mAttr.setKeyable(true);
	addAttribute(aInValue);
	attributeAffects(aInValue, aOutValue);

	aMagnitude = nAttr.create("magnitude", "magnitude", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aMagnitude);
	attributeAffects(aMagnitude, aOutValue);

	aGeoPosition = mAttr.create("geoPosition", "geoPosition");
	mAttr.setKeyable(true);
	mAttr.isWorldSpace();
	addAttribute(aGeoPosition);
	attributeAffects(aGeoPosition, aOutValue);

	aVariance = nAttr.create("variance", "variance", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aVariance);
	attributeAffects(aVariance, aOutValue);

	return MS::kSuccess;
}

MStatus PointGrowthNode::compute(const MPlug& plug, MDataBlock& data)
{
	MStatus status;

	if (plug != aOutValue)
	{
		return MS::kUnknownParameter;
	}

	MMatrix inputValue = data.inputValue(aInValue, &status).asMatrix();
	MVector inputPoint = MTransformationMatrix(inputValue).getTranslation(MSpace::kPostTransform);

	MMatrix geoPosition = data.inputValue(aGeoPosition, &status).asMatrix();
	MVector geoPoint = MTransformationMatrix(geoPosition).getTranslation(MSpace::kPostTransform);

	float magnitude = data.inputValue(aMagnitude, &status).asFloat();
	float variance = data.inputValue(aVariance, &status).asFloat();
	if (variance <= 0.0f)
	{
		variance = 0.001f;
	}

	/*
	floatMagnitude = matrixInput - matrixMean
	if magnitude = 0
		make positive 1
	else 
		make 0 
	*/

	//MStatus getData(inputValue);

	float distance = inputValue - mean;
	//float magnitude = sqrt(distance)
	float xMinusB = (inputValue) - (mean);
	float output = magnitude * exp(-(xMinusB * xMinusB) / (2.0f * variance));

	std::cout << "The distance is " << distance << "\n";
	std::cout << "The inputValues are " << inputValue << "\n";
	std::cout << "The mean values are " << mean << "\n";

	MDataHandle hOutput = data.outputValue(aOutValue, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	hOutput.setFloat(output);
	hOutput.setClean();
	data.setClean(plug);

	return MS::kSuccess;
}
