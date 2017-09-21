#ifndef _Ram_h_
#define _Ram_h_

class CRam
{
public:
	CRam(unsigned int size);
	~CRam();

	unsigned int getIP();
	void setIP(unsigned int newIP);

	unsigned char& operator[](unsigned int position);
	
	unsigned int getSize();
	void resize(unsigned int size); 
	void reserve(unsigned int size);

private:
	unsigned int m_uiSize;
	unsigned int m_uiIP;
	unsigned char* m_ucMemory;
};

#endif // !_Ram_h_
