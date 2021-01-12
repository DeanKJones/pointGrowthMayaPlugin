#include "PointGrowth.h"

MTypeId     PointGrowthNode::id(0x00000451);
MObject		PointGrowthNode::aOutValue;
MObject		PointGrowthNode::aInValueX;
MObject		PointGrowthNode::aInValueZ;
MObject		PointGrowthNode::aMagnitude;
MObject		PointGrowthNode::aMean;
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

	aOutValue = nAttr.create("outValue", "outValue", MFnNumericData::kFloat);
	nAttr.setWritable(false);
	nAttr.setStorable(false);
	addAttribute(aOutValue);

	aInValueX = nAttr.create("inValueX", "inValueX", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aInValueX);
	attributeAffects(aInValueX, aOutValue);

	aInValueZ = nAttr.create("inValueZ", "inValueZ", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aInValueZ);
	attributeAffects(aInValueZ, aOutValue);

	aMagnitude = nAttr.create("magnitude", "magnitude", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aMagnitude);
	attributeAffects(aMagnitude, aOutValue);

	aMean = nAttr.create("mean", "mean", MFnNumericData::k3Float);
	nAttr.setKeyable(true);
	nAttr.isWorldSpace();
	MSpace::kObject;
	addAttribute(aMean);
	attributeAffects(aMean, aOutValue);

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

	/*
	space = OpenMaya.MSpace.kObject
		if worldSpace: space = OpenMaya.MSpace.kWorld
	*/

	float inputValueX = data.inputValue(aInValueX, &status).asFloat();
	float inputValueZ = data.inputValue(aInValueZ, &status).asFloat();
	float magnitude = data.inputValue(aMagnitude, &status).asFloat();
	float mean = data.inputValue(aMean, &status).asFloat();
	float variance = data.inputValue(aVariance, &status).asFloat();
	if (variance <= 0.0f)
	{
		variance = 0.001f;
	}

	float xMinusB = ((inputValueX * inputValueZ) / 2 ) - mean;
	float output = magnitude * exp(-(xMinusB * xMinusB) / (2.0f * variance));

	MDataHandle hOutput = data.outputValue(aOutValue, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	hOutput.setFloat(output);
	hOutput.setClean();
	data.setClean(plug);

	return MS::kSuccess;
}

/// --- go over plug array --- ///
/*
for (i = 0; i < arrayPlug.numElements(); i++)
{
	MPlug elementPlug = arrayPlug[i];
	unsigned int logicalIndex = elementPlug.logicalIndex();
	// ...
}
*/