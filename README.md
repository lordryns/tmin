# tmin
A lazy text editor in your terminal!

**Disclaimer**: tmin is not intended to be a full scale editor but merely a quick way to add or update lines in a file.

if you want a conventional editor, check out Neovim or GNU Nano


## Installation guide

*note:* pre-built binaries or exist for windows and termux (android) users, for any other architecture, you'd need to manually build from source.

### For Windows 
Just go to the releases and download the .exe or .tar.gz file and you're set

### For Termux (Android):
Run 

```bash 
bash <(curl -s https://raw.githubusercontent.com/lordryns/tmin/main/install.sh)
```

This should install help you set everything up, if it fails you can either:

1. Clone this repo and build from source 
2. Manually install the executable from the releases tab

### Building from source 
Step 1: Clone the repo 

```bash 
git clone https://github.com/lordryns/tmin.git
```

Step 2: Build from source 
Enter the path
```bash 
cd tmin
```
then
```bash 
gcc -o tmin main.c
```

or if you're using clang 
```bash 
clang main.c -o tmin
```

*note* that it should be `tmin.exe` if you're on windows.


Happy hacking :)
