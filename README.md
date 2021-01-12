"pointGrowthMayaPlugin" 

// INSTALL PLUGIN IN MAYA //

Write in the MEL script editor:

///
createNode pointGrowth
///

or a preconnected node settup in the Python script editor:

///
import maya.cmds as cmds
import pymel.core as pm

controller = pm.polySphere(radius = 0.2, name = 'controller')
cubeSize = 0.2
magnitude = 1
variance = 0.35

for i in range(5):
    #moveCube = (1, 0, 0)
    newCube = pm.polyCube(depth = cubeSize, height = cubeSize, width = cubeSize, name = 'polycube')
    #newCube.translate.set(moveCube)
    node = pm.createNode('pointGrowth')
    pm.connectAttr('controller.translateX', 'pointGrowth*.inValueX')
    pm.connectAttr('pointGrowth*.outValue', 'polycube*.translateY')
    pm.connectAttr('polycube*.center', 'pointGrowth*.mean')
    
    #Set Param
    pm.setAttr('pointGrowth*.magnitude', magnitude)
    pm.setAttr('pointGrowth*.variance', variance)
    pm.setAttr('pointGrowth*.inValueZ', 1)
///
