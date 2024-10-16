#include "StateBase.h"
#include "..\Player\Soldier.h"
#include "..\Enemy\Mutant.h"
#include "..\Enemy\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class StateBase<Soldier>;
template class StateBase<Mutant>;
template class StateBase<Magician>;

template<class Object>
//�R���X�g���N�^
StateBase<Object>::StateBase(Object* holder_) {
	holder = holder_;//�X�e�[�g��ێ����Ă���I�u�W�F�N�g�̃|�C���^��ۑ�
	holderPosition = holder->getPosition();
	holderAngle = holder->getAngle();//�����Ă���p�x���擾
}

template<class Object>
//�f�X�g���N�^
StateBase<Object>::~StateBase() {}