# Helium-Lex

 Personal lexical analyzer by James Zhang, as an individule assignment of the course *COMP450305*: "形式语言与编译", XJTU.



## Project description

This project aims to implement a python tokenizer, which is the first module of the compiler. It can read a python script as follows:

```python
import math
a, b, c = 3.3, 4.1, -5.0
print((-b + math.sqrt(b**2 - 4*a*c)) / (2*a))
```

And tokenize it as follows:

```plain
0000	Keyword,			import
0001	Identifier,			math
0002	Identifier,			a
0003	Operator,			,
0004	Identifier,			b
0005	Operator,			,
0006	Identifier,			c
0007	Operator,			=
0008	Float   ,			3.3
0009	Operator,			,
0010	Float   ,			4.1
0011	Operator,			,
0012	Operator,			-
0013	Float   ,			5.0
0014	Identifier,			print
0015	Operator,			(
0016	Operator,			(
0017	Operator,			-
0018	Identifier,			b
0019	Operator,			+
0020	Identifier,			math
0021	Operator,			.
0022	Identifier,			sqrt
0023	Operator,			(
0024	Identifier,			b
0025	Operator,			*
0026	Operator,			*
0027	Integer,			2
0028	Operator,			-
0029	Integer,			4
0030	Operator,			*
0031	Identifier,			a
0032	Operator,			*
0033	Identifier,			c
0034	Operator,			)
0035	Operator,			)
0036	Operator,			/
0037	Operator,			(
0038	Integer,			2
0039	Operator,			*
0040	Identifier,			a
0041	Operator,			)

```

It uses a self-developed DFA to acheive the goal.

Currently, it supports language features as follows:

| Feature                         | Scheduled | Implemented | Tested |
| ------------------------------- | --------- | ----------- | ------ |
| Operators                       | yes       | yes         | yes    |
| Keywords                        | yes       | yes         | yes    |
| Identifiers                     | yes       | yes         | yes    |
| Indents                         | yes       | no          | yes    |
| Decimal Integers                | yes       | yes         | yes    |
| Decimal Floats                  | yes       | yes         | yes    |
| Abnormal Floats `.3, 5.`        | yes       | no          | no     |
| Oct & Hex & Bin Ints `0x8F`     | no        | no          | yes    |
| Comments                        | yes       | yes         | yes    |
| Multiline Comments & Raw String | yes       | no          | yes    |
| Strings                         | yes       | yes         | yes    |
| Line contiuation                | yes       | yes         | yes    |







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
./HeliumLex ./tests/test.py ./tests
```



The result could be checked by comparing with the python language tokenizer.

```bash
python -m tokenize tests/test.py
```





### Windows

Using WSL in Windows is encouraged, but `MSVC` can also be used to build this project.

 1. Start Visual Studio
 2. Select "File" -> "Open" -> "CMake"
 3. Select "CmakeLists.txt"
 4. Wait MSVC to build files
 5. Configure the build and install directory in the root directory
 6. Run HeliumLex.exe in terminal



### MacOS

Building in MacOS is not yet tested, but using the `cmake` tool in MacOS is similar using in Linux.