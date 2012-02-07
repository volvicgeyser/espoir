#pragma once

//２次元平面図上の位置を表すポイントクラス

template <class T>
struct Point_t{
	T x;
	T y;

	Point_t<T> operator + (const Point_t<T>& p) const{
		Point_t<T> result;
		result.x = this->x + p.x;
		result.y = this->y + p.y;
		return result;
	}
	
	Point_t<T> operator-(const Point_t<T>& p) const{
		Point_t<T> result;
		result.x = this->x - p.x;
		result.y = this->y - p.y;
		return result;
	}
	template<typename S>Point_t<T> operator*(const S s) const{
		Point_t<T> result;
		result.x  = result.x * s;
		result.y = result.y * s;
		return result;
	}
	template<typename S>Point_t<T> operator/(const S s) const{
		Point_t<T> result;
		result.x = result.x / s;
		result.y = result.y / s;
		return result;
	}
	void operator+=(const Point_t<T>& p){
		this->x = p.x + this->x;
		this->y = p.y + this->y;
	}
	void operator-=(const Point_t<T>& p){
		this->x = this->x - p.x;
		this->y = this->y - p.y;
	}
	template<typename S>void operator*=(S s){
		this->x = this->x * s;
		this->y = this->y * s;
	}
	template<typename S>void operator/=(S s){
		this->x = this->x * s;
		this->y = this->y * s;
	}
	void operator=(const Point_t<T>& p){
		this->x = p.x;
		this->y = p.y;
	}
	void Reset(){
		this->x = 0;
		this->y = 0;
	}
};

typedef Point_t<int> Point;
typedef Point_t<float> PointF;