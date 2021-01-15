Maya plugin to implement a guassian function based on the distance of two geometries

                                    ##################################
                                        INSTALLING PLUGIN IN MAYA
                                    ##################################

  Install the plugin in Maya:
      1. Open Maya
      2. Windows
      3. Settings/Preferences
      4. Plug-in manager
      5. Browse to the .mll location and select it

                                    ##################################
                                           RUNNING A TEST SETUP 
                                    ##################################
                                    
  import maya.cmds as cmds
  import pymel.core as pm

  #... Control Values
  rows = 15            #... Rows and Columns for the grid of cubes
  cols = rows          #
  geoSize = 0.2        #... Size of the sphere radius & cube dimensions
  magnitude = -0.5     #... magnitude is the height in the Y axis the cubes will move from the sphere
  variance = 0.5       #... variance is the falloff of the guassian function 

  gridSpacing = geoSize + (geoSize/2)

  #... create sphere controller
  controller = pm.polySphere(radius = geoSize, name = 'controller')

  #... Create grid 
  for i in range(rows):
      for j in range(cols):
          #... Create Cubes and set them in position
          newCube = pm.polyCube(depth = geoSize, height = geoSize, width = geoSize, name = 'polycube')
          cmds.move((i*gridSpacing), 0, (j*gridSpacing))

          #... Creating the plugin's node and connecting the plugs
          node = pm.createNode('pointGrowth')
          pm.connectAttr('controller.translateX', 'pointGrowth*.inValueX')
          pm.connectAttr('controller.translateZ', 'pointGrowth*.inValueZ')
          pm.connectAttr('pointGrowth*.outValue', 'polycube*.translateY')
          pm.connectAttr(newCube[0] + '.boundingBoxCenterX', 'pointGrowth*.geoPositionX')
          pm.connectAttr(newCube[0] + '.boundingBoxCenterZ', 'pointGrowth*.geoPositionZ')

          #... Set Parameters of the plugin
          for nodes in node:
              pm.setAttr(node + '.magnitude', magnitude)
              pm.setAttr(node + '.variance', variance)

