import os
for i in range(4, 112):
    os.rename("1_%03d.txt"%i, str(i)+".in")
