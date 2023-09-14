#include "UtilFunctions.h"

void UtilFunctions::colour(const char* colour) {
	//yandereDev code time >:)
	if (colour == "red") {
		std::cout << "\033[31m"; }
	if (colour == "blue") {
		std::cout << "\033[34m"; }
	if (colour == "green") {
		std::cout << "\033[32m"; }
	if (colour == "purple") {
		std::cout << "\033[35m"; }
	if (colour == "cyan") {
		std::cout << "\033[36m"; }
	if (colour == "yellow") {
		std::cout << "\033[33m"; }

	if (colour == "clear") {
		std::cout << "\033[0m"; }
	}
