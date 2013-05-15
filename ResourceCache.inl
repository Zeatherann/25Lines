namespace _3de{

template<typename T>ResourceCache<T>::ResourceCache():Cache(){}

template<typename T>ResourceCache<T>::~ResourceCache(){
    Cache.clear();
}
template<typename T>T& ResourceCache<T>::New(std::string File){
    if(!Cache.count(File)){
        if(!Cache[File].loadFromFile(File.c_str())){
            cerr << "Failed to load Resource: \'"+File+"\'";
            exit(FAILED_TO_LOAD_RESOURCE);
        }
    }
    return Cache[File];
}

template<typename T>void ResourceCache<T>::Delete(std::string Key){
    Cache.erase(Key);
}

template<typename T>T& ResourceCache<T>::operator[](std::string Key){
    return Cache[Key];
}

}
