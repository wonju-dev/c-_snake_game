#pragma once

struct Point {
public:
	int x;
	int y;
public:
	Point(int column = 0, int row = 0) : x(column), y(row) {}
public:
	bool operator==(const Point& other) const {
		return (x == other.x) && (y == other.y);
	}
	bool operator<(const Point& other) const {
		if (x < other.x) {
			return true;
		}
		else if (x == other.x) {
			return y >= other.y;
		}
		return false;
	}
};
