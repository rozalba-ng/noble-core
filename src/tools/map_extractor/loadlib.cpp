/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define _CRT_SECURE_NO_DEPRECATE

#include "loadlib.h"
#include "mpq_libmpq04.h"
#include <cstdio>

class MPQFile;

u_map_fcc MverMagic = { {'R','E','V','M'} };

FileLoader::FileLoader()
{
    data = 0;
    data_size = 0;
    version = 0;
}

FileLoader::~FileLoader()
{
    free();
}

bool FileLoader::loadFile(std::string const& fileName, bool log)
{
    free();
    MPQFile mf(fileName.c_str());
	printf("1");
    if(mf.isEof())
    {
		printf("2");
        if (log)
            printf("No such file %s\n", fileName.c_str());
        return false;
    }
	printf("3");
    data_size = mf.getSize();
	printf("4");
    data = new uint8 [data_size];
	printf("5");
    mf.read(data, data_size);
	printf("6");
    mf.close();
	printf("7 ");	
	if (prepareLoadedData() == true) {
		printf("8");
		return true;
	}
	if (fileName.find("AlteracValley") != std::string::npos)
	{
		printf("8.0");
		return true;
	}
	printf(" 9");
    printf("Error loading %s", fileName.c_str());
    mf.close();
    free();
    return false;
}

bool FileLoader::prepareLoadedData()
{
    // Check version
	printf(" ODIN ");
    version = (file_MVER *) data;
	printf(" DVA %u", version->ver);
	if (version->fcc != MverMagic.fcc) {
		printf(" TRI ");
		printf("Wrong MVER");
		return false;
	}
	if (version->ver != FILE_FORMAT_VERSION) {
		printf(" CHETIRE ");
		printf("Wrong MVER 2");
		return false;
	}
	printf(" PYAT ");
    return true;
}

void FileLoader::free()
{
    if (data) delete[] data;
    data = 0;
    data_size = 0;
    version = 0;
}
