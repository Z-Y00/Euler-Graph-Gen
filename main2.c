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

  int output = open (argv[1],O_WRONLY|O_CREAT); 
  puts(argv[1]);
  int a, next_a;
  int b; //to store the next int as string
  //init the buffer
  int edge_num = 0;
  float* features = malloc(SIZE);//build feature space and reuse it 
  for(int i=0;i<NUM;i++)
      features[i]=i*i;
  
  int32_t* edges = malloc(SIZE);
  float* bufOf1f = malloc(SIZE);
  for(int i=0;i<NUM;i++)
      bufOf1f[i]=1.0;
  int32_t* bufOf1 = malloc(SIZE);
  for(int i=0;i<NUM;i++)
      bufOf1[i]=1;
  int zero=0;
  int OneHundred=100;
  #define PINRT1    write(output,&bufOf1[0],sizeof(int32_t));
  #define PINRT1f   write(output,&bufOf1f[0],sizeof(float));
  #define PINRT0    write(output,&zero,sizeof(int32_t));
  #define ONEHundred &OneHundred
  #define DEBUG ;//puts("debug");
  scanf("%d	",&next_a);
  while(true){
  //loop begin
  //read in the data
      a = next_a;
  scanf("%d",&b);
  //test if this is the last node
  if(scanf("%d	",&next_a) == EOF) break;
   //build str
  edges[edge_num]=b;
  if(next_a == a){
      edge_num++;
      continue;
  }
  //else, add current node, print out this and go to next
  DEBUG
  
  //output the node
  int nodeInfoBytes = 8 + 4 + 4 +\
              4 + 4 + 4+\
              edge_num*(12)+\
              4+\
              4+4+4+\
              4;
  int edgeInfoBytes = 8 * 2+ 4 \
                          +4+4 \
                          +4+4;
  
  int blockBytes =  4 + (4 + 4 * edge_num)+nodeInfoBytes+edgeInfoBytes*edge_num;
  
  write(output,&blockBytes,sizeof(int32_t));
  write(output,&nodeInfoBytes,sizeof(int32_t));
  write(output,&a,sizeof(int64_t));
  PINRT1
  PINRT1f
  PINRT1
  //only have one??
  write(output, &edge_num,sizeof(int64_t));//total num of E
  PINRT1f
  
  write(output,edges,sizeof(int32_t)*edge_num);//neighborIdList
  write(output,bufOf1,sizeof(float)*edge_num);//neighborWeightList as 1
  
  //no uint64 feature
  PINRT0
  //1 float feature
  PINRT1
  write(output,ONEHundred,sizeof(int32_t));//100 for each node
  write(output,features,sizeof(float)*100);
  //no binary feature
  PINRT0
  
  //L178
  write(output,&edge_num,sizeof(int32_t));
  
  for(int i=0;i<edge_num;i++){//all the same
     write(output,&edgeInfoBytes,sizeof(int32_t));
  }
  for(int i=0;i<edge_num;i++){//for each edge
     write(output,&a,sizeof(int64_t));
     write(output,&edges[i],sizeof(int64_t));
     PINRT1
     PINRT1f
     //no edge feature
     PINRT0
     PINRT0
     PINRT0
  }
  //reset the num
  edge_num = 0;
  }
  
return 0;
}
  