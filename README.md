# File Management Utility

This utility provides a set of features to efficiently manage files on your system. Whether you want to share files over the network, hide them, encrypt using XOR cipher, calculate file hashes, search recursively, sort by extension, or perform compression and decompression, this utility has you covered.

### Key Features:

- **Sharing Files:** Share files seamlessly over the network.
- **Hiding Files:** Keep sensitive files out of sight.
- **File Encryption:** Secure your files using the XOR cipher.
- **File Hash Calculation:** Calculate MD5 and SHA256 hashes for data integrity verification.
- **Recursive File Search:** Easily locate files within directories and subdirectories.
- **File Sorting:** Sort files based on their extensions for better organization.
- **File Compression and Decompression:** Compress and decompress files efficiently.

## Use Cases

### 1. **Sharing Files Over the Network**

**Scenario:**
You are working on a collaborative project with team members spread across different locations. The File Management Utility allows you to seamlessly share project files over the network, ensuring everyone has access to the latest updates.

**Steps:**
- Use the "Sharing Files" feature to distribute project files.
- Access shared files from remote locations, promoting collaboration and real-time updates.

### 2. **Securing Sensitive Information**

**Scenario:**
You have confidential files that need an extra layer of security. The File Encryption feature enables you to encrypt these files using the XOR cipher, safeguarding sensitive information.

**Steps:**
- Select the files you want to secure.
- Use the "File Encryption" feature to apply XOR cipher encryption.
- Decryption can be performed when needed using the utility.

### 3. **Verifying Data Integrity**

**Scenario:**
You want to ensure the integrity of your files during transfers or storage. The File Management Utility allows you to calculate MD5 and SHA256 hashes, providing a quick way to verify data integrity.

**Steps:**
- Choose the file(s) you want to verify.
- Utilize the "File Hash Calculation" feature to generate MD5 and SHA256 hashes.
- Compare generated hashes to ensure file integrity.

### 4. **Efficient File Sorting**

**Scenario:**
You have a directory with a mix of file types, and you want to organize them based on their extensions. The utility's "File Sorting" feature simplifies this process.

**Steps:**
- Run the "File Sorting" feature to organize files based on their extensions.
- Enjoy a more structured and organized file system.

### 5. **Searching for Files**

**Scenario:**
You have a large directory structure, and you need to find specific files. The utility's recursive file search feature helps you locate files efficiently.

**Steps:**
- Use the "Recursive File Search" feature to search for files within directories and subdirectories.
- Easily find the files you need without manually navigating through the entire structure.

### 6. **Archiving and Decompressing Files**

**Scenario:**
You want to save storage space or share multiple files as a single compressed archive. The utility's compression and decompression features assist in achieving this.

**Steps:**
- Select the files you want to compress.
- Use the "File Compression" feature to create a compressed archive.
- Decompress files when needed, saving space and simplifying file transfer.

These use cases highlight the versatility of the File Management Utility, showcasing its capability to streamline various file-related tasks.

### Best Practices:

- **MakeFile:** Use MakeFile for streamlined and efficient project building.
- **GitHub Repository:** The project is committed to GitHub for version control and collaboration.
- **Clean Code:** Adopt clean coding practices, including the use of header files.
- **Modern C++:** Utilize modern C++ features for enhanced code readability and maintainability.

## Installation

**Prerequisites:**
- [Msys2](https://www.msys2.org/)
- [Visual Studio Code](https://code.visualstudio.com/download)
- Git (OPTIONAL)

**Step 1: Add Msys2 to Path**
1. Open Windows Settings and search for **Edit environment variables for your account**.
2. In **User variables**, select the `Path` variable and click **Edit**.
3. Add the MinGW-w64 destination folder (e.g., `C:\msys64\ucrt64\bin`).
4. Click **OK** to save the updated PATH.

**Step 2: Run Command in Msys2 ucrt64 Shell**
```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-7zip
```

**Step 3: Get Source Files**
- If Git is installed, run:
  ```bash
  git clone https://github.com/DarKnight-HK/fileManagementUtil.git
  ```
- Alternatively, download the ZIP [here](https://github.com/DarKnight-HK/fileManagementUtil).

**Step 4: Compile the Code**
- Open a command prompt in the directory and run:
  ```bash
  mingw32-make
  ```
- To delete obj files, run:
  ```bash
  mingw32-make clean
  ```

## Authors

- [@DarKnight-HK](https://github.com/DarKnight-HK)
- [@juttsalmanmalhi](https://www.instagram.com/juttsalmanmalhi/)
- [@tayyabawan511](https://www.instagram.com/tayyabawan511/)
- [@afaq_kahloon](https://www.instagram.com/afaq_kahloon/)
