/* 
 * QR Code generator library (C++)
 * 
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include "BitBuffer.hpp"


namespace qrcodegen {

BitBuffer::BitBuffer()
	: std::vector<bool>() {}


std::vector<std::uint8_t> BitBuffer::getBytes() const {
	std::vector<std::uint8_t> result(size() / 8 + (size() % 8 == 0 ? 0 : 1));
	for (std::size_t i = 0; i < size(); i++)
		result[i >> 3] |= (*this)[i] ? 1 << (7 - (i & 7)) : 0;
	return result;
}


void BitBuffer::appendBits(std::uint32_t val, int len) {
#ifndef __ICCARM__
	if (len < 0 || len > 31 || val >> len != 0)
		throw "Value out of range";
#endif
	for (int i = len - 1; i >= 0; i--)  // Append bit by bit
		this->push_back(((val >> i) & 1) != 0);
}

}
