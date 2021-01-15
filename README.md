#INSTALL THE PLUGIN IN MAYA
#VISUALIZER FOR THE PYTHON SCRIPT EDITOR IN MAYA 

import maya.cmds as cmds
import pymel.core as pm

#Control Values
geoSize = 0.2
magnitude = -0.5
variance = 0.5
gridSize = 5
amountOfCubes = gridSize**2
#x = (-(geoSize * amountOfCubes)/2) - 0.1

controller = pm.polySphere(radius = geoSize, name = 'controller')

for i in range(amountOfCubes):
    #x += geoSize 
    lambdaNode = lambda x, y, z: '(%s, %s, %s)' % (x*0.2, y*0.0, z*0.2)
    coords = [[lambdaNode(x, y, z) for x in range(gridSize)] for z in range(gridSize)]
    #print(coords[0][0])
    
    for n in range(len(coords)):
        position = coords[0][1]
        #posX = position.index(0)
        print (position)
        #print (type(position))
        newCube = pm.polyCube(depth = geoSize, height = geoSize, width = geoSize, name = 'polycube')
        #print "\n".join(map("\t".join, coords))
        cmds.move(position)

    #node = pm.createNode('pointGrowth')
    #pm.connectAttr('controller.translateX', 'pointGrowth*.inValueX')
    #pm.connectAttr('pointGrowth*.outValue', 'polycube*.translateY')
    #pm.connectAttr(newCube[0] + '.center', 'pointGrowth*.mean')
    
    #Set Param
    #for nodes in node:
        #pm.setAttr(node + '.magnitude', magnitude)
        #pm.setAttr(node + '.variance', variance)
        #pm.setAttr(node + '.inValueZ', 2)
