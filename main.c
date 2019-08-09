#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//size of buf
//attention, the size need to be just suitable, or it would need more time to memset
#define SIZE 409600 //as number of bytes, If too small, it will give wird output
//2nd #define SIZE 4096000 //as number of bytes, If too small, it will give wird output

//for the 3rd ? #define SIZE 4096000 //as number of bytes, If too small, it will give wird output


int main(int argc, char *argv[]){
///input stdin, output stdout

// if(argc!=2)
//     puts("args: the input and output name");

//init
// system("rm  /tmp/Euler-Graph-Gen.tmp ;");
// FILE * input = fopen (argv[1],"rb"); 
// if (!input)
	// return -1; 
char* template_node_id = "{\"node_id\": \"%d\",\"node_type\": \"0\",\"node_weight\": \"1\",\"float_feature\": {\"0\": [], \"1\": [";
char* template_neighbor = "]},\"neighbor\": {\"1\":{},\"0\":{";
char* neighbor_ends="}},";
char* edge_start="\"edge\":[";
char* edge_tmp = "{\"src_id\":%d,\"dst_id\":%d,\"edge_type\":0,\"weight\":1,\"uint64_feature\":{},\"float_feature\":{},\"binary_feature\":{}}";
char* edge_end="]}\n";
int a, next_a;
char b[15]; //to store the next int as string
char e[35]; //store the edge
char feature[10];
//init the buffer for read in the char
char* features_str = malloc(SIZE);
char* neighbor_str = malloc(SIZE);
char* edge_str = malloc(SIZE*40);
memset(features_str,0,SIZE);//reset the buf for each run
memset(neighbor_str,0,SIZE);//reset the buf for each run
memset(edge_str,0,SIZE*40);//reset the buf for each run

int f=0;


scanf("%d	",&next_a);
while(true){
//loop begin
//read in the data 
// scanf("%d %d",&a,&b);
    a = next_a;
scanf("%s",b);
// printf(b);
if(scanf("%d	",&next_a) == EOF) break;
// printf("[debug] %d",next_a);


//test if this is still the last node
// int next_a = get();
// std::cin.putback(next_a);//the only place used cpp, may cause conflict?
 f=(f+1)%10;
 sprintf(feature,"%d",f);
 sprintf(e,edge_tmp,a,b);

 //build str
 //puts("add to str");//debug
 if(features_str[0] !=0 ) strcat(features_str,",");//skip the first one
 strcat(features_str,"\"");
 strcat(features_str,feature);
 strcat(features_str,"\"");

 if(neighbor_str[0] !=0 ) strcat(neighbor_str,",");//skip the first one
 strcat(neighbor_str,"\"");
 strcat(neighbor_str,b);
 strcat(neighbor_str,"\":1");

 if(neighbor_str[0] !=0 ) strcat(edge_str,",");//skip the first one
 strcat(edge_str,e);
 
if(next_a == a){
    continue;
}
//else, add current node, print out this and go to next

//output the node
printf(template_node_id,a);
printf(features_str);
printf(template_neighbor);
printf(neighbor_str);
printf(neighbor_ends);
printf(edge_start);
printf(edge_str);
printf(edge_end);
memset(features_str,0,SIZE);//reset the buf for each run
memset(neighbor_str,0,SIZE);//reset the buf for each run
memset(edge_str,0,SIZE*40);//reset the buf for each run
}

//finalize
// char * mv="mv /tmp/Euler-Graph-Gen.tmp ";
// strcat(mv, argv[2]);
// system(mv);

return 0;
}
