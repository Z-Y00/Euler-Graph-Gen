#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//size of buf
#define SIZE 4096 //as number of bytes, If too small, it will give wird output


int main(int argc, char *argv[]){
///input stdin, output stdout

// if(argc!=2)
//     puts("args: the input and output name");

//init
// system("rm  /tmp/Euler-Graph-Gen.tmp ;");
// FILE * input = fopen (argv[1],"rb"); 
// if (!input)
	// return -1; 
char* template_node_id = "\"node_id\": \"%d\",\n";
char* template_type = "\"node_type\": \"0\",\n";
char* template_node_weight = "\"node_weight\": \"1\",\n";
char* template_feature = "\"float_feature\": {\"0\": [], \"1\": [\n";
char* feature_ends="]},\n";
char* template_neighbor = "\"neighbor\": {\"1\":{},\"0\":{\n";
char* neighbor_ends="}";
int a, next_a;
char b[20]; //to store the next int as string

//init the buffer for read in the char
char* features_str = malloc(SIZE);
char* neighbor_str = malloc(SIZE);
memset(features_str,0,SIZE);//reset the buf for each run
memset(neighbor_str,0,SIZE);//reset the buf for each run

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
#define next_feature "1"
#define next_neig b

 //build str
 //puts("add to str");//debug
 if(features_str[0] !=0 ) strcat(features_str,",");//skip the first one
 strcat(features_str,next_feature);

 if(neighbor_str[0] !=0 ) strcat(neighbor_str,",");//skip the first one
 strcat(neighbor_str,next_neig);
 strcat(neighbor_str,":1");

if(next_a == a){
    continue;
}
//else, add current node, print out this and go to next

//output the node
puts("{");
printf(template_node_id,a);
printf(template_type);

printf(template_node_weight);

printf(template_feature);
printf(features_str);
printf(feature_ends);
printf(template_neighbor);
printf(neighbor_str);
printf(neighbor_ends);

puts("}");

memset(features_str,0,SIZE);//reset the buf for each run
memset(neighbor_str,0,SIZE);//reset the buf for each run
}

//finalize
// char * mv="mv /tmp/Euler-Graph-Gen.tmp ";
// strcat(mv, argv[2]);
// system(mv);

return 0;
}