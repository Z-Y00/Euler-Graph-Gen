# Gen

```
Debug
./PaRMAT -nVertices 500  -nEdges   25000 -output 1.txt.sorted  -threads 10  -sorted -memUsage 0.6

[yoo@seele Release]$ 

./PaRMAT -nVertices 50000  -nEdges   2500000 -output 0.05.txt.sorted  -threads 10  -sorted -memUsage 0.6

./PaRMAT -nVertices 500000  -nEdges   25000000 -output 0.5.txt.sorted  -threads 10  -sorted -memUsage 0.6
./PaRMAT -nVertices 5000000  -nEdges   250000000 -output 1.txt.sorted  -threads 10  -sorted -memUsage 0.6
./PaRMAT -nVertices 50000000  -nEdges  2500000000 -output 2.txt.sorted  -threads 10  -sorted -memUsage 0.6

./PaRMAT -nVertices 500000000 -nEdges  25000000000 -output /storage/3.txt  -threads 14  -memUsage 0.6

./PaRMAT -nVertices 500000000 -nEdges  25000000000 -output 3.txt.sorted  -threads 14  -sorted -memUsage 0.6

gdb -ex  catch exception  catch throw  run --args 


DATA_DIR="/home/yoo/euler/examples/$DATASET/$NUM_WORKERS"

DATASET=$1


hdfs dfs -mkdir -p /home/yoo/euler/examples/test/1/ /home/yoo/euler/examples/test/2/ /home/yoo/euler/examples/test/4/ /home/yoo/euler/examples/test/8/ /home/yoo/euler/examples/debug/1/



hdfs dfs -mkdir -p /home/yoo/euler/examples/0.05/1/ 
hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/0.05/1/1-0.dat /home/yoo/euler/examples/0.05/1/
hdfs dfs -mkdir -p /home/yoo/euler/examples/0.5/1/ 
hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/0.5/1/1-0.dat /home/yoo/euler/examples/0.5/1/
hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/debug/1/1-0.dat /home/yoo/euler/examples/debug/1/


cd ~/E
./build.sh
./run.sh ../PaRMAT/Release/debug.txt ./test1/ 
./run.sh ../PaRMAT/Release/1.txt.sorted ./test1/ 
Node Count:4664768 Edge Count:250000000
hdfs dfs -rm -r /home/yoo/euler/examples/0.5
hdfs dfs -rm -r /home/yoo/euler/examples/test
hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/test1/1/*  /home/yoo/euler/examples/test/1
hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/test1/2/*  /home/yoo/euler/examples/test/2

hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/test1/4/*  /home/yoo/euler/examples/test/4

hadoop fs -copyFromLocal /home/yoo/Euler-Graph-Gen/test1/8/*  /home/yoo/euler/examples/test/8

cd ~/euler/examples/
./train_test.sh test  overlapcache sync  seele 1 seele 1

cd ~/Euler-Graph-Gen

hdfs dfs -lsr -h  /home/yoo/euler/examples/test/
```

# Format;
https://github.com/alibaba/euler/wiki/%E6%95%B0%E6%8D%AE%E5%87%86%E5%A4%87
```
{
  "node_id": "顶点编号，int",
  "node_type": "顶点类型，int",
  "node_weight": "顶点权重，float",
  "neighbor": {"边类型": {"邻居id": "权重", "...": "..."}, "...": "..."},
  "uint64_feature": {"属性编号": ["int", "..."], "...": "..."},
  "float_feature": {"属性编号": ["float", "..."], "...": "..."},
  "binary_feature": {"属性编号": "string", "...": "..."},
  "edge":[{
    "src_id": "起点id, int",
    "dst_id": "终点id, int",
    "edge_type": "边类型, int",
    "weight": "边权重, float",
    "uint64_feature": {"属性编号": ["int", "..."], "...": ["int", "..."]},
    "float_feature": {"属性编号": ["float", "..."], "...": ["float", "..."]},
    "binary_feature": {"属性编号": "string", "...": "..."}
  }, "..."]
}
```
# BUILD
```
./build.sh
```
# RUN
```
./run.sh ../PaRMAT/Release/1.txt.sorted 1.json
```

#


x c
返回 node 
删除 cache
重新编译，不改cmakelist
debug 小图：
