#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 100
#define WORD_SIZE 50
#define DELIMS " ,.;:!?\n"

/*
@把文本替换成我们想要的字符
@字符在字符串中出现的次数
@这句话到底有多少个单词
@对不重复单词进行计数
*/

//记录不重复单词的数量并把他们放到数组里
void extractUniqueWords(const char* text, char uniqueWords[][WORD_SIZE], int* uniqueCount) {
	char tempText[TEXT_SIZE] = { 0 };
	strcpy_s(tempText, TEXT_SIZE, text);

	char* context = NULL;

	//这里都是在循环外处理一次，然后进入循环
	char* token = strtok_s(tempText, DELIMS, &context);						//第一次调用 strtok_s 函数，从 tempText 中分割出第一个单词。DELIMS 是预定义的分隔符字符串，strtok_s 会从 tempText 中查找第一个分隔符，将分隔符之前的部分作为一个单词返回，并更新 context 指针记录当前分割位置。如果找到了单词，token 指向该单词的起始地址；若未找到，token 为 NULL

	while (token != NULL) {
		int found = 0;							//初始化一个标志变量 found 为 0，用于标记当前分割出的单词是否已经存在于 uniqueWords 数组中

		//遍历 uniqueWords 数组，检查当前分割出的单词是否已经存在
		for (int j = 0; j < *uniqueCount; ++j) {
			//使用 strcmp 函数比较 token 和 uniqueWords[j] 是否相等。如果相等，说明该单词已经存在，将 found 标志置为 1，并跳出循环
			if (strcmp(token, uniqueWords[j]) == 0) {
				found = 1;
				break;
			}			
		}

		//如果 found 为 0，说明当前分割出的单词是新的不重复单词
		if (!found) {
			strcpy_s(uniqueWords[*uniqueCount], WORD_SIZE, token);
			//将该单词复制到 uniqueWords 数组的下一个空闲位置

			(*uniqueCount)++;						//更新不重复单词的数量
		}
		token = strtok_s(NULL, DELIMS, &context);	//继续从上次分割的位置开始处理剩余的字符串，获取下一个单词
	}

}

int countWords(const char* text) {
	int count = 0;
	char buffer[TEXT_SIZE] = { 0 };

	strcpy_s(buffer, TEXT_SIZE, text);

	char* context = NULL;									//strtok_s 函数需要一个上下文指针 context 来记录分割的位置，初始化为 NULL

	char* token = strtok_s(buffer, DELIMS, &context);		//第一次调用 strtok_s 函数，从 buffer 中分割出第一个单词。strtok_s 会从 buffer 中查找第一个分隔符，将分隔符之前的部分作为一个单词返回，并更新 context 指针记录当前分割位置。如果找到了单词，token 指向该单词的起始地址；若未找到，token 为 NULL

	//只要 token 不为 NULL，就表示还有单词未处理
	while (token != NULL) {
		count++;											//每分割出一个单词，计数器 count 加 1
		token = strtok_s(NULL, DELIMS, &context);			//后续调用 strtok_s 时，第一个参数传入 NULL，表示继续从上次分割的位置开始处理剩余的字符串

		//为什么要传入NULL？
		//strtok_s函数在内部维护了一个状态，用于记录上次分割到的位置。当第一次调用strtok_s时，需要传入要分割的字符串，函数会在这个字符串中查找分隔符，并将找到的第一个子字符串（即单词）返回，同时记录下分割的位置。后续调用时传入NULL，是告诉函数继续从上次记录的位置开始查找下一个分隔符，以实现对整个字符串的连续分割。如果不传入NULL，而是再次传入原始字符串，那么每次都会从字符串的开头重新开始分割，无法达到按顺序逐个获取单词的目的。
	}

	return count;
}

//计算某个字母出现的次数，遍历字符串
int countChar(const char* text, char ch) {
	int count = 0;
	while (*text) {
		if (*text == ch) {
			count++;
		}
		text++;
	}

	return count;
}

//进行字符串的替换
void relpaceWord(const char* text, const char* oldWord, const char* newWord, char* result) {
	char buffer[TEXT_SIZE] = { 0 };				//用来临时存储处理之后的字符串，之后复制到result中

	const char* pos = text;						//指针指向当前正在处理的字符串位置，初始时指向 text 的开头

	const char* temp = text;					//temp 指针用于查找 oldWord 在 text 中的位置，初始时也指向 text 的开头

	size_t oldLen = strlen(oldWord);

	//使用 strstr 函数在 pos 指向的字符串中查找 oldWord 的第一次出现位置，并将结果存储在 temp 中。如果找到了，temp 指向 oldWord 的起始位置；如果没找到，temp 为 NULL，循环结束。
	while ((temp = strstr(pos, oldWord)) != NULL) {

		strncat_s(buffer, sizeof(buffer), pos, temp - pos);			//将 pos 到 temp 之间的字符串追加到 buffer 中。temp - pos 表示这部分字符串的长度

		strcat_s(buffer, sizeof(buffer), newWord);					//将 newWord 追加到 buffer 中，完成一次替换

		pos = temp + oldLen;										//将 pos 指针移动到 oldWord 之后的位置，继续查找下一个 oldWord
	}

	strcat_s(buffer, sizeof(buffer), pos);							//将 pos 之后的剩余字符串追加到 buffer 中

	strcpy_s(result, TEXT_SIZE, buffer);							//将 buffer 中的替换结果复制到 result 中
}

int main(void)
{

	char text[TEXT_SIZE] = "This is a simple test. This test is for testing.";

	char replacedText[TEXT_SIZE] = { 0 };

	char oldWord[] = "test";

	char newWord[] = "example";

	char countCharTarget = 's';

	//用来存储一些独特的单词，用空格去隔开，把每个单词存进数组的每一行；
	char uniqueWords[TEXT_SIZE][WORD_SIZE] = { 0 };

	int uniqueCount = 0;

	relpaceWord(text, oldWord, newWord, replacedText);
	//替换的原来文本，要替换的单词，替换成什么，把替换之后的文本装到新的里面
	printf("Replaced Text: %s\n", replacedText);

	int charChout = countChar(replacedText, countCharTarget);
	printf("Character: '%c' appears %d times.\n", countCharTarget, charChout);

	int wordCount = countWords(replacedText);
	printf("Total number of words %d.\n", wordCount);

	extractUniqueWords(replacedText, uniqueWords, &uniqueCount);
	puts("Unique words: ");

	//二维数组由一位数组模拟而来，这里的for循环时一行一行增加的
	for (int i = 0; i < uniqueCount; i++) {
		printf("%s\n", uniqueWords[i]);
	}

	return 0;
}