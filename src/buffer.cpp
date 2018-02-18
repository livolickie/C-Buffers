#include "buffer.h"

Buffer::Buffer(int sz)
{
	size = sz;
	pos = new char[sz];
	start = pos;
}

template <typename T> void Buffer::write(T val)
{
	if ((sizeof(T) + (pos - start)) <= size)
	{
		*(T *)pos = val;
		pos += sizeof(T);
	}
	else
	{
		int last_b = pos - start;
		pos = new char[size + sizeof(T)];
		memcpy(pos, start, last_b);
		delete start;
		start = pos;
		pos += last_b;
		size += sizeof(T);
		*(T *)pos = val;
		pos += sizeof(T);
	}
}

template <typename T> T Buffer::read()
{
	T r = *(T *)pos;
	pos += sizeof(T);
	return r;
}

void Buffer::write_string(char * val)
{
	for (int i = 0; val[i] != '\0'; i++)
		write<char>(val[i]);
	write<char>('\0');
}

char * Buffer::read_string()
{
	char * r = pos;
	while (*pos != '\0')
		pos++;
	pos++;
	return r;
}

void Buffer::seek()
{
	pos = start;
}

void Buffer::seek(int bytes)
{
	pos += bytes;
}

void Buffer::clear()
{
	delete start;
	pos = new char[size];
	start = pos;
}

void Buffer::resize(int new_s)
{
	size = new_s;
	delete start;
	pos = new char[new_s];
	start = pos;
}

void Buffer::destroy()
{
	pos = start;
	delete start;
}

void Buffer::live(int sz)
{
	size = sz;
	pos = new char[sz];
	start = pos;
}

void Buffer::copy(Buffer * b1, Buffer * b2, int sz, int ofs)
{
	b2->pos += ofs;
	if (sz + (b2->pos - b2->start) <= b2->size)
	{
		memcpy(b2->pos, b1->start, sz);
		b2->pos += sz;
	}
	else
	{
		int last_b = b2->pos - b2->start;
		b2->pos = new char[b2->size + (sz + last_b - b2->size)];
		memcpy(b2->pos, b2->start, b2->size);
		b2->size += (last_b + sz - b2->size);
		delete b2->start;
		b2->start = b2->pos;
		b2->pos += last_b;
		memcpy(b2->pos, b1->start, sz);
		b2->pos += sz;
	}
}

void Buffer::save(char * dir)
{
	std::ofstream fl;
	fl.open(dir, std::ios_base::binary);
	fl.write(start, size);
	fl.close();
}

void Buffer::load(char * dir)
{
	std::ifstream fl;
	fl.open(dir, std::ios_base::binary);
	fl.seekg(0, std::ios_base::end);
	int sz = fl.tellg();
	fl.seekg(0, 0);
	int last_byte = pos - start;
	if (sz + last_byte <= size)
	{
		fl.read(pos, sz);
		fl.close();
		pos += sz;
	}
	else
	{
		pos = new char[size + (sz + last_byte - size)];
		memcpy(pos, start, last_byte);
		delete start;
		start = pos;
		pos += last_byte;
		size += (sz + last_byte - size);
		fl.read(pos, sz);
		fl.close();
		pos += sz;
	}
}

char * Buffer::sha()
{
	return (char *)sha512(std::string(start,pos)).c_str();
}

int Buffer::tell()
{
	return pos - start;
}

int Buffer::memory()
{
	return size;
}