import os

def getWorkingDirs(testdir):
    dirs = [t for t in os.listdir(testdir) if t != '.DS_Store']
    work_dirs = []
    for directory in dirs:
        work_dirs.append((testdir +"/"+ directory))
    return work_dirs

def removeControlM(directory):
    files = [t for t in os.listdir(directory) if t != '.DS_Store']
    for file in files:
        cmd = "dos2unix " + directory + "/"+ file
        os.system(cmd)
    return

def changeEXTTo(directory, new_ext, number_char_ext):
    files = [t for t in os.listdir(directory) if t != '.DS_Store']
    for file in files:
        file = file[:-number_char_ext] + new_ext
        cmd = "dos2unix " + file 
        os.system(cmd)
    return

if __name__ == "__main__":
    probs_dir = "/pbr1"
    maps_dir = "/maps"
    results_dir = "/results"
    working_dirs = getWorkingDirs((os.getcwd() + "/test1"))
    for directory in working_dirs:
        # changeEXTTo(directory+probs_dir, "txt" ,5)
        removeControlM(directory+probs_dir)
        # changeEXTTo(directory+probs_dir, "prbs1" ,3)

        # changeEXTTo(directory+maps_dir, "txt" ,4)
        removeControlM(directory+maps_dir)
        # changeEXTTo(directory+maps_dir, "maps" ,3)

        # changeEXTTo(directory+results_dir, "txt" ,7)
        removeControlM(directory+results_dir)
        # changeEXTTo(directory+results_dir, "queries" ,3)
