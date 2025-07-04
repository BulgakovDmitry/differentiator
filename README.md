<div align="center">
  <img src="docs/diffPicREADME.png" alt="Diff Banner" width="800">
  
  # 🛡️ Implementation of a differentiating calculator in C (C++)
  ![GitHub code size](https://img.shields.io/github/languages/code-size/BulgakovDmitry/differentiator)
  ![GitHub last commit](https://img.shields.io/github/last-commit/BulgakovDmitry/differentiator)
  
</div>

## 🚀 Quick Start
To build the project:
```cpp
git clone https://github.com/BulgakovDmitry/differentiator
cd differentiator
make run
./diff.out
```
The project has a function for graphical output of a binary tree. For this purpose graphviz is used. Download it on linux at the following script:
```bash
sudo apt update
sudo apt install graphviz
```
It is also possible to output the expression in a pdf file for easy reading. The built-in tex is used for this purpose. Script for installation:
```bash
sudo apt update
sudo apt install texlive-full
```

## 🔍 Overview
All mathematical expressions are written in a binary tree. In the general case, visually it looks as follows (fragment from the graphical dump)
<div align="center">
  <img src="docs/diffGraphDump.png" alt="Graph Dump Banner" width="400">
</div>
