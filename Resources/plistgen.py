import sys

n = int(sys.argv[1])
sizex= float(sys.argv[2])
sizey= sizex;
if len(sys.argv)>3: sizey = sys.argv[3]

for i in xrange(n):
  print "\t\t<key>Sq0"+str(i)+".png</key>"
  print "\t\t\t<dict>"
  print "\t\t\t\t<key>frame</key>"
  print "\t\t\t\t<string>{{"+str(int(i*sizex))+ ",0},{"+str(int(sizex))+","+str(sizey)+"}}</string>"
  print "\t\t\t\t<key>offset</key>"
  print "\t\t\t\t<string>{0,0}</string>"
  print "\t\t\t\t<key>rotated</key>"
  print "\t\t\t\t<false/>"
  print "\t\t\t\t<key>sourceColorRect</key>"
  print "\t\t\t\t<string>{{0,0},{"+str(int(sizex))+","+str(sizey)+"}}</string>"
  print "\t\t\t\t<key>sourceSize</key>"
  print "\t\t\t\t<string>{"+str(int(sizex))+","+str(sizey)+"}}</string>"
  print "\t\t\t</dict>"
