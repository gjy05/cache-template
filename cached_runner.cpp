#include "cached_runner.h"
#include "task_runner.h"
// TODO: 필요한 함수 구현

CachedRunner::CachedRunner(Cache &cache) : cache_(cache), hits_(0), misses_(0) {}

// 파일의 숫자를 전부 곱하여 반환한다
double CachedRunner::multiply(std::string filename)
{
    double value;
    if (cache_.get("multiply(" + filename + ")", value) == true)
    {
        hits_++;
    }
    else
    {
        value = TaskRunner::multiply(filename);
        cache_.add("multiply(" + filename + ")", value);
        misses_++;
    }
    return value;
}
// 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
int CachedRunner::palindrome(std::string filename)
{
    int value;
    if (cache_.get("palindrome(" + filename + ")", value) == true)
    {
        hits_++;
    }
    else
    {
        value = TaskRunner::palindrome(filename);
        cache_.add("palindrome(" + filename + ")", value);
        misses_++;
    }
    return value;
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits() { return hits_; }
// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses() { return misses_; }