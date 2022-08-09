#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;  //
    struct Node *next; //堆疊中用來指向下一個節點
};

typedef struct Node *nodeptr;    //建立一個指標nodeptr

/*將資料推入stack*/
void push(nodeptr *s, char x)
{
    nodeptr q = (nodeptr)malloc(sizeof(struct Node)); //分配記憶體空間
    q -> info = x;
    if(*s == NULL)   //nodeptr *s 為空的情況
    {
        q -> next = NULL;//將q的下一個點指到NULL
        *s = q; //將S指標指到q
    }
    else
    {
        q -> next = *s;  //依序堆疊到下一個
        *s = q;//將S指標指到q
    }
}

/*從堆疊中取出資料*/
char pop(nodeptr *s)
{
    if(*s == NULL)  //nodeptr *s為空的情況 不回傳任何東西
        return;
    else
    {
        char val = (*s)->info;   //將堆疊資料取出
        *s = (*s) -> next;      //將資料的指標指向下一筆
        return val;
    }
}

/*判斷是否為數字用於infixtopostfix*/
int is_digit(char c)
{
    if(c >= '0' && c <= '9') //字元介於0-9間
        return 1;
    else
        return 0;
}

/*決定運算子的優先順序*/
int prec(char c)
{
    switch(c)
    {
   		case '+':case '-':return 1;  //加和減的優先順序
		case '*':case '/':return 3;  //乘除的優先順序
		case '(':return 0;    //右括弧的優先順序
        default:return 0;
    }
}
/*中序轉後序*/
char* in_to_pos(char* in) //將中序放入轉換成後序
{
    char *out, c;
    int i,p;
    nodeptr Stack = 0; //建立一個Stack

    out = (char*)malloc(sizeof(char) * 128);//動態記憶體配置

    i = 0;
    p = 0;
    while((c = in[i++])!='\0')//從中序第一個字元或數字跑到最後一個
    {
		if(is_digit(c))   //如果是數字的話
		{
		    out[p++] = c;  //直接存到postfix
		}
		else
		{
		    if(c != '(' && c != ')') //如果是運算子的話(+-*/)
			{
			    out[p++] = ' ';

				if(Stack == 0 || prec(c) > prec(Stack -> info))//如果stack為空或是運算子的優先順序大於stack裡面 就push進去
				{
					push(&Stack,c);
				}

				else  //如果不是上述情況就pop出來
				{

					out[p++] = pop(&Stack);
					if(prec(c) == prec(Stack -> info)) //與stack中運算子相同的情況
                    {
                        out[p++] = ' ';
                        out[p++] = c;
                        out[p++] = ' ';
                    }
                    else        //運算子優先順序大於stack最上層的運算子
                    {
                        out[p++] = ' ';
                        push(&Stack,c);
                    }
             }
             }
            else  //右括號或左括號的狀況
            {
				if(c == '(')
                {
                    push(&Stack, c); //遇到左括號就push進stack
                }

				else if(c == ')')//如果遇到右括號就一直pop遇到左括號為止，如果沒有就pop完
				{
				    while((c = pop(&Stack))!='('){
						out[p++] = ' ';
						out[p++] = c;

					}

				}
			}
		}
	}
	while(Stack != 0)
	{
		out[p++] = ' ';             //如果stack不為0把stack裡的東西全部pop到postfix
		out[p++] = pop(&Stack);
	}
	out[p] = '\0';

	return out;

}

int eval(int a,int b,char op) //利用後序做計算
{
	int c = 1;
	switch(op){
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': return a/b;
		case '^': while(b>0)
			{
				c *= a;
				--b;
			}
			return c;
	}
}

int pos_eval(char* in)   //後序的計算方式由左至右先尋找連續的兩個運算元和一個運算子，將它們做運算。
{
	int i, n, result;
	char c;
	nodeptr Stack = 0;

	i = 0;
	n = 0;
	while((c = in[i++])!='\0')//從後序第一個字元或數字跑到最後一個
	{
		if(is_digit(c))//是數字的話
		{
			while(c!=' '){
				n = c - '0';
				c = in[i++];
			}
			push(&Stack, n);
			n = 0;
			++c;
		}
		else if(c == ' ')//如果是空格的話就繼續
			continue;
		else  //如果是運算元的話
		{
			result = eval(pop(&Stack),pop(&Stack),c);
			push(&Stack, result);
		}
	}
	return pop(&Stack);
}

int main()
{
	char *in, *pos;
	int res;

	in = (char*)malloc(sizeof(char) * 128);

	printf("Enter Infix Expression:\n");
	scanf("%s",in);

 	pos = in_to_pos(in);

	printf("POSTFIX = %s\n", pos);

	res = pos_eval(pos);

	printf("RESULT = %d\n",res);

}
