# Gen

```
Debug
./PaRMAT -nVertices 500  -nEdges   25000 -output 1.txt.sorted  -threads 10  -sorted -memUsage 0.6

[yoo@seele Release]$ 
./PaRMAT -nVertices 5000000  -nEdges   250000000 -output 1.txt.sorted  -threads 10  -sorted -memUsage 0.6
./PaRMAT -nVertices 50000000  -nEdges  2500000000 -output 2.txt.sorted  -threads 10  -sorted -memUsage 0.6

./PaRMAT -nVertices 500000000 -nEdges  25000000000 -output /storage/3.txt  -threads 14  -memUsage 0.6

./PaRMAT -nVertices 500000000 -nEdges  25000000000 -output 3.txt.sorted  -threads 14  -sorted -memUsage 0.6


hdfs dfs -rm -r /home/yoo/euler/examples/test/1


DATA_DIR="/home/yoo/euler/examples/$DATASET/$NUM_WORKERS"

DATASET=$1

./train_test.sh test  overlapcache sync  seele 1 seele 1

hdfs dfs -mkdir -p /home/yoo/euler/examples/test/1/

hadoop fs -copyFromLocal /home/yoo/E/*  /home/yoo/euler/examples/test/

hdfs dfs -lsr  /home/yoo/euler/examples/test/
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