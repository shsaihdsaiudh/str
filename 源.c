#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 100
#define WORD_SIZE 50
#define DELIMS " ,.;:!?\n"

/*
@���ı��滻��������Ҫ���ַ�
@�ַ����ַ����г��ֵĴ���
@��仰�����ж��ٸ�����
@�Բ��ظ����ʽ��м���
*/

//��¼���ظ����ʵ������������Ƿŵ�������
void extractUniqueWords(const char* text, char uniqueWords[][WORD_SIZE], int* uniqueCount) {
	char tempText[TEXT_SIZE] = { 0 };
	strcpy_s(tempText, TEXT_SIZE, text);

	char* context = NULL;

	//���ﶼ����ѭ���⴦��һ�Σ�Ȼ�����ѭ��
	char* token = strtok_s(tempText, DELIMS, &context);						//��һ�ε��� strtok_s �������� tempText �зָ����һ�����ʡ�DELIMS ��Ԥ����ķָ����ַ�����strtok_s ��� tempText �в��ҵ�һ���ָ��������ָ���֮ǰ�Ĳ�����Ϊһ�����ʷ��أ������� context ָ���¼��ǰ�ָ�λ�á�����ҵ��˵��ʣ�token ָ��õ��ʵ���ʼ��ַ����δ�ҵ���token Ϊ NULL

	while (token != NULL) {
		int found = 0;							//��ʼ��һ����־���� found Ϊ 0�����ڱ�ǵ�ǰ�ָ���ĵ����Ƿ��Ѿ������� uniqueWords ������

		//���� uniqueWords ���飬��鵱ǰ�ָ���ĵ����Ƿ��Ѿ�����
		for (int j = 0; j < *uniqueCount; ++j) {
			//ʹ�� strcmp �����Ƚ� token �� uniqueWords[j] �Ƿ���ȡ������ȣ�˵���õ����Ѿ����ڣ��� found ��־��Ϊ 1��������ѭ��
			if (strcmp(token, uniqueWords[j]) == 0) {
				found = 1;
				break;
			}			
		}

		//��� found Ϊ 0��˵����ǰ�ָ���ĵ������µĲ��ظ�����
		if (!found) {
			strcpy_s(uniqueWords[*uniqueCount], WORD_SIZE, token);
			//���õ��ʸ��Ƶ� uniqueWords �������һ������λ��

			(*uniqueCount)++;						//���²��ظ����ʵ�����
		}
		token = strtok_s(NULL, DELIMS, &context);	//�������ϴηָ��λ�ÿ�ʼ����ʣ����ַ�������ȡ��һ������
	}

}

int countWords(const char* text) {
	int count = 0;
	char buffer[TEXT_SIZE] = { 0 };

	strcpy_s(buffer, TEXT_SIZE, text);

	char* context = NULL;									//strtok_s ������Ҫһ��������ָ�� context ����¼�ָ��λ�ã���ʼ��Ϊ NULL

	char* token = strtok_s(buffer, DELIMS, &context);		//��һ�ε��� strtok_s �������� buffer �зָ����һ�����ʡ�strtok_s ��� buffer �в��ҵ�һ���ָ��������ָ���֮ǰ�Ĳ�����Ϊһ�����ʷ��أ������� context ָ���¼��ǰ�ָ�λ�á�����ҵ��˵��ʣ�token ָ��õ��ʵ���ʼ��ַ����δ�ҵ���token Ϊ NULL

	//ֻҪ token ��Ϊ NULL���ͱ�ʾ���е���δ����
	while (token != NULL) {
		count++;											//ÿ�ָ��һ�����ʣ������� count �� 1
		token = strtok_s(NULL, DELIMS, &context);			//�������� strtok_s ʱ����һ���������� NULL����ʾ�������ϴηָ��λ�ÿ�ʼ����ʣ����ַ���

		//ΪʲôҪ����NULL��
		//strtok_s�������ڲ�ά����һ��״̬�����ڼ�¼�ϴηָ��λ�á�����һ�ε���strtok_sʱ����Ҫ����Ҫ�ָ���ַ�����������������ַ����в��ҷָ����������ҵ��ĵ�һ�����ַ����������ʣ����أ�ͬʱ��¼�·ָ��λ�á���������ʱ����NULL���Ǹ��ߺ����������ϴμ�¼��λ�ÿ�ʼ������һ���ָ�������ʵ�ֶ������ַ����������ָ���������NULL�������ٴδ���ԭʼ�ַ�������ôÿ�ζ�����ַ����Ŀ�ͷ���¿�ʼ�ָ�޷��ﵽ��˳�������ȡ���ʵ�Ŀ�ġ�
	}

	return count;
}

