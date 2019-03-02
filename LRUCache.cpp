#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <list>
#include <unordered_map>

//双向链表的结点, 作为页面
struct Node 
{
    Node(int k, int v)
        : key(k), val(v)
    {}
    int key;
    int val;
};

class LRUCache 
{
public:
    LRUCache(int c) 
        : capacity(c) 
    {}
    int get(int k)
    {
        if (cacheMap.begin() == cacheMap.end()) //内存中没有页面, 这时需要调用set插入页面
            return -1;
        
        //将该页面移到链表头
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[k]);
        //更新,存储链表头结点
        cacheMap[k] = cacheList.begin();
        return cacheMap[k]->val;
    }
    void set(int k, int v) 
    {
        //内存中没有该页
        if (cacheMap.find(k) == cacheMap.end())
        {
            //满了,删除尾结点
            if (cacheList.size() == capacity) 
            {
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            //插入到链表头,更新哈希表
            cacheList.push_front(Node(k, v));
            cacheMap[k] = cacheList.begin();
        }
        else //内存中有该页,就更新他的值并移到链表头
        {
            cacheMap[k]->val = v;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[k]);
            cacheMap[k] = cacheList.begin();
        }   
    }
private:
    int capacity;   //规定一个链表大小
    std::list<Node> cacheList;  //双向链表
    std::unordered_map<int, std::list<Node>::iterator> cacheMap;//存储链表结点和结点位置对应关系,实现O1时间复杂度
};


#endif