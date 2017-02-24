#include <stdio.h>
#include <stdlib.h>


/* maintain a NFA state, all live NFA states make up a list */
struct re_state{
	int next_idx;	/* next char's idx in p */
	char re[2];	/* current regular expression string */
	struct re_state* prev;	
	struct re_state* next;
};

/* insert node after current one */
/* return original next ptr */
struct re_state* insert_state(struct re_state* cur, int idx, char* re){
	struct re_state* ptr = cur;
	
	ptr = (struct re_state*) malloc(sizeof(struct re_state));
	ptr->next_idx = idx;
	ptr->re[0] = re[0];
	ptr->re[1] = re[1];
	ptr->prev = cur;
	ptr->next = cur->next;

	cur->next->prev = ptr;
	cur->next = ptr;
	return ptr->next;
}

/* delete current node */
/* return original next ptr */
struct re_state* delete_state(struct re_state* cur){
	struct re_state* ptr = cur->next;
	if(cur->prev != NULL)
		cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	return ptr;
}

/* remove repeated states */
void check_state(struct re_state* head, struct re_state* rear){
	struct re_state* ptr_i = head;
	struct re_state* ptr_j;

	while(ptr_i != rear){
		ptr_j = ptr_i->next;

//		printf("re: %c%c, idx:%d\n", ptr_i->re[0], ptr_i->re[1], ptr_i->next_idx);

		while(ptr_j != rear){
			if(ptr_i->next_idx == ptr_j->next_idx)
				ptr_j = delete_state(ptr_j);
			else 
				ptr_j = ptr_j->next;
		}
		ptr_i = ptr_i->next;
	}
}


/* transfer state according to the re and the c */
/* certain new states may be added if there's continuous '*'s */
/* return 0 if c doesn't follow re */
int forward_state(char* p , struct re_state* cur, char c, int* max_idx){
	int idx = cur->next_idx;
	struct re_state* ptr = cur;

	/* check if the c follows the re in cur state */
	if(	!(cur->re[0] == c 
		|| cur->re[0] == '.' && c != '\0' 
		|| cur->re[1] == '*' && c == '\0')){
		return 0;
	}

	/* udpate max followed idx in p */
	if(cur->next_idx > *max_idx)
		*max_idx = cur->next_idx;

	/* transfer states */
	while(p[idx] != '\0' && p[idx + 1] == '*'){
		insert_state(ptr, idx + 2, p + idx);
		ptr = ptr->next;
		idx += 2;
	}
	if(p[idx] != '\0'){
		insert_state(ptr, idx + 1, p + idx);
	}

	return 1;
}


bool isMatch(char* s, char* p) {
	int result, live = 0, flag = 0, i = 0, max_idx = -1;	

	if(s[0] == '\0' && p[0] == '\0')
		return true;


	struct re_state* state_head = (struct re_state*) malloc(sizeof(struct re_state));
	struct re_state* state_rear = (struct re_state*) malloc(sizeof(struct re_state));
	state_head->prev = NULL;
	state_head->next = state_rear;
	state_rear->prev = state_head;
	state_rear->next = NULL;

	/* init states list, same as forward_state based on re '.' and the char '\0' */
	state_head->re[0] = '.';
	state_head->re[1] = '.';
	state_head->next_idx = 0;
	forward_state(p, state_head, '~', &max_idx);

    /* iterate string s and maintain live states */
    while(flag != 2 && state_head->next != state_rear){
    	
    	struct re_state* ptr = state_head->next;
    	struct re_state* next = ptr;

    	live = 0;
    	while(ptr != state_rear){
    		next = ptr->next;
    		result = forward_state(p, ptr, s[i], &max_idx);

 			/* delete cur state if it should not be recycled or not followed*/
  			if(result == 0 || ptr->re[1] != '*')
  				delete_state(ptr);
  
  			if(result == 1 && p[ptr->next_idx] == '\0'){
  				live = 1;
  			}
  			ptr = next;
  		}

  		check_state(state_head, state_rear);

  		/* one more forward to deal with specify case: abc, abcd* */
  		if(s[i] == '\0')
  			flag++;

  		if(flag == 0)
  			i++;
	}

    if(s[i] == '\0' && p[max_idx] == '\0' && live == 1)
    	return true;
    else
    	return false;        	
}


int main(){

	char s[8], p[8];
	printf("input s: ");
	scanf("%s", s);
//	s[0] = '\0';
	printf("\ninput p: ");
	scanf("%s", p);
//	p[0] = '\0';
	printf("result is: %d\n", (int)isMatch(s, p));

}

