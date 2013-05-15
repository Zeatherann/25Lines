#ifndef RESOURCECACHE_HPP
#define RESOURCECACHE_HPP

namespace _3de{
template<typename T>class ResourceCache{
public:
	///Variables
	std::map<std::string,T> Cache;
	///Constructors
	ResourceCache();
	///Destructors
	~ResourceCache();
	///Functions
	T& New(std::string File);
	void Delete(std::string Key);
	///Operators
	T& operator[](std::string key);
};

}
#include "ResourceCache.inl"
#endif // RESOURCECACHE_HPP
