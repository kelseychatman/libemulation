
/**
 * libemulator
 * Package class
 * (C) 2009-2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Type for accessing DML packages (zip and directory type)
 */

#include <fstream>
#include <sys/stat.h>

#include "OEPackage.h"

OEPackage::OEPackage(string packagePath)
{
	this->packagePath = packagePath;
	zip = NULL;
	
	
	// To-Do: Make platform independent
	struct stat statbuf;
	bool isPathCreated = (stat(packagePath.c_str(), &statbuf) == 0);
	
	bool isPackage;
	if (isPathCreated)
		isPackage = (statbuf.st_mode & S_IFDIR);
	else
		isPackage = (packagePath.substr(packagePath.size() - 1, 1) == "/");
	
	if (isPackage)
	{
		mkdir(packagePath.c_str(), 0777);
		open = (stat(packagePath.c_str(), &statbuf) == 0);
	}
	else
	{
		zip = zip_open(packagePath.c_str(), ZIP_CREATE, NULL);
		open = (zip != NULL);
	}
}

OEPackage::~OEPackage()
{
	if (zip)
		zip_close(zip);
	
	zip = NULL;
}

bool OEPackage::isOpen()
{
	return open;
}

bool OEPackage::readFile(string localPath, vector<char> &data)
{
	bool error = true;
	
	if (!open)
		return false;
	
	if (zip)
	{
		struct zip_stat zipStat;
		struct zip_file *zipFile;
		
		if (zip_stat(zip, (const char *) localPath.c_str(), 0, &zipStat) == 0)
		{
			if ((zipFile = zip_fopen(zip, localPath.c_str(), 0)) != NULL)
			{
				data.resize(zipStat.size);
				error = (zip_fread(zipFile, &data[0], zipStat.size) != zipStat.size);
				zip_fclose(zipFile);
			}
		}
	}
	else
	{
		ifstream file((packagePath + PACKAGE_PATH_SEPARATOR + localPath).c_str());
		
		if (file.is_open())
		{
			file.seekg(0, ios::end);
			int size = file.tellg();
			file.seekg(0, ios::beg);
			
			data.resize(size);
			file.read(&data[0], size);
			
			error = !file.good();
			
			file.close();
		}
	}
	
	return !error;
}

bool OEPackage::writeFile(string localPath, vector<char> &data)
{
	bool error = true;
	
	if (!open)
		return false;
	
	if (zip)
	{
		struct zip_source *zipSource = NULL;
		
		if ((zipSource = zip_source_buffer(zip, &data[0], data.size(), 0)) != NULL)
		{
			int index;
			if ((index = zip_name_locate(zip, localPath.c_str(), 0)) == -1)
				error = (zip_add(zip, localPath.c_str(), zipSource) == -1);
			else
				error = (zip_replace(zip, index, zipSource) == -1);
			
			zip_source_free(zipSource);
		}
	}
	else
	{
		ofstream file((packagePath + PACKAGE_PATH_SEPARATOR + localPath).c_str());
		
		if (file.is_open())
		{
			file.write(&data[0], data.size());
			error = !file.good();
			file.close();
		}
	}
	
	return !error;
}

bool OEPackage::remove()
{
	// To-Do: Remove

	return true;
}