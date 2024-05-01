#include "cache.h"
#include <sstream>

// TODO: 필요한 함수 구현

Cache::Cache() {}
Cache::~Cache() {}

// int를 cache에 추가한다, palindrome 의 경우
void Cache::add(std::string key, int value)
{
    if (cache_list_.size_ == CACHE_SIZE) // 꽉 차서 마지막 캐시 노드를 지우고 그것을 가리키는 해시 노드를 지운다
    {
        std::string last_cache_node_key = cache_list_.get_key(CACHE_SIZE - 1); // 마지막 캐시 노드의 키
        int hashed_key = hash(last_cache_node_key);                            // 해시 리스트 인덱스

        cache_list_.del_node(CACHE_SIZE - 1); // 캐시 노드 삭제 완료

        for (int i = 0; i < hash_map_lists_[hashed_key].size_; i++)
        {
            if (hash_map_lists_[hashed_key].get_key(i).find(last_cache_node_key) !=
                std::string::npos) // 마지막 캐시 노드를 가리키는 해시 노드를 찾았다면
            {
                hash_map_lists_[hashed_key].del_node(i); // 해시 노드 삭제 완료
                break;
            }
            
        }
    }

    cache_list_.add_node_at_0(key, value);
    hash_map_lists_[hash(key)].add_node_at_0("hash_" + key, cache_list_.head_->next_);
}
// double을 cache에 추가한다, multiply 의 경우
void Cache::add(std::string key, double value)
{
    if (cache_list_.size_ == CACHE_SIZE) // 꽉 차서 마지막 캐시 노드를 지우고 그것을 가리키는 해시 노드를 지운다
    {
        std::string last_cache_node_key = cache_list_.get_key(CACHE_SIZE - 1); // 마지막 캐시 노드의 키
        int hashed_key = hash(last_cache_node_key);                            // 해시 리스트 인덱스

        cache_list_.del_node(CACHE_SIZE - 1); // 캐시 노드 삭제 완료

        for (int i = 0; i < hash_map_lists_[hashed_key].size_; i++)
        {
            if (hash_map_lists_[hashed_key].get_key(i).find(last_cache_node_key) !=
                std::string::npos) // 마지막 캐시 노드를 가리키는 해시 노드를 찾았다면
            {
                hash_map_lists_[hashed_key].del_node(i); // 해시 노드 삭제 완료
            }
            break;
        }
    }

    cache_list_.add_node_at_0(key, value);
    hash_map_lists_[hash(key)].add_node_at_0("hash_" + key, cache_list_.head_->next_);
}

// key에 해당하는 value를 cache에서 가져온다
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, int &value)
{ // palindrome 의 경우

    bool is_hit = false;
    int hashed_key = hash(key);

    for (int i = 0; i < hash_map_lists_[hashed_key].size_; i++)
    {
        if (hash_map_lists_[hashed_key].get_key(i).find(key) != std::string::npos)
        { // 캐시 노드를 가리키는 해시 노드를 찾았다면
            is_hit = true;
            value = static_cast<const int>(*static_cast<const int *>(
                static_cast<const Node *>(hash_map_lists_[hashed_key].get_value(i))->value_));
            cache_list_.move_node_to_0(key);
            break;
        }
    }

    return is_hit;
}
// key에 해당하는 value를 cache에서 가져온다.
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, double &value)
{ // multiply 의 경우
    bool is_hit = false;
    int hashed_key = hash(key);

    for (int i = 0; i < hash_map_lists_[hashed_key].size_; i++)
    {
        if (hash_map_lists_[hashed_key].get_key(i).find(key) != std::string::npos)
        {
            is_hit = true;
            value = static_cast<const double>(*static_cast<const double *>(
                static_cast<const Node *>(hash_map_lists_[hashed_key].get_value(i))->value_));
            cache_list_.move_node_to_0(key);
            break;
        }
    }

    return is_hit;
}

// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString()
{
    std::ostringstream ss;
    for (int i = 0; i < cache_list_.size_; i++)
    {
        ss << ("[" + cache_list_.get_key(i) + ": ");
        if (cache_list_.get_key(i).find("palindrome") != std::string::npos)
        {
            ss << *static_cast<const int *>(cache_list_.get_value(i));
        }
        else
        {
            ss << *static_cast<const double *>(cache_list_.get_value(i));
        }
        ss << "]";

        if (i + 1 != cache_list_.size_)
        {
            ss << " -> ";
        }
    }
    ss << "\n";
    return ss.str();
}