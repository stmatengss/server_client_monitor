<h2>Query System</h2>
<h3>1. System Introduction</h3>
Abel是一家从事大数据分析的公司，每天要从大量的数据中发现有价值的信息。最近他们得到了A国家大约几亿人在2015年的收入数据.对于每一个人，只包含他所在城市编号，年龄以及收入(美元)。现在Abel公司邀请你作为他们的系统架构师，设计并实现一个高效的查找系统，帮助他们公司的数据分析师更快的检索到需要的信息。

该系统的要求如下：<br>
Input: txt格式文件，由若干行组成，每一个行由"城市编号 年龄 收入"组成, 如下：<br>

1001 20 12000<br>
1001 50 24200<br>
1020 30 30000<br>
...

其中，城市编号由四位有效数字组成，XXXX(第一位不为0)，年龄与收入为整数类型。

系统需要实现以下三个常用的查询功能:<br>
1. 查询城市x某个年龄段的平均收入<br>
2. 查询城市X的收于最高的前K位的收入<br>
3. 分别查询某些城市某一年龄段收入的中位数<br>

为了简化你的工作，我们提供一个简单的Memory Store system framework来帮助你实现此内存查询系统，您只能修改core目录下的文件。
系统目录结构如下:<br>
<pre>
CCSP
|---benchmark
|------driver.cpp (main function)
|---bin
|---core (your code)
|------headers.hpp
|------mstore.hpp (your system code)
|---tools
|---Makefile
</pre>

core目录下的mstore.hpp是你实现系统的主要代码，core目录下新增的文件需要引入到mstore.hpp下，以下四个接口需要你实现：<br>

<pre>
/*
  Function: 输入数据预处理
  @Params: input 输入文件路径
*/
<span style="color:#00f">void preprocessing(std::string input);</span>

/*
  Function: 查询城市x某个年龄段的平均收入
  @Params: city 城市编号
  @Params: [startAge, endAge] 左右边界都包含
  @Return: 平均收入。
*/
<span style="color:#00f">float queryAverageIncome(int city, int startAge, int endAge);</span>

/*
  Function: 查询城市X的收于最高的前K位的收入
  @Params: city 城市编号
  @Params: k 前K位
  @Return: 从大到小排序的前K位收入列表
*/
<span style="color:#00f">vector<int> queryIncomeTopK(int city, int k);</span>

/*
  Function: 分别查询某些城市某一年龄段收入的中位数
  @Params: cities 需要查询城市的列表
  @Params: [startAge, endAge] 左右边界都包含
  @Return: 每个城市该年龄段收入中位数列表，返回数据与输入城市编号顺序一一对应
*/
<span style="color:#00f">vector<int> queryMedianIncomes(vector<int> cities, int startAge, int endAge);</span>
</pre>

<h3>2. Getting Started</h3>
<pre>
/*编译程序*/
<span style="color:#00f;">make</span>
/*生成数据, 默认情况下, 每个人产生的数据相同*/
<span style="color:#00f">./bin/gen -o [output file path] -n [Optional: number of persons(default=100000000)]</span>
/*运行测试, 默认情况下, 每个人产生的数据相同*/
<span style="color:#00f">driver -i [input file path]</span>
</pre>

<h3>3. Tips</h3>
简单的实现此系统的功能要求非常的简单，但是需要你细致的优化系统的性能，并注意以下问题:<br>
a) 数据是否能完全放入内存中?<br>
b) 是否能利用多线程加速查询速度？<br>
c) 用户在使用系统时，query到达的顺序并不会固定，你是否考虑到了这个问题？<br>
... ...