#include"Vector2.h"

using namespace std;

//ゼロベクトル
const Vector2 Vector2::ZERO = Vector2(0, 0);

//コンストラクタ
Vector2::Vector2() {}

//コンストラクタ
Vector2::Vector2(int x_, int y_) {
	x = x_;
	y = y_;
}

//コンストラクタ
Vector2::Vector2(float x_, float y_) {
	x = static_cast<int>(x_);
	y = static_cast<int>(y_);
}

//コンストラクタ
Vector2::Vector2(VECTOR vector_) {
	x = static_cast<int>(vector_.x);
	y = static_cast<int>(vector_.y);
}

//内積処理
float Vector2::Dot(Vector2 vec_01, Vector2 vec_02) {
	return static_cast<float>((vec_01.x * vec_02.x) + (vec_01.y * vec_02.y));
}

//外積処理
float Vector2::Cross(Vector2 vec_01, Vector2 vec_02) {
	return static_cast<float>((vec_01.x * vec_02.y) - (vec_01.y * vec_02.x));
}

//サイズを返す
int Vector2::getSize() const {
	float vecX = static_cast<float>(x);
	float vecY = static_cast<float>(y);
	return static_cast<int>(sqrtf(vecX * vecX + vecY * vecY));
}

//正規化処理
Vector2 Vector2::Normalized() const {
	int size = getSize();
	return Vector2(x / size, y / size);
}

//加算の演算子オーバーロード
Vector2 Vector2::operator+(const Vector2& other_) const {
	return Vector2(x + other_.x, y + other_.y);
}

//減算の演算子オーバーロード
Vector2 Vector2::operator-(const Vector2& other) const {
	return Vector2(x - other.x, y - other.y);
}

//乗算の演算子オーバーロード
Vector2 Vector2::operator*(int value) const {
	return Vector2(x * value, y * value);
}

//除算の演算子オーバーロード
Vector2 Vector2::operator/(int value) const {
	return Vector2(x / value, y / value);
}

//加算の演算子オーバーロード(二項演算子)
Vector2& Vector2::operator +=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

//加算の演算子オーバーロード(二項演算子)
Vector2& Vector2::operator -=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

//等式の演算子オーバーロード
bool Vector2::operator ==(const Vector2& other) {
	return (x == other.x && y == other.y);
}

//不等式の演算子オーバーロード
bool Vector2::operator !=(const Vector2& other) {
	return (x != other.x || y != other.y);
}

//ライブラリが用意したベクトルクラスにキャスト
Vector2::operator VECTOR() {
	return VGet(static_cast<float>(x), static_cast<float>(y), 0.0f);
}
