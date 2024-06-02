#include "Util.h"

std::pair<int, int> operator+ (const std::pair<int, int>& l, const std::pair<int, int>& r) {
	return std::make_pair(l.first + r.first, l.second + r.second);
}

std::pair<int, int> operator+ (const std::pair<int, int>& l, const short& r) {
	assert(VK_LEFT <= r && r <= VK_DOWN && "Added non-directional key in positions");
	switch (r) {
	case VK_LEFT:
		return l + LEFT;
	case VK_UP:
		return l + UP;
	case VK_RIGHT:
		return l + RIGHT;
	case VK_DOWN:
		return l + DOWN;
	}
}

bool operator< (const std::pair<int, int>& l, const std::pair<int, int>& r) {
	return (l.first < r.first&& l.second < r.second);
}

void operator+= (std::pair<int, int>& l, const std::pair<int, int>& r) {
	l = l + r;
}

void operator+= (std::pair<int, int>& l, const short& r) {
	l = l + r;
}