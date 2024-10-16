#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "..\Player\Soldier.h"

//テンプレートコンストラクタを実体化
template class MoveState<Soldier>;

//static定数定義
template<class Object>
const float MoveState<Object>::MOVE_SPEED = 1.0f;	//移動速度
template<class Object>
const float MoveState<Object>::JUMP_POWER = 10.0f;	//ジャンプ時の初速
template<class Object>
const float MoveState<Object>::AVOID_SPEED = 5.0f;	//回避時の速度

//コンストラクタ
template<class Object>
MoveState<Object>::MoveState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Move";
	isRun = false;
}

//デストラクタ
template<class Object>
MoveState<Object>::~MoveState() {}

//更新処理
template<class Object>
StateBase<Object>* MoveState<Object>::Run() {
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		this->animationName = "Run";
		isRun = true;
	}
	
	Vector3 addVector = Move() + Jump() + Avoid();

	//modelの原点座標は当たり判定の底なので、高さ分を足して代入
	Vector3 position = this->holder->getPosition();
	Vector3 centerPosition = Vector3(position.x, position.y, position.z);

	this->holderPosition = centerPosition + addVector;

	//何も操作が無ければIdleStateに遷移
	if (!isMove && !isJump && !isAvoid) {
		Object* holderAddress = this->holder;
		delete this;
		return new IdleState<Object>(holderAddress);
	}
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//左クリックでAttackStateに遷移
		Object* holderAddress = this->holder;
		delete this;
		return new AttackState<Object>(holderAddress);
	}

	return this;
}

//移動処理
template<class Object>
Vector3 MoveState<Object>::Move() {
	moveVector = Vector3::ZERO;
	isMove = false;

	//回避中は移動出来ない
	if (!isAvoid) {
		if (CheckHitKey(KEY_INPUT_W)) {
			moveVector += this->holder->getFrontDirection() * MOVE_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			moveVector += Vector3(Matrix::GetRotateMatrix(Vector3(0.0f, DX_PI_F, 0.0f)) * this->holder->getFrontDirection());
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			moveVector += Vector3(Matrix::GetRotateMatrix(Vector3(0.0f, -DX_PI_F / 2, 0.0f)) * this->holder->getFrontDirection());
		}
		if (CheckHitKey(KEY_INPUT_D)) {
			moveVector += Vector3(Matrix::GetRotateMatrix(Vector3(0.0f, DX_PI_F / 2, 0.0f)) * this->holder->getFrontDirection());
		}
	}

	if (moveVector != Vector3::ZERO) {
		isMove = true;
		Rotate();
	}
	
	float speed = isRun ? MOVE_SPEED * 3.0f : MOVE_SPEED;

	return moveVector * speed;
}

//ジャンプ処理
template<class Object>
Vector3 MoveState<Object>::Jump() {

	//着地したらジャンプ処理を終了
	if (this->holder->IsGround() && isJump) {
		jumpVector = Vector3::ZERO;
		this->animationName = "Move";
		isJump = false;
	}
	//LeftShiftキーでジャンプ処理を実行
	if (CheckHitKey(KEY_INPUT_SPACE) && !isJump) {
		this->animationName = "Jump";
		jumpVector.y += JUMP_POWER;
		isJump = true;
	}

	//重力処理
	if (isJump) {
		//ジャンプは上まで飛んだあと地面に折り返すため尺の半分は下方向になるように減速する力は二倍にしている
		jumpVector.y -= (JUMP_POWER / this->holder->getTotalAnimationTime()) * 2.0f;
	}

	return jumpVector;
}

//回避処理
template<class Object>
Vector3 MoveState<Object>::Avoid() {
	//
	if (GetMouseInput() & MOUSE_INPUT_RIGHT && !isAvoid) {
		isAvoid = true;
		this->animationName = "Avoid";
		if (moveVector == Vector3::ZERO) {
			avoidVector += this->holder->getFrontDirection() * AVOID_SPEED;
		}
		else {
			avoidVector += moveVector.Normalized() * AVOID_SPEED;
		}
	}
	if (isAvoid) {
		Vector3 direction = avoidVector.Normalized();
		avoidVector -= (direction * AVOID_SPEED) / this->holder->getTotalAnimationTime();

		//アニメーションが終了したら回避処理を終了
		if (this->holder->IsFinish()) {
			avoidVector = Vector3::ZERO;
			this->animationName = "Move";
			isAvoid = false;
		}	
	}

	return avoidVector;
}

//回転処理
template<class Object>
void MoveState<Object>::Rotate() {
	moveVector = moveVector.Normalized();
	this->holderAngle.y = GetAngleFromVector(moveVector);
}