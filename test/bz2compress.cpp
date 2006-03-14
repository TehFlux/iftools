/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * bz2compress.cpp                  Bzip2 compression test.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <iostream>
#include <string>
#include "ionflux/tools.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please specify an input file!" << endl;
		return 0;
	}
	string inputFile = argv[1];
	string original = readFile(inputFile);
	string compressed;
	string decompressed;
	if (original == "")
	{
		cout << "No input data, finished." << endl;
		return 0;
	}
	bz2Compress(original, compressed);
	if (compressed != "")
	{
		cout << "Writing compressed file... ";
		writeFile("test.compressed", compressed, 0);
		cout << "done." << endl;
		bz2Decompress(compressed, decompressed);
		if (decompressed != "")
		{
			cout << "Writing decompressed file... ";
			writeFile("test.decompressed", decompressed, 0);
			cout << "done." << endl;
			cout << "SHA-1 of original file:     " << makeHex(sha1(original)) 
				<< endl;
			cout << "SHA-1 of decompressed file: " 
				<< makeHex(sha1(decompressed)) << endl;
			if (sha1(original) == sha1(decompressed))
				cout << "Compression appears to work! :-)" << endl;
			else
				cout << "Compression doesn't work. :-(" << endl;
		} else
			cout << "Decompression failed." << endl;
	} else
		cout << "Compression failed." << endl;
	return 0;
}

/** \file bz2compress.cpp
 * \brief Bzip2 compression test.
 */
