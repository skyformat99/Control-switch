#ifndef __SIGNAL_STREAM
#define __SIGNAL_STREAM


//��SignalStreamʵ�ֵľ�ֵ�˲���
template<int filterWindow>
class AverageFilter :public SignalStream<float, filterWindow>
{
public:
	float getFilterOut(float newNum)
	{
		push(newNum);
		float temp = 0;
		for (int i = 0; i < filterWindow; i++)
		{
			temp += operator[](i);
		}
		temp /= filterWindow;
		return temp;
	}
};


//��circle bufferʵ�ֵ������źŴ�����
//�����źŴ洢��ͨ���̳л�ʵ����ʵ���źŴ�������
//ע��ģ����ĺ���ʵ�ֱ���д��ͷ�ļ���
template<typename T, int Size>
class SignalStream
{
	int indexHead;
public:
	T buf[Size];

	//��ʼ��bufΪ0
	SignalStream();

	//���bufΪ0
	void clear();

	//����buf�ĳ���
	int size();

	//ѹ�����µ����ݲ�������ɵ�����
	void push(T signal);

	//����[]����������0��ʼΪ���µ��ɵ�����
	T &operator [](int index);
};

template<typename T, int Size>
SignalStream<T, Size>::SignalStream() :
	indexHead(0)
{
	clear();
}

template<typename T, int Size>
void SignalStream<T, Size>::clear()
{
	for (int i = 0; i < Size; i++)
	{
		buf[i] = 0;
	}
}

template<typename T, int Size>
int SignalStream<T, Size>::size()
{
	return Size;
}

template<typename T, int Size>
void SignalStream<T, Size>::push(T signal)
{
	indexHead--;
	indexHead %= Size;
	if (indexHead < 0)
	{
		indexHead += Size;
	}
	buf[indexHead] = signal;
}

template<typename T, int Size>
T & SignalStream<T, Size>::operator[](int index)
{
	return buf[(index + indexHead) % Size];
}

#endif