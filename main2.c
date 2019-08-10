#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define NUM 2*1024*1024  // M of 
#define SIZE NUM*sizeof(int64_t) //as number of bytes, If too small, it will give wird output

///input stdin, output argv[0]

int main(int argc, char *argv[]){
  puts(argv[1]);
  //puts(argv[2]);
  FILE* input = fopen (argv[1],"r"); 
  int output2[2];
  int output4[4];
  int output8[8];
  //TODO add auto spliter roundrubin and opt
  int output = open("./1-0.dat",O_WRONLY|O_CREAT); 
  output2[0] = open("./2-0.dat",O_WRONLY|O_CREAT);
  output2[1] = open("./2-1.dat",O_WRONLY|O_CREAT);
  output4[0] = open("./4-0.dat",O_WRONLY|O_CREAT);
  output4[1] = open("./4-1.dat",O_WRONLY|O_CREAT);
  output4[2] = open("./4-2.dat",O_WRONLY|O_CREAT);
  output4[3] = open("./4-3.dat",O_WRONLY|O_CREAT);
  output8[0] = open("./8-0.dat",O_WRONLY|O_CREAT);
  output8[1] = open("./8-1.dat",O_WRONLY|O_CREAT);
  output8[2] = open("./8-2.dat",O_WRONLY|O_CREAT);
  output8[3] = open("./8-3.dat",O_WRONLY|O_CREAT);
  output8[4] = open("./8-4.dat",O_WRONLY|O_CREAT);
  output8[5] = open("./8-5.dat",O_WRONLY|O_CREAT);
  output8[6] = open("./8-6.dat",O_WRONLY|O_CREAT);
  output8[7] = open("./8-7.dat",O_WRONLY|O_CREAT);

if(output8[7]==-1) puts("open failed");
  int output_count = 0; //roundrubin 
  
  int64_t a, next_a;
  int64_t b; //to store the next int as string
  //init the buffer
  int edge_num = 0;
  int i;//for the gcc 4.8 
  float* features = malloc(SIZE);//build feature space and reuse it 
  for( i=0;i<101;i++)
      features[i]=i*i;
  
  int64_t* edges = malloc(SIZE);
  float* bufOf1f = malloc(SIZE);
  for(i=0;i<NUM;i++)
      bufOf1f[i]=1.0;
  int32_t* bufOf1 = malloc(SIZE);
  for(i=0;i<NUM;i++)
      bufOf1[i]=1;
  int zero=0;
  int OneHundred=100;
  int32_t two=2;
  float feature1 = 0.0;
  int featureInt=0;
  bool lastRun = false;
  char* write_buf = malloc(SIZE*100);
  int write_ptr = 0;
  #define WRITE(x,y,z) write_buf[write_ptr]=y; write_ptr+=z;
  #define PINRT1       WRITE(output,&bufOf1[0],sizeof(int32_t));
  #define PINRT1f      WRITE(output,&bufOf1f[0],sizeof(float));
  #define PINRT0       WRITE(output,&zero,sizeof(int32_t));
  #define ONEHundred   &OneHundred
  #define DEBUG        ;// printf("%d: %d %d\n",a,blockBytes,nodeInfoBytes);//puts("debug");

  fscanf(input,"%lld	",&next_a);
  while(true){
  //loop begin
  //read in the data
      a = next_a;
  fscanf(input,"%lld",&b);
  //test if this is the last node
  if(fscanf(input,"%lld	",&next_a) == EOF) {lastRun = true; next_a = 0; }//force it to go on
   //build str
  edges[edge_num]=b;
  if(next_a == a){
      edge_num++;
      continue;
  }
   edge_num++;//plus one!
   if(edge_num>SIZE) {puts("the edge_num"); printf("%d",edge_num);exit(1);}
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
  WRITE(output,&blockBytes,sizeof(int32_t));
  WRITE(output,&nodeInfoBytes,sizeof(int32_t));
  WRITE(output,&a,sizeof(int64_t));//writer.writeLong(block.getNode_id());
  PINRT1 //writer.writeInt(block.getNode_type());
  PINRT1f//writer.writeFloat(block.getNode_weight());
  PINRT1 //writer.writeInt(meta.getEdge_type_num());
  //only have one
  WRITE(output, &edge_num,sizeof(int32_t));//total num of E//    writer.writeIntList(edgeGroupNum);
   //sumWeight should be EdgeNum*1.0
  float sumWeight = edge_num*1.0;
  WRITE(output,&sumWeight,sizeof(float));
  
  WRITE(output,edges,sizeof(int64_t)*edge_num);//neighborIdList
  WRITE(output,bufOf1,sizeof(float)*edge_num);//neighborWeightList as 1
  
  //no uint64 feature
  PINRT0
  
  //2 float feature getNode_float_feature_num
  WRITE(output,&two,sizeof(int32_t));
  //size of 1st feature
  PINRT1
  //size of 2nd feature
  WRITE(output,ONEHundred,sizeof(int32_t));//100 for each node
  
  //content of 1st feature
  WRITE(output,&feature1,sizeof(float));
  featureInt=(featureInt+1)%2;
  feature1 = featureInt;
  //content of 2nd feature
  WRITE(output,features,sizeof(float)*100);
  
  //no binary feature
  PINRT0
  
  //writer.writeInt(block.getEdge().size());
  WRITE(output,&edge_num,sizeof(int32_t));
  
  for(i=0;i<edge_num;i++){//all the same
     WRITE(output,&edgeInfoBytes,sizeof(int32_t));
  }
  for(i=0;i<edge_num;i++){//for each edge
     WRITE(output,&a,sizeof(int64_t));//writer.writeLong(edge.getSrc_id());
     WRITE(output,&edges[i],sizeof(int64_t));//writer.writeLong(edge.getDst_id());
     PINRT1
     PINRT1f
     //no edge feature
     PINRT0
     PINRT0
     PINRT0
  }
  //reset the num
  edge_num = 0;
  output_count++;
  //real write
  int result = 0;
  result = write(output,write_buf,write_ptr);//1
  if(result == -1) puts("write failed");
  result = write(output2[output_count%2],write_buf,write_ptr);//2
  if(result == -1) puts("write failed");
  result = write(output4[output_count%4],write_buf,write_ptr);//4
  if(result == -1) puts("write failed");
  result = write(output8[output_count%8],write_buf,write_ptr);//8
  if(result == -1) puts("write failed");
  //printf("%d",write_ptr);
//  puts("write done");
  write_ptr = 0;

  if (lastRun) break;
      
}
close(output);
close(output2[0]);  
close(output2[1]);  
close(output4[0]);  
close(output4[1]);
close(output4[2]);  
close(output4[3]);
close(output8[0]);  
close(output8[1]);
close(output8[2]);  
close(output8[3]);
close(output8[4]);  
close(output8[5]);
close(output8[6]);  
close(output8[7]);
return 0;
}
  
