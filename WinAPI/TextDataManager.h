#pragma once
#include "SingletonBase.h"
/*
FILE* file;
#include <fstream>
���Ͽ� ������....��Ŭ��� h�� ���°� ���� C��.
//Text-���⽱���� �������, XML,
//INI-���Ӽ� ���ֺ����ϴ°���־��� �ɼǰ�����
//JSON-�ڹٵ����ڹٽ�ũ��Ʈ������Ʈ������Ʈ,
//����� ���þ��̵�

�ð���� �ؽ�Ʈ�� �Ұ���
*/
#define SAVE_BUFFER 128
#define LOAD_BUFFER 128
class TextDataManager : public SingletonBase<TextDataManager>
{
public:
    HRESULT init(void);
    void release(void);

    void save(const char* fileName, vector<string>vStr);
    char* vectorArrayCombine(vector<string> vArray);
    vector<string> load(const char* fileName);
    vector<string> charArraySeparation(char charArray[]);
public:
    TextDataManager() {}
    ~TextDataManager() {}
};

