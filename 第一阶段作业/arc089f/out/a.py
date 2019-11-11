import os
for i in range(5, 112):
    os.rename("1_%03d.txt"%i, "a"+str(i)+".out")
