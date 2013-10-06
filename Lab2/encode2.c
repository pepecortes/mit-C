#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN     9

struct tnode
{
    struct  tnode* left; /*used when in tree*/
    struct  tnode* right; /*used when in tree*/  
    struct  tnode* parent;/*used when in tree*/
    struct  tnode* next; /*used when in list*/ 
    float   freq;
    int     isleaf;
    char     symbol;
};

struct freqnode{ //store characters and their frequencies
		char symbol;
		unsigned int count;
		float freq;
		struct freqnode* next;
};

/*global variables*/
char code[MAX_SYMBOLS][MAX_LEN];
struct tnode* root=NULL; /*tree of symbols*/
struct tnode* qhead=NULL; /*list of current symbols*/
struct cnode* chead=NULL;/*list of code*/
struct freqnode* fhead = NULL; /*list of frequencies*/
int NCHAR = 0; /*number of characters/nodes*/

/*
    @function   talloc
    @desc       allocates new node 
*/
struct tnode* talloc(int symbol,float freq)
{
    struct tnode* p=(struct tnode*)malloc(sizeof(struct tnode));
    if(p!=NULL)
    {
        p->left=p->right=p->parent=p->next=NULL;
        p->symbol=symbol;
        p->freq=freq;
		p->isleaf=1;
    }
    return p;
}

/*
    @function   falloc
    @desc       allocates new freqnode 
*/
struct freqnode* falloc(char c){
    struct freqnode* p = (struct freqnode*)malloc(sizeof(struct freqnode));
    if(p != NULL){
				p->symbol = c;
        p->next = NULL;
        p->count = 0;
        p->freq = 0;
    }
    return p;
}

/*
    @function display_tnode_list
    @desc     displays the list of tnodes during code construction
*/
void pq_display(struct tnode* head)
{
    struct tnode* p=NULL;
    printf("list:");
    for(p=head;p!=NULL;p=p->next)
    {
        printf("(%c,%f) ",p->symbol,p->freq);
    }
    printf("\n");
}

/*
 * name: 	tree_display
 * @param:	root of the tree
 * @return:	void, just print; used for debugging 
 */
void tree_display(struct tnode* head){
	if (head->isleaf){
		printf("(%c,%f) ",head->symbol,head->freq);
		return;
	}
	tree_display(head->right);
	tree_display(head->left);
}

/*
    @function pq_insert
    @desc     inserts an element into the priority queue
    NOTE:     makes use of global variable qhead
*/
void pq_insert(struct tnode* p){
	struct tnode* curr=NULL;
	struct tnode* prev=NULL;
	printf("inserting:%c,%f\n",p->symbol,p->freq);
	if(qhead == NULL){ //qhead is empty
		qhead = p;
		return;
	}	
	//find correct position to insert
	curr = qhead;
	while ((curr != NULL) && (p->freq >= curr->freq)){
		prev = curr;
		curr = curr->next;
	}
	p->next = curr;
	if (curr == qhead){ //insert at the beginning
		qhead = p;
	}
	else { //insert between prev and next
		prev->next = p;
	}
	return;
}

/*
    @function pq_pop
    @desc     removes the first element
    NOTE:     makes use of global variable qhead
*/
struct tnode* pq_pop(){
	struct tnode* p=NULL;
    //remove and return front of the queue
    if (qhead == NULL){
		return NULL;
	}
    p = qhead;
    qhead = qhead->next;
    p->next = NULL;
    printf("popped:%c,%f\n",p->symbol,p->freq);
	return p;
}

/*
	@function build_code
	@desc     generates the string codes given the tree
	NOTE: makes use of the global variable root
*/
void generate_code(struct tnode* root,int depth){
	int symbol;
	int len; /*length of code*/
	if(root->isleaf){
		symbol = root->symbol;
		len = depth;
		code[symbol][len] = '\0';
		while (root->parent != NULL){
			len--;
			if (root->parent->right == root){
				code[symbol][len] = '1';
			} else {
				code[symbol][len] = '0';
			}
			root = root->parent;
		}
		printf("built code:%c,%s\n",symbol,code[symbol]);
	} else {
		generate_code(root->left,depth+1);
		generate_code(root->right,depth+1);
	}
}

