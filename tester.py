import os
from posix import listdir
from subprocess import call

def make():
    os.system("rm aedmaps")
    os.system("make")
    return

def getFilenamesInDir(directory):
    filenames = [t for t in os.listdir(directory) if t != '.DS_Store']
    return filenames

def getWorkingDirs(testdir):
    dirs = [t for t in os.listdir(testdir) if t != '.DS_Store']
    work_dirs = []
    for directory in dirs:
        work_dirs.append((testdir +"/"+ directory))
    return work_dirs

def removeQueries(mapsdir):
    os.chdir(mapsdir)
    os.system("rm *.queries")
    return

def solveFor(working_dir, my_program, probs_dir, maps_dir, results_dir, main_dir):
    pbs = getFilenamesInDir((working_dir+probs_dir))
    maps = getFilenamesInDir((working_dir+maps_dir))
    result_dir = working_dir + results_dir
    mode = "-" + working_dir[-3:]
    
    for pb in pbs:
        for mapa in maps:

            print("Problem: " + pb + " Map: " + mapa)
            cmd = "./"+my_program 
            args = mode+ " " + working_dir +"/"+probs_dir+"/"+pb + " " + working_dir +"/"+maps_dir+"/"+mapa
            print("Arguments:", args)

            os.system((cmd + " "+ args))
            tmp_res = mapa[:-4] + 'queries'
            diff_command = "sdiff " + working_dir + maps_dir +"/"+tmp_res + " " + result_dir+ "/" +tmp_res+ ' | egrep -n "\||>|<"'
            print("Diff command: " + diff_command)
            os.system(diff_command)
            print("\n")
            
    return

if __name__ == "__main__":
    make()
    main_dir = os.getcwd()
    my_program = "aedmaps"
    probs_dir = "/pbr1"
    maps_dir = "/maps"
    results_dir = "/results"
    working_dirs = getWorkingDirs((os.getcwd() + "/test1"))
    working_dirs_names = getFilenamesInDir(main_dir + "/test1")
    
    for working_dir in working_dirs:
        removeQueries(working_dir+maps_dir)
        os.chdir(main_dir)
        print("Solving probs for files in: "+ working_dir)
        solveFor(working_dir, my_program, probs_dir, maps_dir, results_dir, main_dir)
        removeQueries(working_dir+maps_dir)

    os.chdir(main_dir)
    os.system("make clean")
    os.system("rm aedmaps")