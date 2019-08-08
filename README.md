# Gen
```
./PaRMAT -nVertices 5000000 -nEdges 2500000 -output 1.txt.sorted  -threads 10  -sorted

./PaRMAT -nVertices 50000000 -nEdges 250000000 -output 2.txt-sorted  -threads 10  -sorted

```
#Format;
https://github.com/alibaba/euler/wiki/%E6%95%B0%E6%8D%AE%E5%87%86%E5%A4%87

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

#BUILD
```
./build.sh
```
#RUN
```
./run.sh ../PaRMAT/Release/1.txt.sorted 1.json
```

#