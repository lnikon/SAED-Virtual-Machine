#ifndef _Ram_h_
#define _Ram_h_

class CRam
{
public:
	CRam(); // default capacity = 4096;
	CRam(unsigned int capacity);
	~CRam();

	unsigned int getIP();
	void setIP(unsigned int newIP);

	unsigned char& operator[](unsigned int position);

	unsigned int getSize();
		
private:
	unsigned int m_uiSize;
	unsigned int m_uiIP;
	unsigned char* m_ucMemory;
};

#endif // !_Ram_h_
