


#include "ExpTree.h"
/*
 * Read input string with contains a post-fix expression and buid the corresponding expression evaluation
 *
 * handles input of one post-fix expressio of integers n read from stdin. Examples:
 *   a b c + +    a b - c +   where a,b,c are integers
 * ignores all white space and uses C's sscanf to find acceptable integer formats. Input can flow over
 * multiple lines and is terminated with EOF. 
 *
 * This program only handles regular ints on your machine. So if you input very long int values they will be either
 * truncated or wrap around due to overflow, depening on what sscanf does will integer conversion from too long
 * string values.
 * 
 * Does not handle overflow in general, so if you have a resulting expression too large for an int, an overflow
 * generate unexpected results. 
 *
 */



tokenType convertToken( char *tokenStr, int *tokenVal);

TNode * newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2);

const char *tokenToStr(tokenType tokenT);
void printNode( TNode * node);

ExpT *
newExpressionTree() {
    StackObj *S;
    
    S = newStack();
    return S;
}

//postcondition: the caller needs to free the tree pointer
void
deleteTree(TNode *T) {
    
    if (T != NULL) {
	T->value = 0;	// neurotic
       	deleteTree(T->leftOperand);
       	deleteTree(T->rightOperand);
        free(T);
    }
}

//postcondition: the caller needs to free the tree pointer
void
deleteExpressionTree(ExpT *T) {
  
    TNode *node;
    StackObj *S = T;

    while ((node = (TNode *) pop(S)) != NULL) {
	deleteTree(node);
    }
}


void 
printNode( TNode * node) {
  
        printf(" node addr = %p, type = %d, value = %d, leftOp = %p, rightOp = %p\n", node, node->type, 
			node->value, node->leftOperand, node->rightOperand);

}

//returns enumerated type appropriate to operator or operand
tokenType
convertToken( char *tokenStr, int *tokenVal) {
   
    tokenType retVal;
    char      junkChars[MAX_TOKEN_LENGTH];
    int	      scanCount;

    // check what the token string might be
    scanCount = sscanf (tokenStr, "%d%s", tokenVal, junkChars);
    
    if (scanCount == 1) {
        //printf("token is an integer,str is %s, value = %d\n", tokenStr, *tokenVal);
        return OPERAND;
    }
    if (scanCount == 2) {  // check no trailing characters
        fprintf(stderr, "ERROR, unaccceptable format, had some extra characters in the integer %d\n", *tokenVal);
        exit(EXIT_FAILURE);
    }

    if (scanCount > 2 ) {
        fprintf(stderr, "something weird in input parsing, exiting with str = %s\n", tokenStr);
        exit(EXIT_FAILURE);
    }
    // maybe an operator, try and check the format
    else { 
        if (strlen(tokenStr) > MAX_OPERATOR_LENGTH) {
            printf("sorry, can't handle operators longer than 1 character\n");
            return END;
        }
        switch (tokenStr[0]) {
  	    case '+':
		 retVal = PLUS;
		 break;
  	    case '-': 
		retVal = MINUS; 
                break;
  	    case '*': 
		retVal = MUL;
		break;
  	    case '/':
		retVal = DIV;
		break;
            default: 
		fprintf(stderr, "sorry, don't recognize this operator %c\n", tokenStr[0]);
                exit(EXIT_FAILURE);
	}
        //printf("got operator = %d\n", retVal);
        return retVal;
    }

}

//operands are created as leaves, operators are created as parents to operands and/or operators
TNode *
newTNode(tokenType inputToken, int tokenVal, TNode *op1, TNode *op2)  {
    
    TNode *node;
    
    node = (TNode *) malloc ((size_t)(sizeof(TNode)));
    node->type = inputToken;
    if (inputToken == OPERAND ) { // this will be a leaf
        node->value = tokenVal;
        node->leftOperand = NULL;
        node->rightOperand = NULL;
    }
    else { // this will be an internal node, iff node is created for an operator
        node->leftOperand = op1;
        node->rightOperand = op2;
    }
    return node;
}


const char *
tokenToStr(tokenType tokenT) {
//returns string for operator based on enumerated value
const static char *tokenChars[] = {"+", "-", "*",  "/", "^D"};

	return tokenChars[tokenT];

}

