#include <iostream>
#include <map>

using namespace std;

const int BucketsSize = 7;

int hashKey(int key)
{
	if (key < 0)
		return -key;
	return key;
}
int hashKey(const string& key)
{
	int hash = 0;
	for (char c : key)
		hash += c;
	return hash;
}
int hashKey(char key)
{
	return (int)key;
}


template<class T, class K>
class Hashing
{
public:

	void insert(T key, K value)
	{
		int hash = hashKey(key);
		if(Buckets[hash % BucketsSize].insert({ key,value }).second)
			sizeB++;
	}

	K& at(const T& key)
	{
		int hash = hashKey(key);
		return Buckets[hash % BucketsSize].at(key);
	}

	K& operator[](const T& key)
	{
		int hash = hashKey(key);
		return Buckets[hash % BucketsSize][key];
	}

	void erase(const T& key)
	{
		int hash = hashKey(key);
		sizeB -= Buckets[hash % BucketsSize].erase(key);
	}

	void clear()
	{
		for (auto& m : Buckets)
			m.clear();
		sizeB = 0;
	}

	void show()
	{
		cout << "> ======================" << endl;
		for (const auto& m : Buckets)
		{
			cout << "[";
			for (const auto& p : m)
				cout << " { " << p.first << ", " << p.second << " }; ";
			cout << "]";
			cout << endl;
		}
		cout << "< ======================" << endl;
	}

	int size()
	{
		return sizeB;
	}

private:
	map<T, K> Buckets[BucketsSize] = {};
	int sizeB = 0;
};

void testInt()
{
	Hashing <int, int> h;
	cout << "int, int" << endl;

	h.insert(5, 8);
	h.insert(32, 7);
	h.insert(8, 4);
	h.insert(-6, 30);
	h.insert(13, 12);
	h.insert(121, 11);
	h.insert(79, 5);
	h[5] = 3;
	h.show();

	h.erase(5);
	h.show();

	h.clear();
	h.show();
}

void testStr()
{
	Hashing <string, string> tea;
	cout << "\nstring, string" << endl;
	tea.insert("Bai Hao Yinzhen", "white tea");
	tea.insert("Jasmine", "green tea");
	tea.insert("Earl grey", "black tea");
	tea.insert("Karkade", "red tea");
	tea.show();
	cout << "Jasmine is " << tea.at("Jasmine");
}

int main()
{
	testInt();
	testStr();
}