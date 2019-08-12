#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <tuple>

typedef uint64_t NodeID;

typedef std::tuple<NodeID, NodeID, int32_t> EdgeID;


class EmptyEdge{
  EdgeID id_;
  int32_t type_;

  float weight_;

  std::vector<int32_t> uint64_features_idx_;

  std::vector<uint64_t> uint64_features_;

  std::vector<int32_t> float_features_idx_;

  std::vector<float> float_features_;

  std::vector<int32_t> binary_features_idx_;

  std::string binary_features_;
};
std::vector<EmptyEdge*> e;
 std::string node_info;
 int main(){
     int i=0;
     sleep(1);
     for(;i<1024*512;i++){
     e.push_back(new EmptyEdge());
     }
     std::cout<<"ends\n";
     sleep(10);
     return 0;
}
