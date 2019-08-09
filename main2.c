#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define NUM 102400
#define SIZE NUM*sizeof(int64_t) //as number of bytes, If too small, it will give wird output

///input stdin, output argv[0]

int main(int argc, char *argv[]){
  puts(argv[1]);
  puts(argv[2]);
  FILE* input = fopen (argv[1],"r"); 
  //TODO add auto spliter and auto multi threading
  int output = open (argv[2],O_WRONLY|O_CREAT); 


  int a, next_a;
  int b; //to store the next int as string
  //init the buffer
  int edge_num = 0;
  float* features = malloc(SIZE);//build feature space and reuse it 
  for(int i=0;i<101;i++)
      features[i]=i*i;
  
  int64_t* edges = malloc(SIZE);
  float* bufOf1f = malloc(SIZE);
  for(int i=0;i<NUM;i++)
      bufOf1f[i]=1.0;
  int32_t* bufOf1 = malloc(SIZE);
  for(int i=0;i<NUM;i++)
      bufOf1[i]=1;
  int zero=0;
  int OneHundred=100;
  int32_t two=2;
  float feature1 = 0.0;
  int featureInt=0;
  bool lastRun = false;
  #define PINRT1     write(output,&bufOf1[0],sizeof(int32_t));
  #define PINRT1f    write(output,&bufOf1f[0],sizeof(float));
  #define PINRT0     write(output,&zero,sizeof(int32_t));
  #define ONEHundred &OneHundred
  #define DEBUG      ;// printf("%d: %d %d\n",a,blockBytes,nodeInfoBytes);//puts("debug");
  fscanf(input,"%d	",&next_a);
  while(true){
  //loop begin
  //read in the data
      a = next_a;
  fscanf(input,"%d",&b);
  //test if this is the last node
  if(fscanf(input,"%d	",&next_a) == EOF) {lastRun = true; next_a = 0; }//force it to go on
   //build str
  edges[edge_num]=b;
  if(next_a == a){
      edge_num++;
      continue;
  }
   edge_num++;//plus one!
  //else, add current node, print out this and go to next
  
  //output the node
  // node_id + node_type + node_weight
  //1  uint64 feature
  //100 float feature
  //meta.getEdge_type_num() == 1
  int nodeInfoBytes = 8 + 4 + 4 +\
              4 + 4 + 4+\
              edge_num*(12)+\
              4+0*(8+4)+\
              4+2*4+1*4+4*(100)+\
              4;
  int edgeInfoBytes = 8 * 2 + 4 + 4 \
                          +4 \
                          +4 \
                          +4;//36?
  
  int blockBytes =  4 + (4 + 4 * edge_num)+nodeInfoBytes+edgeInfoBytes*edge_num;
  DEBUG
  write(output,&blockBytes,sizeof(int32_t));
  write(output,&nodeInfoBytes,sizeof(int32_t));
  write(output,&a,sizeof(int64_t));//writer.writeLong(block.getNode_id());
  PINRT1 //writer.writeInt(block.getNode_type());
  PINRT1f//writer.writeFloat(block.getNode_weight());
  PINRT1 //writer.writeInt(meta.getEdge_type_num());
  //only have one
  write(output, &edge_num,sizeof(int32_t));//total num of E
   //sumWeight should be EdgeNum*1.0
  float sumWeight = edge_num*1.0;
  write(output,&sumWeight,sizeof(float));
  
  write(output,edges,sizeof(int64_t)*edge_num);//neighborIdList
  write(output,bufOf1,sizeof(float)*edge_num);//neighborWeightList as 1
  
  //no uint64 feature
  PINRT0
  
  //2 float feature getNode_float_feature_num
  write(output,&two,sizeof(int32_t));
  //size of 1st feature
  PINRT1
  //size of 2nd feature
  write(output,ONEHundred,sizeof(int32_t));//100 for each node
  
  //content of 1st feature
  write(output,&feature1,sizeof(float));
  featureInt=(featureInt+1)%2;
  feature1 = featureInt;
  //content of 2nd feature
  write(output,features,sizeof(float)*100);
  
  //no binary feature
  PINRT0
  
  //writer.writeInt(block.getEdge().size());
  write(output,&edge_num,sizeof(int32_t));
  
  for(int i=0;i<edge_num;i++){//all the same
     write(output,&edgeInfoBytes,sizeof(int32_t));
  }
  for(int i=0;i<edge_num;i++){//for each edge
     write(output,&a,sizeof(int64_t));//writer.writeLong(edge.getSrc_id());
     write(output,&edges[i],sizeof(int64_t));//writer.writeLong(edge.getDst_id());
     PINRT1
     PINRT1f
     //no edge feature
     PINRT0
     PINRT0
     PINRT0
  }
  //reset the num
  edge_num = 0;
  if (lastRun) break;
      
}
  
return 0;
}
  