/*
	@func	dump_code
	@desc	output code file
*/
void dump_code(FILE* fp)
{
	int i=0;
	for(i=0;i<MAX_SYMBOLS;i++)
	{
		if(code[i][0]) /*non empty*/
			fprintf(fp,"%c %s\n",i,code[i]);
	}
}

/*
	@func	encode
	@desc	outputs compressed stream
*/
void encode(char* str,FILE* fout)
{
	while(*str)
	{
		fprintf(fout,"%s",code[*str]);
		str++;
	}
}


/*
 * 
 * name: search frequency node
 * @param character to lookup, head of freqnode list
 * @return the found node. create if does not exist
 * 
 */
struct freqnode* search_freqnode(char c, struct freqnode *head){
	
		struct freqnode *curr = head;
		struct freqnode *prev = NULL;
		
		while (curr != NULL){
				if (curr->symbol == c){
						return curr;
				}
				prev = curr;
				curr = curr->next;
		}
		//not found: create
		prev->next = falloc(c);
		return prev->next;
}

/*
 * 
 * name: count frequencies
 * @desc ouputs number of different characters and their frequencies
 * @return pointer to root freqnode 
 * 
 */
struct freqnode* count_freq(char *file){
    /*
    example:
    float freq[]={0.01,0.04,0.05,0.11,0.19,0.20,0.4};
		int   NCHAR=7; //number of characters
    */
    char c = 0;
    unsigned int count_char = 0;
    struct freqnode *head = NULL;
    struct freqnode *pnode = NULL;
    
    head = falloc('a'); //create the list. first item is an 'a'
		FILE* fp=fopen(file,"r");
		while ((c = (char)fgetc(fp)) != EOF){ //browse the file
				pnode = search_freqnode(c, head); //create if does not exist
				pnode->count++;
				count_char++;
		}
		fclose(fp);
		
		/* compute frequencies */
		pnode = head;
		do {
			pnode->freq = (float)pnode->count / count_char;
		} while ((pnode = pnode->next) != NULL);
		
		return head;
}

/*
    @function main
*/
int main()
{
    struct tnode* p=NULL;
    struct tnode *lc, *rc;
    struct freqnode *fcurr;
    int i=0;
		const char *CODE_FILE="code.txt";
		const char *OUT_FILE="encoded.txt";
		char *IN_FILE = "book.txt";
		FILE* fout=NULL;
		
		memset(code,0,sizeof(code)); //zero out code
		qhead=NULL;
		fhead = count_freq(IN_FILE); //read characters and count frequencies
		
    /*initialize with freq*/
    fcurr = fhead;
		while (fcurr != NULL){
				pq_insert(talloc(fcurr->symbol, fcurr->freq));
				NCHAR++;
				fcurr = fcurr->next;
		}
    
    /*build tree*/
    i = 0;
    for(i=0; i<NCHAR-1; i++){
				printf("Iteration: %i\n", i);
        lc=pq_pop();
        rc=pq_pop();
        p=talloc(0,lc->freq+rc->freq);
        lc->parent=rc->parent=p;
        p->right=rc; p->left=lc;
				p->isleaf=0;
        pq_insert(p);
    }
    root=pq_pop(); //get root
    generate_code(root,0); //build code
		puts("code:");//output code
		fout=fopen(CODE_FILE,"w");
		dump_code(stdout);
		dump_code(fout);
		fclose(fout);

	///*encode a sample string*/
	//puts("orginal:abba cafe bad");
	//fout=fopen(OUT_FILE,"w");
	//encode("abba cafe bad",stdout);
	//encode("abba cafe bad",fout);
	//fclose(fout);
	//getchar();
	///*TODO: clear resources*/
    return 0;
}
