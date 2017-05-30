#!/bin/python
import os
import stat
import time

INTERVAL = 1

class Filestat:
    def __init__(self, n, s):
        self.name = n
        self.stat = s
        self.count = 0
        self.lasttime = time.time();
    
    def checkdiff(self, other):#update time and check for changes
        newtime = time.time()
        if(self.stat != other.stat):
            if(newtime - other.lasttime < INTERVAL):
                self.count += 1
                if(self.count >= 3):
                    print("WARNING: ", self.name, " may be compromised");
                
            
        else:
            count = 0
        self.stat = other.stat
        self.lasttime = newtime

filelist = {}#initialize dictionary
for fn in os.listdir("."):
    filelist[fn] = Filestat(fn, os.stat(fn))
        
#st = os.stat('.')

while True:
    for fn in os.listdir("."):
        if fn in filelist:
            filelist[fn].checkdiff(Filestat(fn, os.stat(fn)))
            
    
    

