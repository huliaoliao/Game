#ifndef					__POKER_SET_TYPE_H__
#define					__POKER_SET_TYPE_H__

/*	���漯�ϵ�����	2017.6.10
*/

enum PokersType
{
	NONE,			//ʲô������
	SINGLE,			//����
	PAIR,				//����
	TRIPLE,			//����
	TRIPLEWITHSINGLE,		//����һ
	TRIPLEWITHPAIR,			//������
	BOMB,			//ը��
	KINGBOMB,	//��ը
	STRAIGHT,	//˳��
	PAIRSTRAIGHT,				//˫˳
	TRIPLESTRAIGHT,			//��˳
	TRIPLESTRAIGHTWITHSINGLE,				//��˳��һ
	TRIPLESTRAIGHTWITHPAIR					//��˳����
};

#endif