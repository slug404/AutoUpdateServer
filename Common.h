#ifndef COMMON_H
#define COMMON_H

#include <QString>

struct FileInfor
{
	bool operator < (const FileInfor &other) const
	{
		if(fileName < other.fileName)
		{
			return true;
		}
		else if(fileName == other.fileName)
		{
			if(filePath < other.filePath)
			{
			   return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	QString fileName;
	QString filePath;
};

#endif // COMMON_H
