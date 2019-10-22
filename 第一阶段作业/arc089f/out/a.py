import os
for i in range(1, 4):
    os.rename("0_%03d.txt"%i, str(i)+".out")
