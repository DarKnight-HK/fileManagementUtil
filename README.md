
# File management utility

This utility has the following features:

- Sharing files over the network
- Hiding files
- File Encryption using XOR cypher
- File hash calculation(MD5, SHA256)
- Recursively searching for files
- Sorting files based on their extension
- File Compression and Decompression

### OTHER GOOD PRACTICES:
- MakeFile
- Commited to GitHub
- Clean Code by using header files
- Modern C++




## Installation

Pre requisites:
- [Msys2](https://www.msys2.org/)
- [Visual Studio Code](https://code.visualstudio.com/download)
- Git (OPTIONAL)
## Step 1 : Add Msys2 to path
1.  In the Windows search bar, type **Settings** to open your Windows Settings.
2.  Search for **Edit environment variables for your account**.
3.  In your **User variables**, select the `Path` variable and then select **Edit**.
4.  Select **New** and add the MinGW-w64 destination folder you recorded during the installation process to the list. If you used the default settings above, then this will be the path: `C:\msys64\ucrt64\bin`.
5.  Select **OK** to save the updated PATH. You will need to reopen any console windows for the new PATH location to be available.


## Step 2: Run this command in Msys2 ucrt64 shell
```bash
  pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-7zip
```
## Step 3: Get the source files
- If you have git installed, run this command
```bash
  git clone https://github.com/DarKnight-HK/fileManagementUtil.git
```
- Or just download zip using this [link](https://github.com/DarKnight-HK/fileManagementUtil)

## Step 4: Compile the code
- Open a command prompt in the directory the files are present at and run this command
```bash
  mingw32-make
```
- Now run this command to delete the obj files
``` bash
  mingw32-make clean
```
## Authors

- [@DarKnight-HK](https://github.com/DarKnight-HK)
- [@juttsalmanmalhi](https://www.instagram.com/juttsalmanmalhi/)
- [@tayyabawan511](https://www.instagram.com/tayyabawan511/)
- [@afaq_kahloon](https://www.instagram.com/afaq_kahloon/)

