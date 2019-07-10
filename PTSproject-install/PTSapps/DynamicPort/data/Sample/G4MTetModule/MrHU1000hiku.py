import sys

def checkFileFormat(fname):
    if fname == "exit" : sys.exit()
    #check file is fname or not.
    ret = True
    if fname.split('.')[-1] != "tet":
        ans = raw_input("it is not .tet file. Are you OK? (Y/N):") 
        if ans not in ["Y","y","Yes","yes","YES"]: 
            ret = False
    return ret

def readFile():
    while True:
        try:
            # input file name
            fname = str(raw_input("Please .tet file name:"))
            # check .tet file or not
            if not checkFileFormat(fname): continue
            #file open
            f = open(fname,'r')
        except SystemExit: sys.exit()
        except:
            #error
            print "Sorry, file open failed. Try again."
            print sys.exc_info()
        else:
            #success
            print "file open successed."
            break
    # read first line
    f.readline()
    # reading file
    readed = []
    for l in f:
        buf = l.split()
        readed.append(buf)
    print str(len(readed)) + " lines read completed."
    return readed


def main():
    # file read. readed is list.
    readed = readFile()
    # calculation
    for l in readed:
        l[-1] = str(float(l[-1]) - 1000)
    
    # open output file.
    while True:
        try:
            outfname = raw_input("Please output file name: ")
            if not checkFileFormat(outfname): continue 
            fout = open(outfname,"w")
        except SystemExit: sys.exit()
        except:
            print "file open failed. please try again."
            print sys.exc_info()
        else:
            break

    #writing to output file
    print "Writing file..."
    fout.write(str(len(readed)))
    fout.write("\n")
    for l in readed:
        fout.write(" ".join(l))
        fout.write("\n")
    print "Write complete. GOOD BYE!"

if __name__ == "__main__":
    main()
