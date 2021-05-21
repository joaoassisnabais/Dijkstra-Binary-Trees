import os
from stringcolor import *
from subprocess import call

def make():
    call(['rm', 'aedmaps'])
    call('make')
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

def removeRoutes(mapsdir):
    os.chdir(mapsdir)
    call("rm *.routes", shell=True)
    return

def solveFor(work_dir, my_prog, probs_dir, maps_dir, res_dir, main_dir):
    pbs = getFilenamesInDir((work_dir+probs_dir))
    maps = getFilenamesInDir((work_dir+maps_dir))
    mode = "-aa"
    
    for pb in pbs:
        for mapa in maps:
            print(cs("Problem: ", "orchid")+ pb, "\n" + cs("Map: ", "orchid") + mapa)
            program = f'./{my_prog}' 
            args = f'{mode} {work_dir+probs_dir}/{pb} {work_dir+maps_dir}/{mapa}'
            print(cs("Arguments:","orchid"), args)

            cmd = f'{program} {args}'
            call(cmd , shell=True)
            tmp_res = mapa[:-4] + 'routes'
            diff_command = f'sdiff {work_dir+maps_dir}/{tmp_res} {work_dir+res_dir}/{tmp_res} | egrep -n "\||>|<"'
            
            print(cs("Diff Command: ", "aqua") + diff_command)
            call(diff_command, shell=True)
            print("\n")
            
    return

def solveValgrind (work_dir, my_prog, probs_dir, maps_dir, res_dir, main_dir):
    pbs = getFilenamesInDir((work_dir+probs_dir))
    maps = getFilenamesInDir((work_dir+maps_dir))
    mode = "-" + work_dir[-3:]
    
    for pb in pbs:
        for mapa in maps:
            print(cs("Problem: ", "orchid")+ pb, "\n" + cs("Map: ", "orchid") + mapa)
            program = f'./{my_prog}' 
            args = f'{mode} {work_dir+probs_dir}/{pb} {work_dir+maps_dir}/{mapa}'
            print(cs("Arguments:","orchid"), args)

            cmd = f'valgrind --leak-check=full {program} {args}'
            print(cs("Valgrind log:","aqua"))
            call(cmd , shell=True)
            print("\n")
            
    return

if __name__ == "__main__":
    make()
    main_dir = os.getcwd()
    my_program = "aedmaps"
    probs_dir = "/prbs"
    maps_dir = "/maps"
    results_dir = "/routes"
    test_dir = "/test2"
    working_dirs = getWorkingDirs((os.getcwd() + test_dir))
    working_dirs_names = getFilenamesInDir(main_dir + test_dir)
    
    for working_dir in working_dirs:
        removeRoutes(working_dir+maps_dir)
        os.chdir(main_dir)
        print(cs("Solving probs for files in: ", "orchid")+ working_dir)
        solveFor(working_dir, my_program, probs_dir, maps_dir, results_dir, main_dir)
        #solveValgrind(working_dir, my_program, probs_dir, maps_dir, results_dir, main_dir)
        removeRoutes(working_dir+maps_dir)

    os.chdir(main_dir)
    call(['make', 'clean'])
    call(['rm', 'aedmaps'])
