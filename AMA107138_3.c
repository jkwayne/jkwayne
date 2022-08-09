#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;  //
    struct Node *next; //���|���Ψӫ��V�U�@�Ӹ`�I
};

typedef struct Node *nodeptr;    //�إߤ@�ӫ���nodeptr

/*�N��Ʊ��Jstack*/
void push(nodeptr *s, char x)
{
    nodeptr q = (nodeptr)malloc(sizeof(struct Node)); //���t�O����Ŷ�
    q -> info = x;
    if(*s == NULL)   //nodeptr *s ���Ū����p
    {
        q -> next = NULL;//�Nq���U�@���I����NULL
        *s = q; //�NS���Ы���q
    }
    else
    {
        q -> next = *s;  //�̧ǰ��|��U�@��
        *s = q;//�NS���Ы���q
    }
}

/*�q���|�����X���*/
char pop(nodeptr *s)
{
    if(*s == NULL)  //nodeptr *s���Ū����p ���^�ǥ���F��
        return;
    else
    {
        char val = (*s)->info;   //�N���|��ƨ��X
        *s = (*s) -> next;      //�N��ƪ����Ы��V�U�@��
        return val;
    }
}

/*�P�_�O�_���Ʀr�Ω�infixtopostfix*/
int is_digit(char c)
{
    if(c >= '0' && c <= '9') //�r������0-9��
        return 1;
    else
        return 0;
}

/*�M�w�B��l���u������*/
int prec(char c)
{
    switch(c)
    {
   		case '+':case '-':return 1;  //�[�M��u������
		case '*':case '/':return 3;  //�������u������
		case '(':return 0;    //�k�A�����u������
        default:return 0;
    }
}
/*��������*/
char* in_to_pos(char* in) //�N���ǩ�J�ഫ�����
{
    char *out, c;
    int i,p;
    nodeptr Stack = 0; //�إߤ@��Stack

    out = (char*)malloc(sizeof(char) * 128);//�ʺA�O����t�m

    i = 0;
    p = 0;
    while((c = in[i++])!='\0')//�q���ǲĤ@�Ӧr���μƦr�]��̫�@��
    {
		if(is_digit(c))   //�p�G�O�Ʀr����
		{
		    out[p++] = c;  //�����s��postfix
		}
		else
		{
		    if(c != '(' && c != ')') //�p�G�O�B��l����(+-*/)
			{
			    out[p++] = ' ';

				if(Stack == 0 || prec(c) > prec(Stack -> info))//�p�Gstack���ũάO�B��l���u�����Ǥj��stack�̭� �Npush�i�h
				{
					push(&Stack,c);
				}

				else  //�p�G���O�W�z���p�Npop�X��
				{

					out[p++] = pop(&Stack);
					if(prec(c) == prec(Stack -> info)) //�Pstack���B��l�ۦP�����p
                    {
                        out[p++] = ' ';
                        out[p++] = c;
                        out[p++] = ' ';
                    }
                    else        //�B��l�u�����Ǥj��stack�̤W�h���B��l
                    {
                        out[p++] = ' ';
                        push(&Stack,c);
                    }
             }
             }
            else  //�k�A���Υ��A�������p
            {
				if(c == '(')
                {
                    push(&Stack, c); //�J�쥪�A���Npush�istack
                }

				else if(c == ')')//�p�G�J��k�A���N�@��pop�J�쥪�A������A�p�G�S���Npop��
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
		out[p++] = ' ';             //�p�Gstack����0��stack�̪��F�����pop��postfix
		out[p++] = pop(&Stack);
	}
	out[p] = '\0';

	return out;

}

int eval(int a,int b,char op) //�Q�Ϋ�ǰ��p��
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

int pos_eval(char* in)   //��Ǫ��p��覡�ѥ��ܥk���M��s�򪺨�ӹB�⤸�M�@�ӹB��l�A�N���̰��B��C
{
	int i, n, result;
	char c;
	nodeptr Stack = 0;

	i = 0;
	n = 0;
	while((c = in[i++])!='\0')//�q��ǲĤ@�Ӧr���μƦr�]��̫�@��
	{
		if(is_digit(c))//�O�Ʀr����
		{
			while(c!=' '){
				n = c - '0';
				c = in[i++];
			}
			push(&Stack, n);
			n = 0;
			++c;
		}
		else if(c == ' ')//�p�G�O�Ů檺�ܴN�~��
			continue;
		else  //�p�G�O�B�⤸����
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
