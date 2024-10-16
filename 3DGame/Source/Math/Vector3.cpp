#include"Vector3.h"

using namespace std;

const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);

Vector3::Vector3(){}

Vector3::Vector3(float x_, float y_, float z_) {
	x = x_;
	y = y_;
	z = z_;
}

Vector3::Vector3(VECTOR vector_) {
	x = vector_.x;
	y = vector_.y;
	z = vector_.z;
}

//内積処理
float Vector3::Dot(Vector3 vec_01, Vector3 vec_02) {
	return (vec_01.x * vec_02.x) + (vec_01.y * vec_02.y) + (vec_01.z * vec_02.z);
}

//外積処理
Vector3 Vector3::Cross(Vector3 vec_01, Vector3 vec_02) {
	return Vector3((vec_01.y * vec_02.z) - (vec_01.z * vec_02.y),//X成分
				  (vec_01.z * vec_02.x) - (vec_01.x * vec_02.z),//Y線分
				  (vec_01.x * vec_02.y) - (vec_01.y * vec_02.x)	//Z成分
					);
}

Vector3 Vector3::Normalized() const {
	float size = getSize();
	return Vector3(x / size, y / size, z / size);
}

Vector3 Vector3::operator+(const Vector3& other_) const{
	return Vector3(x + other_.x, y + other_.y, z + other_.z);
}

Vector3 Vector3::operator-(const Vector3& other_) const{
	return Vector3(x - other_.x, y - other_.y, z - other_.z);
}

Vector3 Vector3::operator*(float value_) const{
	return Vector3(x * value_, y * value_, z * value_);
}

Vector3 Vector3::operator/(float value_) const{
	return Vector3(x / value_, y / value_, z / value_);
}

Vector3& Vector3::operator +=(const Vector3& other_) {
	x += other_.x;
	y += other_.y;
	z += other_.z;
	return *this;
}
Vector3& Vector3::operator -=(const Vector3& other_) {
	x -= other_.x;
	y -= other_.y;
	z -= other_.z;
	return *this;
}

//加算の演算子オーバーロード(二項演算子)
Vector3& Vector3::operator *=(float value_) {
	x *= value_;
	y *= value_;
	z *= value_;
	return *this;
}

//減算の演算子オーバーロード(二項演算子)
Vector3& Vector3::operator /=(float value_) {
	x /= value_;
	y /= value_;
	z /= value_;
	return *this;
}

//等式の演算子オーバーロード
bool Vector3::operator ==(const Vector3& other_) {
	return (x == other_.x && y == other_.y && z == other_.z);
}

//不等式の演算子オーバーロード
bool Vector3::operator !=(const Vector3& other_) {
	return (x != other_.x || y != other_.y || z != other_.z);
}

//ライブラリのベクトルクラスにキャスト
Vector3::operator VECTOR() const {
	return VGet(x, y, z);
}