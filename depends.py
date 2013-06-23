# python script to grab and install dependencies

# check if a program is installed
def which(program):
    import os
    def is_exe(fpath):
        return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            path = path.strip('"')
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file

    return None

def install():
    from subprocess import call
    call(["sudo", "apt-get", "install", "clang nasm"])

needsDeps = False

# clang
if which("clang"):
    print "clang is installed"
else:
    needsDeps = True

# nasm
if which("nasm"):
    print "nasm is installed"
else:
    needsDeps = True

# install deps
if needsDeps:
    install()
