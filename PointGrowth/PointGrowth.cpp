#include "PointGrowth.h"

MTypeId     PointGrowthNode::id(0x00000451);
MObject		PointGrowthNode::aOutValue;
//MObject		PointGrowthNode::aPointGL;
MObject		PointGrowthNode::aMatrixGL;
MObject		PointGrowthNode::aInValueX;
MObject		PointGrowthNode::aInValueZ;
MObject		PointGrowthNode::aMagnitude;
MObject		PointGrowthNode::aGeoPositionX;
MObject		PointGrowthNode::aGeoPositionZ;
MObject		PointGrowthNode::aVariance;

PointGrowthNode::PointGrowthNode(){
}

PointGrowthNode::~PointGrowthNode(){
}

void* PointGrowthNode::creator(){
	return new PointGrowthNode();
}

MStatus PointGrowthNode::initialize()
{
	MStatus status;
	MFnNumericAttribute nAttr;

	/// INITIALIZE ATTRIBUTES ///
	/// OUTPUT VALUES ///

	aOutValue = nAttr.create("outValue", "outValue", MFnNumericData::kFloat);
	nAttr.setWritable(false);
	nAttr.setStorable(false);
	addAttribute(aOutValue);

	/// INPUT POSITIONS

	aInValueX = nAttr.create("inValueX", "inValueX", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aInValueX);
	attributeAffects(aInValueX, aOutValue);

	aInValueZ = nAttr.create("inValueZ", "inValueZ", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aInValueZ);
	attributeAffects(aInValueZ, aOutValue);

	aMatrixGL = nAttr.create("inMatrixGL", "inMatrixGL", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aInValueZ);
	attributeAffects(aInValueZ, aOutValue);
	
	/// AFFECTED GEO POSITIONS
	
	aGeoPositionX = nAttr.create("geoPositionX", "geoPositionX", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aGeoPositionX);
	attributeAffects(aGeoPositionX, aOutValue);

	aGeoPositionZ = nAttr.create("geoPositionZ", "geoPositionZ", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aGeoPositionZ);
	attributeAffects(aGeoPositionZ, aOutValue);
	
	/// MAGNITUDE + VARIANCE

	aMagnitude = nAttr.create("magnitude", "magnitude", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aMagnitude);
	attributeAffects(aMagnitude, aOutValue);

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

	/// OGL ///
	MMatrix inputMatrix = data.inputValue(aMatrixGL).asMatrix();
	MVector inputPoint = MTransformationMatrix(inputMatrix).getTranslation(MSpace::kPostTransform);

	 
	float inputValueX = data.inputValue(aInValueX, &status).asFloat();
	float inputValueZ = data.inputValue(aInValueZ, &status).asFloat();

	float geoPositionX = data.inputValue(aGeoPositionX, &status).asFloat();
	float geoPositionZ = data.inputValue(aGeoPositionZ, &status).asFloat();

	float magnitude = data.inputValue(aMagnitude, &status).asFloat();
	float variance = data.inputValue(aVariance, &status).asFloat();
	if (variance <= 0.0f){
		variance = 0.001f;
	}

	float xSqr = (inputValueX - geoPositionX) * (inputValueX - geoPositionX);
	float zSqr = (inputValueZ - geoPositionZ) * (inputValueZ - geoPositionZ);
	float distance = (xSqr + zSqr);

	float length = (sqrt(distance));
	if (length == 0.0f) {
		length = 0.001f;
	}

	float output = (magnitude * exp(-(length*length) / (2.0f * (variance))));

	MDataHandle hOutput = data.outputValue(aOutValue, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	hOutput.setFloat(output);
	hOutput.setClean();
	data.setClean(plug);

	return MS::kSuccess;
}

/// --- OPENGL --- ///

void PointGrowthNode::drawDisc(float radius, int divisions, bool filled)
{
	int renderState = filled ? GL_POLYGON : GL_LINE_LOOP;
	float degreesPerDiv = 360.0f / divisions;
	float radiansPerDiv = degreesPerDiv * 0.01745327778f;
	MFloatPointArray points(divisions);
	for (int i = 0; i < divisions; i++)
	{
		float angle = i * radiansPerDiv;
		float x = cos(angle) * radius;
		float z = sin(angle) * radius;
		points[i].x = x;
		points[i].z = z;
	}

	glBegin(renderState);
	for (int i = 0; i < divisions; i++)
	{
		glVertex3f(points[i].x, 0.0f, points[i].z);
	}
	glEnd();
}


bool PointGrowthNode::isBounded() const
{
	return true;
}


bool PointGrowthNode::isTransparent() const
{
	return true;
}


MBoundingBox PointGrowthNode::boundingBox() const
{
	MBoundingBox bbox;
	return bbox;
}
