#pragma once
class GridItem {
public:
	GridItem(const char& symbol);
	char get_symbol() const;
private:
	const char symbol;
};