// should not be called with empty tree
int 
expressionEval(TNode *T) {
    //check T to see if operand or operator. if operand, return operand. If operator, 
    //make an int that is equal to fcn(left) (use switch here to determine operator) fcn(right)
    if(T == NULL){
        return 0;
    }
    int eval = 0;
    
    if(T->type == OPERAND){
        return T->value;
    } else {
        //divisor_eval is only used to check division by zero case
        int divisor_eval = 0;
        //find appropriate operator for token type
        // **switch requires a single char, hence the [0]
        switch(tokenToStr(T->type)[0]){
        case '+':
            eval = expressionEval(T->leftOperand) + expressionEval(T->rightOperand);
            break;
  	    case '-': 
            eval = expressionEval(T->leftOperand) - expressionEval(T->rightOperand);
            break;
  	    case '*': 
            eval = expressionEval(T->leftOperand) * expressionEval(T->rightOperand);
            break;
  	    case '/':
            //a new variable to check if dividing by zero
            divisor_eval = expressionEval(T->rightOperand);
            if(divisor_eval == 0){
                fprintf(stderr, "error: cannot divide by zero. Exiting\n");
                exit(EXIT_FAILURE);
            }
            eval = expressionEval(T->leftOperand) / divisor_eval;
            break;
        default: 
		    return 0;
        }
    }
    return eval;
}
void
inorderTraverse(FILE *out, TNode  *T) {
    if(T == NULL){
        return;
    }
    if(T->type == END){
        return;
    }
    //if tokenStr = "^D", nothing will be printed but the node's operands will still be traversed
    char* tokenStr = tokenToStr(T->type);
    if(strcmp(tokenStr,"^D") != 0){
       fprintf(out, "(");   
    }
    inorderTraverse(out, T->leftOperand);
    
    //the "in order" print statements
    if(T->type == OPERAND){
        fprintf(out, "(%i)", T->value);
    } //else if(T->type == END){}
    
    if(strcmp(tokenStr,"") != 0 && strcmp(tokenStr,"^D") != 0){
        fprintf(out,"%s",tokenStr);
    }

    inorderTraverse(out, T->rightOperand);
    if(strcmp(tokenStr,"^D") != 0){
       fprintf(out, ")");   
    }
    
}

//creates the output expression using inorderTraverse() and expressionEval()
//also checks if there is leftover terms and gives an error message
void
outputExpressionTree(ExpT *T){

    TNode *node;
    StackObj *S = T;

    // check if the expression tree is correct for evaluation
    // check overflow or underflow of operands
    if (stackSize(S) > 1 ) {
        fprintf (stderr, "ERROR extra operands in expression\n");
    }
    else {
       node = (TNode *) pop(S);
       inorderTraverse(stdout, node);
       printf(" = %d\n", expressionEval(node));
    }
}

//adds input to stack according to token type
void
inputExpressionTree(ExpT *T){

    char  inputToken[MAX_TOKEN_LENGTH + 1];
    tokenType token;
    TNode  *node, *op1, *op2;
    int   tokenVal;
    StackObj *S;
  
    S = T;
    while (scanf( "%s", inputToken) > 0) {	
	
	//printf("input token = %s\n", inputToken);
      
        token = convertToken (inputToken, &tokenVal);
        //printf( "converted token %d \n", token);
        if (token == OPERAND ) {
        //operand node insertion
	    if ((node = newTNode(OPERAND, tokenVal, NULL, NULL)) == NULL) 
		    fprintf(stderr, "problem creating node\n");
        else
            push(S, (void *)node);
        }
        else {
	        if ((op2 = pop(S)) == NULL) {
		    fprintf(stderr, "sorry, out of operands for operators\n");
 		    exit(EXIT_FAILURE);
            }

	        if ((op1 = pop(S)) == NULL) {
		    fprintf(stderr, "sorry, out of operands for operator\n");
 		    exit(EXIT_FAILURE);
            }
        //assuming no errors for operator node insertion
            node = newTNode(token, 0, op1, op2);
            push(S, node);
        }
    }
}
