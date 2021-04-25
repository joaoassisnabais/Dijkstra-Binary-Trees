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

if __name__ == "__main__":
    probs_dir = "/pbr1"
    maps_dir = "/maps"
    results_dir = "/results"
    working_dirs = getWorkingDirs((os.getcwd() + "/test1"))
    for directory in working_dirs:
        removeControlM(directory+probs_dir)
        removeControlM(directory+maps_dir)
        removeControlM(directory+results_dir)