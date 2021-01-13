import maya.cmds as cmds
import pymel.core as pm

controller = pm.polySphere(radius = geoSize, name = 'controller')

#Control Values
geoSize = 0.2
magnitude = -0.5
variance = 0.5
amountOfCubes = 20
x = (-(geoSize * amountOfCubes)/2) - 0.1
z = 0

for i in range(amountOfCubes):
    newCube = pm.polyCube(depth = geoSize, height = geoSize, width = geoSize, name = 'polycube')
    x += geoSize
    z += 0
    cmds.move(x, 0, z)

    node = pm.createNode('pointGrowth')
    pm.connectAttr('controller.translateX', 'pointGrowth*.inValueX')
    pm.connectAttr('pointGrowth*.outValue', 'polycube*.translateY')
    pm.connectAttr(newCube[0] + '.center', 'pointGrowth*.mean')
    
    #Set Param
    for nodes in node:
        pm.setAttr(node + '.magnitude', magnitude)
        pm.setAttr(node + '.variance', variance)
        pm.setAttr(node + '.inValueZ', 2)
