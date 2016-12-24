from os import listdir
from os.path import isfile
from os.path import splitext

flags = '-Wall -Werror'

def options(opt):
    opt.load('compiler_c')

def configure(cnf):
    cnf.load('compiler_c')

def build(bld):
    print("Compile shell...")
    bld.program(source='shell.c', 
                target='shell', 
                cflags=flags)
    if isfile('build/shell'):
        print("Move sh6.")
        bld.exec_command('cp build/shell shell')

    print("Compile cp...")
    bld.program(source='my_cp.c', 
                target='mycp', 
                cflags=flags)
    if isfile('build/mycp'):
        print("Move next.")
        bld.exec_command('cp build/mycp mycp')
        
    print("Compile ls...")
    bld.program(source='my_ls_v2.c', 
                target='myls', 
                cflags=flags)
    if isfile('build/myls'):
        print("Move next.")
        bld.exec_command('cp build/myls myls')
    
    print("Compile rm...")
    bld.program(source='my_rm.c', 
                target='myrm', 
                cflags=flags)
    if isfile('build/myrm'):
        print("Move next.")
        bld.exec_command('cp build/myrm myrm')
        
    print("Compile uptime...")
    bld.program(source='my_uptime.c', 
                target='myuptime', 
                cflags=flags)
    if isfile('build/myuptime'):
        print("Move next.")
        bld.exec_command('cp build/myuptime myuptime')
    
    print("Compile who...")
    bld.program(source='my_who.c', 
                target='mywho', 
                cflags=flags)
    if isfile('build/mywho'):
        print("Move next.")
        bld.exec_command('cp build/mywho mywho')
           
   
   
      