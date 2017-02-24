
/* maintain a NFA state, all live NFA states make up a list */
struct re_state{
	int next_idx;	/* next char's idx in p */
	char re[2];	/* current regular expression string */
	struct re_state* prev;	
	struct re_state* next;
};

/* insert node after current one, and return original next ptr */
struct re_state* insert_state(struct re_state* cur, int idx, char* re){
	struct re_state* ptr = (struct re_state*) malloc(sizeof(struct re_state));
	ptr->next_idx = idx;
	ptr->re[0] = re[0];
	ptr->re[1] = re[1];
	ptr->prev = cur;
	ptr->next = cur->next;

	cur->next->prev = ptr;
	cur->next = ptr;
	return ptr->next;
}

/* delete current node, and return original next ptr */
struct re_state* delete_state(struct re_state* cur){
	struct re_state* ptr = cur->next;
	if(cur->prev != NULL)
		cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	return ptr;
}

/*
char* next_re(char* p, int idx){

}
*/

struct re_state* forward(char* p , struct re_state** cur){
	if(p[cur->next_idx+1] == '*'){
		cur = insert_state(cur, cur->next_idx + 2, p + cur->next_idx);
		return forward(p, cur);
	}
	else{
		return insert_state(cur, cur->next_idx + 1, p + cur->next_idx);
	}

}

int isFollow(char* p, struct re_state** cur, char c){
	if(cur->re != NULL && (cur->re[0] == '.' || cur->re[0] == c)){
		if(p[cur->next_idx] != '\0'){
			if(p[cur->next_idx+1] == '*')
				insert_state(cur, cur->next_idx + 2, p + cur->next_idx);
			else{
				insert_state(cur, cur->next_idx + 1, p + cur->next_idx);
			}
			cur = forward_state(p, cur);
		}
		if(cur->re[1] == '*')
			return 2;
		else
			return 1;
	}
	return 0;
}

bool isMatch(char* s, char* p) {
	struct re_state* state_head = (struct re_state*) malloc(sizeof(struct re_state));
	struct re_state* state_rear = (struct re_state*) malloc(sizeof(struct re_state));
	state_head->prev = NULL;
	state_head->next = state_rear;
	state_rear->prev = NULL;
	state_rear->next = state_rear;

	if(p[1] == '*'){
		state_head->re[0] = p[0];
		state_head->re[1] = p[1];
		state_head->next_idx = 2;
	}
	else{
		state_head->re[0] = p[0];
		state_head->re[1] = p[1];
		state_head->next_idx = 1;
	}

    int flag = 0, result, i = 0;	

    /* iterate string s and maintain live states */
    while(s[i] != '\0' && state_head != NULL && state_head != state_rear){
    	struct re_state* state_cur = state_head;
    	while(state_cur != state_rear){
    		result = isFollow(p, state_cur, s[i]);
    		if(result == 2){
    			flag = 1;
    			state_cur = state_cur->next;
    		}
    		if(result == 1){
    			flag = 1;
    			state_cur = delete_state(state_cur);
    		}
    		if(result == 0){
    			state_cur = delete_state(state_cur);
    		}
  		}
  		i++;
	}
    if(s[i] == '\0' && flag == 1)
    	return true;
    else
    	return false;        	
}



