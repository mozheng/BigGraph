#pragma once
/*
	����һ���º�����������Ĭ��hash������
	Ĭ�ϵ�ҪС�ںſ��ã�������ʱ��Ҫ��������С�ں�
*/
template<class _T >
class HashFunc
{
public:
	int operator()(const _T & key)
	{
		long key_address= (long)&key;//������Ϊkey��������Σ���ַ����Ψһ�ģ�����������hash��á���������ʲô��һ��ȥ��
									 //��Ϊ��������ԭ�����Ǽ��з����ڴ棬���Խ���ʹ��ʱֱ�ӽ�ȡ��Ϊ�˼��ݽ�long�س�int
		/*
		|�����ڴ�|
		|		| <-key ��ʼ����	
		|		|
		|		|
		*/
		return (int)(key_address);
	}
};