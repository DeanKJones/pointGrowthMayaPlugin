#include "PointGrowth.h"
#include <maya/MFnPlugin.h>

/// Init Plugin ///
///////////////////////////////////////////////////////

MStatus initializePlugin(MObject obj)
{
    MStatus   status;
    MFnPlugin plugin(obj, "Dean Jones", "1.0", "Any");

    status = plugin.registerNode("pointGrowth",
        PointGrowthNode::id,
        PointGrowthNode::creator,
        PointGrowthNode::initialize);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
    MStatus   status;
    MFnPlugin plugin(obj);

    status = plugin.deregisterNode(PointGrowthNode::id);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    return MS::kSuccess;
}