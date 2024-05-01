#ifndef CACHE_H
#define CACHE_H

#include <string>

#define CACHE_SIZE 10

class Cache
{
private:
    // TODO: private inner struct/class 선언 가능
    // TODO: private 멤버 변수와 함수 추가 가능
    class Node // 리스트의 노드
    {
    public:
        // 캐시 노드일 경우: calculation(filename)
        // 해시 노드일 경우: hash_calculation(filename)
        // 더미 노드일 경우: dummy
        const std::string key_;
        // 캐시 노드일 경우 int*(palindrome 일 경우) || double*(multiply 일 경우)
        // 해시 노드일 경우 Node*
        // 더미 노드일 경우 nullptr
        const void *value_;
        // 다음 노드를 가리킨다
        Node *next_;

        Node(std::string key, int value) : key_(key),
                                           value_(new const int(value)), // palindrome
                                           next_(nullptr){};

        Node(std::string key, double value) : key_(key),
                                              value_(new const double(value)), // multiply
                                              next_(nullptr){};

        Node(std::string key, Node *value) : key_(key),
                                             value_(value), // 캐시 노드의 주소값
                                             next_(nullptr){};

        Node() : key_("dummy"), value_(nullptr), next_(nullptr){}; // 더미 노드

        ~Node() // 해시 노드인 경우는 value_ 가 가리키는 노드를 캐시 리스트에서 따로 삭제해 준다
        {       // 더미 노드는 애초에 가리키는 곳이 없으므로 value_ 를 삭제하면 안 된다
            if (key_.find("hash") == std::string::npos &&
                key_.find("dummy") == std::string::npos)
            { // 그러므로 캐시 노드일 경우만 value_ 를 지운다
                if (key_.find("palindrome") != std::string::npos)
                {
                    delete static_cast<const int *>(value_);
                }
                else
                {
                    delete static_cast<const double *>(value_);
                }
            } // next_ 또한 삭제하면 안 된다
        }
    };

    class Linked_List // 더미 노드가 있는 단일 연결 리스트
    {
    public:
        Node *head_;
        int size_;

        // 노드 추가는 0번째 에서만 이루어진다.
        Linked_List() : head_(new Node()), size_(0) {}
        ~Linked_List()
        {
            while (size_ != 0)
            {
                del_node(0);
            }
            delete head_;
        }
        // 0번째 위치에 노드 추가, int 형 value
        void add_node_at_0(std::string key, int value)
        {
            Node *new_node = new Node(key, value);
            new_node->next_ = head_->next_; // 새 노드의 다음 노드 = 더미 노드의 다음 노드
            head_->next_ = new_node;        // 더미 노드의 다음 노드 = 새 노드
            size_++;
        }
        // 0번째 위치에 노드 추가, double 형 value
        void add_node_at_0(std::string key, double value)
        {
            Node *new_node = new Node(key, value);
            new_node->next_ = head_->next_; // 새 노드의 다음 노드 = 더미 노드의 다음 노드
            head_->next_ = new_node;        // 더미 노드의 다음 노드 = 새 노드
            size_++;
        }
        // 0번째 위치에 노드 추가, Node* 형 value
        void add_node_at_0(std::string key, Node *value)
        {
            Node *new_node = new Node(key, value);
            new_node->next_ = head_->next_; // 새 노드의 다음 노드 = 더미 노드의 다음 노드
            head_->next_ = new_node;        // 더미 노드의 다음 노드 = 새 노드
            size_++;
        }

        // 리스트의 i 번째 노드를 지운다(범위 벗어남에 주의)
        void del_node(int node_i)
        {
            Node *before_del_node = head_; // 지울 노드 한 칸 전을 가리킬 것이다
            Node *del_node;                // 지울 노드를 가리킬 것이다

            for (int i = 0; i < node_i; i++)
            { // 0번째 노드를 지울 것이라면 더미 노드를 가리킨다
                before_del_node = before_del_node->next_;
            }

            del_node = before_del_node->next_;        // 지울 노드 = 지울 노드 한 칸 전 노드의 다음 노드
            before_del_node->next_ = del_node->next_; // 한 칸 전 노드의 다음 노드 = 지울 노드 다음 노드
            delete del_node;                          // 소멸자 호출
            size_--;
        }

        // i 번째 노드의 key_ 를 반환(범위 벗어남에 주의)
        const std::string get_key(int node_i) const
        {
            Node *node = head_; // 지금은 더미 노드를 가리키고, (node_i - 1)번째 노드를 가리킬 것이다
            for (int i = 0; i < node_i; i++)
            {
                node = node->next_;
            } // node_i == 0 일 때, 더미 노드를 가리킴
            return node->next_->key_;
        }
        // i 번째 노드의 value_ 를 반환
        const void *get_value(int node_i) const
        {
            Node *node = head_; // 지금은 더미 노드를 가리키고, (node_i - 1)번째 노드를 가리킬 것이다
            for (int i = 0; i < node_i; i++)
            {
                node = node->next_;
            } // node_i == 0 일 때, 더미 노드를 가리킴
            return node->next_->value_;
        }

        void move_node_to_0(std::string key) const // key 와 일치하는 노드를 0번째 위치로 옮긴다
        {
            Node *before_moving_node = head_; // 움직일 노드 한 칸 전 노드
            Node *moving_node;                // 움직일 노드

            while (before_moving_node->next_->key_.find(key) == std::string::npos)
            {
                before_moving_node = before_moving_node->next_;
            }

            moving_node = before_moving_node->next_;
            before_moving_node->next_ = moving_node->next_;
            moving_node->next_ = head_->next_;
            head_->next_ = moving_node;
        }
    };

    // 해시 함수
    int hash(std::string key)
    {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
        {
            sum += key[i];
        }
        return sum % CACHE_SIZE;
    }

    Linked_List hash_map_lists_[CACHE_SIZE];
    Linked_List cache_list_;

public:
    Cache();
    ~Cache();
    // int를 cache에 추가한다
    void add(std::string key, int value);
    // double을 cache에 추가한다
    void add(std::string key, double value);
    // key에 해당하는 value를 cache에서 가져온다
    // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
    bool get(std::string key, int &value);
    // key에 해당하는 value를 cache에서 가져온다.
    // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
    bool get(std::string key, double &value);

    // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
    // 다음과 같이 표현된 문자열을 반환한다
    // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
    std::string toString();
};

#endif