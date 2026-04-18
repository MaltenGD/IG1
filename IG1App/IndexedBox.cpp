#include "IndexedBox.h"
#include "IndexMesh.h"

IndexedBox::IndexedBox(GLdouble length)
{
	mMesh = IndexMesh::generateIndexedBox(length);
}
