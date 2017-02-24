import os

os.chdir(r"D:\Users\Zvone\Projects\Code Plagiarism Detector\TestPodaci\3217")
listFiles = os.listdir(os.curdir)
filesLength = [ (0, "Empty") ]

for fileName in listFiles:
    f = open (fileName, mode='r')
    f.seek(0, 2)
    filesLength.append((f.tell(), fileName) )

filesLength.sort()

for tuple in filesLength:
    print tuple
    
x = input("Press any key")