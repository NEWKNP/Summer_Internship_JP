# Summer_Internship_JP
gamma ray radiation simulated by PTSIM.

## Software
### Geant 4

It is a toolkit for the simulation of the passage of particles through matter.  

Download link >> **[link](https://geant4.web.cern.ch/support/download)**  

Available in Linux and mac only.  
For Windows please use virtual operation system ex. **[Oracle VM Virtual Box](https://www.virtualbox.org/)**  

### PTSIM

It stands for Particle Therapy System simulation framework.  

Latest versions >> **[Download link](PTSproject-104-002-001-20190408.tar.gz)**  
Or in this **[Page](https://wiki.kek.jp/display/g4med/PTsim)**   
Or download by cmd command  
(make sure in terminal you are in correct directory)
``` bash
wget https://wiki.kek.jp/download/attachments/5343876/PTSproject-104-002-001-20190408.tar.gz?version=1&modificationDate=1554898709174&api=v2
```

English **[Documents](https://wiki.kek.jp/display/g4med/2018-08++PTSIM+short+tutorial+in+Taiwan)**   
Japanese **[Documents](https://wiki.kek.jp/display/geant4/Geant4+Tutorial+for+Medicine+2018)**   

## Set Up and Installation
``` bash
[WARNING] the program versions (the number in file name) might be same. Please check the file name first!  

# Extract file
tar zxvf PTSproject-104-002-001-20190408.tar.gz

# Build PTSIM
cd PTSproject
## Build library
./buildToolkitIAEA.sh
## Build application
./buildDynamicIAEA.sh

```


![Directory Structure](/asset/Directory_structure.png "Directory Structure")


``` bash
# In DynamicPort directory (workspace) 
cd PTSproject-install/PTSapps/DynamicPort

# Simulation and get data collection as root file
## with**out** simulated render
./bin/PTSdemo -m <filename>
## with simulated render
./bin/PTSdemo -u Qt -i <filename>

# Edit file
emacs <filename>

```

## Simulation Part and Code description
``` bash
[WARNING] You must do IF you download my file *Sample6.mac*
./bin/PTSdemo -m Sample6.mac

# Edit Sample file
emace Sample.mac
-- inside file --
...
/vis ...  //can comment if you don't want render
/run/beamOn <number of beam>
...
-----------------

# Edit radiation parameters
emacs /macros/DynamicPort/particleGun.mac
-- inside file --
/gun/particle <proton|gamma>
/gun/energy <int>. MeV
/gun/position <x> <y> <z> mm
/gun/direction <px> <py> <pz>
-----------------

```

## Github Guide(Linux/Windows)
``` bash
> Go to work directory

*Make sure that your cmd can read git command

# create git
git init

# add work file or folder
git add <file/folder>

# commit
git commit -m "<commit comment>"

> create your repository in github

# link your local directory with git repository
git remote add <your command name> <your github repository link>

# debug (If git push is error)
git fetch <your command name> master
git merge --allow-unrelated-histories

# push your repository
git push <your command name> master

```