//����ĳ����ĸ���ֵĴ����������ַ���
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

//�����ַ������滻
void relpaceWord(const char* text, const char* oldWord, const char* newWord, char* result) {
	char buffer[TEXT_SIZE] = { 0 };				//������ʱ�洢����֮����ַ�����֮���Ƶ�result��

	const char* pos = text;						//ָ��ָ��ǰ���ڴ�����ַ���λ�ã���ʼʱָ�� text �Ŀ�ͷ

	const char* temp = text;					//temp ָ�����ڲ��� oldWord �� text �е�λ�ã���ʼʱҲָ�� text �Ŀ�ͷ

	size_t oldLen = strlen(oldWord);

	//ʹ�� strstr ������ pos ָ����ַ����в��� oldWord �ĵ�һ�γ���λ�ã���������洢�� temp �С�����ҵ��ˣ�temp ָ�� oldWord ����ʼλ�ã����û�ҵ���temp Ϊ NULL��ѭ��������
	while ((temp = strstr(pos, oldWord)) != NULL) {

		strncat_s(buffer, sizeof(buffer), pos, temp - pos);			//�� pos �� temp ֮����ַ���׷�ӵ� buffer �С�temp - pos ��ʾ�ⲿ���ַ����ĳ���

		strcat_s(buffer, sizeof(buffer), newWord);					//�� newWord ׷�ӵ� buffer �У����һ���滻

		pos = temp + oldLen;										//�� pos ָ���ƶ��� oldWord ֮���λ�ã�����������һ�� oldWord
	}

	strcat_s(buffer, sizeof(buffer), pos);							//�� pos ֮���ʣ���ַ���׷�ӵ� buffer ��

	strcpy_s(result, TEXT_SIZE, buffer);							//�� buffer �е��滻������Ƶ� result ��
}

int main(void)
{

	char text[TEXT_SIZE] = "This is a simple test. This test is for testing.";

	char replacedText[TEXT_SIZE] = { 0 };

	char oldWord[] = "test";

	char newWord[] = "example";

	char countCharTarget = 's';

	//�����洢һЩ���صĵ��ʣ��ÿո�ȥ��������ÿ�����ʴ�������ÿһ�У�
	char uniqueWords[TEXT_SIZE][WORD_SIZE] = { 0 };

	int uniqueCount = 0;

	relpaceWord(text, oldWord, newWord, replacedText);
	//�滻��ԭ���ı���Ҫ�滻�ĵ��ʣ��滻��ʲô�����滻֮����ı�װ���µ�����
	printf("Replaced Text: %s\n", replacedText);

	int charChout = countChar(replacedText, countCharTarget);
	printf("Character: '%c' appears %d times.\n", countCharTarget, charChout);

	int wordCount = countWords(replacedText);
	printf("Total number of words %d.\n", wordCount);

	extractUniqueWords(replacedText, uniqueWords, &uniqueCount);
	puts("Unique words: ");

	//��ά������һλ����ģ������������forѭ��ʱһ��һ�����ӵ�
	for (int i = 0; i < uniqueCount; i++) {
		printf("%s\n", uniqueWords[i]);
	}

	return 0;
}