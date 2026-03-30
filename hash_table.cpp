#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<class Key, class Data>
class hash_table
{
private:
    vector<list<pair<Key, Data>>> vec;
public:
    hash_table()
    {
        vec.resize(16);
    }
    virtual ~hash_table() 
    {
        for (auto& v : vec)
        {
            v.clear();
        }
    }
    void add(const Key& key, const Data& data)
    {
        vec[hash<Key>{}(key) % 16].push_back({ key, data });
    }
    Data get(const Key& key) const
    {
        for (auto& v : vec[hash<Key>{}(key) % 16])
        {
            if (v.first == key)
                return v.second;
        }
        return 0;

    }
    Data& operator[](const Key& key)
    {
        for (auto& v : vec[hash<Key>{}(key) % 16])
        {
            if (v.first == key)
                return v.second;
        }
        vec[hash<Key>{}(key) % 16].push_back({ key,Data() });
        return vec[hash<Key>{}(key) % 16].back().second;
    }
    bool find(const Key& key) const
    {
        for (const auto& v : vec[hash<Key>{}(key) % 16])
        {
            if (v.first == key)
                return true;
        }
        return false;
    }
    void clear()
    {
        for (auto& v : vec)
        {
            v.clear();
        }
    }
    void remove(const Key& key)
    {
        for (auto &&it = vec[hash<Key>{}(key) % 16].begin(); it != vec[hash<Key>{}(key) % 16].end();)
        {
            if (it->first == key)
            {
                vec[hash<Key>{}(key) % 16].erase(it);
                return;
            }
            else
            {
                ++it;
            }
        }
    }
};
