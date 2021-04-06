# Helium-Lex

 Personal lexical analyzer by James Zhang, as an individule assignment of the course *COMP450305*: "形式语言与编译——赵银亮", XJTU.



## Author Information

| 姓名   | 学号       | 班级            |
| ------ | ---------- | --------------- |
| 张骏扬 | 2173314309 | 计算机试验班 91 |



## Building and Testing the Project

This project is made with `CMake` tools, and tested in `Ubuntu-Linux`. Also this project can be built by `MSVC` in `Windows` environments.



### Linux

First you need to install `cmake` and `gcc` tools.

```bash
sudo apt install cmake build-essential
```

Then in the `Helium-Lex` directory, use cmake to generate the makefile, and build the project.

```bash
cmake .
make
```

Then run the executable file `HeliumLex`, with sample input given in `./tests/test.py`. The preprocessed files and output files can be the attributes of the executable file.

```bash
HeliumLex ./tests/test.py ./tests
```



### Windows

`TODO: Build and Test in Windows`

