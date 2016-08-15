#pragma once
//这是质数集合，尽量找两者之间为2倍关系的质数
//在hashtable里面，因为群论同余问题，所以需要互质。最好是2倍关系
//数据来自网上
#define PRIMENUM 28
extern int Prime[PRIMENUM] =
{
	57,        97,         193,        389,        769,
	1543,      3079,       6151,       12289,      24593,
	49157,     98317,      196613,     393241,     786433,
	1572869,   3145739,    6291469,    12582917,   25165843,
	50331653,  100663319,  201326611,  402653189,  805306457,
	1610612741
};
//获得素数表中下一个大于num的素数，最大不能超过1610612741
extern int GetNextPrime(int num)
{
	for (int i=0; i < PRIMENUM; ++i)
		if (num > Prime[i])
			return Prime[i];
	return Prime[PRIMENUM-1];
}