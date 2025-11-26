How to run the project 
Windows
1. Clone this repository 
2. Install the vcpkg on your computer
3. Open the terminal and go to the root of the vcpkg installation folder, run git rev-parse HEAD and copy the baseline
4. Paste the baseline value you just copied in vcpkg.json's "builtin-baseline" entry.
5. Create and environment variable 'VCPKG_ROOT=path\to\vcpkg' (the fist layer inside vcpkg directory)
6. Open the project as directory in VisualStudio
