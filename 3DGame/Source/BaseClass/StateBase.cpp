#include "StateBase.h"
#include "..\Player\Soldier.h"
#include "..\Enemy\Mutant.h"
#include "..\Enemy\Magician.h"

//テンプレートコンストラクタを実体化
template class StateBase<Soldier>;
template class StateBase<Mutant>;
template class StateBase<Magician>;

template<class Object>
//コンストラクタ
StateBase<Object>::StateBase(Object* holder_) {
	holder = holder_;//ステートを保持しているオブジェクトのポインタを保存
	holderPosition = holder->getPosition();
	holderAngle = holder->getAngle();//向いている角度を取得
}

template<class Object>
//デストラクタ
StateBase<Object>::~StateBase() {}