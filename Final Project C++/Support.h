#ifndef SUPPORT_H
#define SUPPORT_H

template<typename T> T max(T last) {
	return last;
}

template<typename T, typename... Args> T max(T first, Args... others) {
	T max_others = max(others...);
	return (max_others >= first) ? max_others : first;
}

template<typename T> T min(T last) {
	return last;
}
template<typename T, typename... Args> T min(T first, Args... others) {
	T min_others = min(others...);
	return (min_others <= first) ? min_others : first;
}

const std::string INVALID_SHIFT_ERROR = "ERROR: shift must be number";
const std::string AMBIGUOS_SHIFT_ERROR = "ERROR: shift must be passed as one or two numbers";
const std::string AMBIGUOUS_TRIANGLE_ERROR = "ERROR: triangle must be passed as six numbers";
const std::string AMBIGUOUS_RING_ERROR = "ERROR: ring must be passed as four numbers";
const std::string AMBIGUOUS_CENTER_ERROR = "ERROR: center must be passed as two numbers";
const std::string INVALID_INPUT = "ERROR: invalid input";

const std::string MOVE_OPTION_SHIFT = "k";
const std::string MOVE_OPTION_POINT = "point";

#endif