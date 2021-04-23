import os

def make():
    os.system("make")
    return

def getFilenamesInDir(dir):
    return os.listdir(dir)

def getWorkingDirs(testdir):
    dirs = os.listdir(testdir)
    work_dirs = []
    for dir in dirs:
        work_dirs.append((testdir + dir))
    return work_dirs

def solveFor(working_dir, my_program, probs_dir, maps_dir, results_dir):
    os.chdir(working_dir)
    os.system("rm -rf tmp")
    os.mkdir("tmp")
    os.system("mv " + my_program+" "+"tmp")
    
    pbs = getFilenamesInDir((working_dir+probs_dir))
    maps = getFilenamesInDir((working_dir+maps_dir))
    result_dir = working_dir + results_dir
    mode = "-" + working_dir[:-3]
    
    for pb in pbs:
        for mapa in maps:
            print("Problem " + pb + " Map " + mapa)
            os.system("./"+my_program +" "+ mode+ " " + pb + " " + mapa)
            tmp_res = pb[:-5] + 'queries'
            diff_command = "sdiff " + tmp_res + " " + result_dir +tmp_res+ ' | egrep -n "\||>|<"'
            print("Diff command: " + diff_command)
            os.system(diff_command)
            
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
        print("Solving probs in dir "+ working_dir)
        os.system(("mv "+my_program+" "+working_dir))
        solveFor(working_dir, my_program, probs_dir, maps_dir, results_dir)
        os.system(("mv " + my_program + " " + main_dir))

    os.system("make clean")
