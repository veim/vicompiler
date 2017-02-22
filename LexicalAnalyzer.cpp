
/* maintain a NFA state, all live NFA states make up a list */
struct re_state{
	int next_idx;	/* next char's idx in p */
	string cur_re;	/* current regular expression string */
	re_state* prev;	
	re_state* next;
}

/* insert node after cur, and return original next ptr */
re_state* insert_state(re_state* cur, int idx, string re){
	re_state* ptr = new re_state(idx, re, cur, cur->next);
	cur->next->prev = ptr;
	cur->next = ptr;
	return ptr->next;
}

/* delete node in cur, and return original next ptr */
re_state* delete_state(re_state* cur){
	re_state* ptr = cur->next;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	delete cur;
	return ptr;
}

bool isFollow(char c, string re){
	if(re[0] == '.' || re[0] == c){
		if(re.size() == 1 || re.size() == 2 && re[1] == '*')
			return true;
	}
	return false;
}


class Solution {
public:
    bool isMatch(string s, string p) {
		re_state* state_head = new re_state(-1, "", NULL, NULL);
		re_state* state_rear = new re_state(-1, "", NULL, NULL);
	    state_head->next = state_rear;
	    state_rear->prev = state_head;

	    int n_live_states = 0;
	    int i;	

	    /* iterate string s and maintain live states */
	    while(*s != '\0'){
	    	re_state* state_cur = state_head;
	    	while(state_cur != state_rear){
	    		if(state_cur.cur_re )
	    		if(p[state_cur.next_idx]){

	    		}






	    	}	

	    	/* try to expand candidates by one step */
	    	if(*(p + candidates[i-1] + 1) == '.'){	

	    	}
	  	

	    	s++;
	    	if(n_live_states == 0)
	    		return false;
	    }	

	 
	    return n_live_states;        	

    }
};


