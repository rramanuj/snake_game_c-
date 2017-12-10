#include "GridItem.h"
GridItem::GridItem(const char& symbol) : symbol(symbol) {}
char GridItem::get_symbol() const {
	return symbol;
}