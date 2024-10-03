#include "basicthing.h"

basicthing::basicthing(string _inpData)
{
	data = _inpData;
}
basicthing::~basicthing()
{

}
string basicthing::selfDraw()
{
	return data;
}