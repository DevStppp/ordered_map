#ifndef STPPP_ORDERED_MAP_H
#define STPPP_ORDERED_MAP_H

#include <algorithm>
#include <list>
#include <mutex>
#include <unordered_map>

namespace stppp {
template<typename Key, typename T, typename Hash = std::hash<Key>>
class ordered_map
{
  public:
    using value_type = std::pair<const Key, T>;
    using list_type = std::list<value_type>;
    using iterator = typename list_type::iterator;
    using const_iterator = typename list_type::const_iterator;
    using reverse_iterator = typename list_type::reverse_iterator;
    using const_reverse_iterator = typename list_type::const_reverse_iterator;
    using map_type = std::unordered_map<Key, iterator, Hash>;
    using map_iterator = typename map_type::iterator;
    using size_type = std::size_t;
    using initlist_type = std::initializer_list<value_type>;

    using _writeLocker = std::lock_guard<std::mutex>;

  public:
    // Constructor/Destructor
    ordered_map() noexcept
      : m_list()
      , m_map()
    {
    }

    explicit ordered_map(const size_type bucket_count,
                         const Hash& hash = Hash()) noexcept
      : m_list()
      , m_map(bucket_count, hash)
    {
    }

    ordered_map(initlist_type initlist)
      : ordered_map()
    {
        insert(end(), initlist);
    }

    ordered_map(initlist_type initlist, const size_type bucket_count, const Hash& hash = Hash())
      : ordered_map(bucket_count, hash)
    {
        insert(end(), initlist);
    }

    ordered_map(const ordered_map& rhs) noexcept
      : m_list(rhs.m_list)
      , m_map(rhs.m_map)
    {
    }

    ordered_map(ordered_map&& rhs) noexcept
      : m_list(std::move(rhs.m_list))
      , m_map(std::move(rhs.m_map))
    {
    }

    virtual ~ordered_map() noexcept
    {
        clear();
    }

    ordered_map& operator=(const ordered_map& rhs) noexcept
    {
        {
            _writeLocker lock(m_mutex);

            //std::pair<const key,value> = std::pair<const key, value>
            //build error
            m_list.clear();
            std::for_each(rhs.m_list.begin(), rhs.m_list.end(), [&](const value_type& i) {
                m_list.emplace_back(i.first, i.second);
            });

            m_map = rhs.m_map;
        }
        return (*this);
    }

    ordered_map& operator=(ordered_map&& rhs) noexcept
    {
        {
            _writeLocker lock(m_mutex);
            m_list = std::move(rhs.m_list);
            m_map = std::move(rhs.m_map);
        }

        return (*this);
    }

  public:
    //
    //
    // Iterator
    //
    //
    iterator begin() noexcept
    {
        return m_list.begin();
    }

    const_iterator begin() const noexcept
    {
        return m_list.begin();
    }

    iterator end() noexcept
    {
        return m_list.end();
    }

    const_iterator end() const noexcept
    {
        return m_list.end();
    }

    const_iterator cbegin() const noexcept
    {
        return m_list.cbegin();
    }

    const_iterator cend() const noexcept
    {
        return m_list.cend();
    }

    reverse_iterator rbegin() noexcept
    {
        return m_list.rbegin();
    }

    reverse_iterator rend() noexcept
    {
        return m_list.rend();
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return m_list.rbegin();
    }

    const_reverse_iterator rend() const noexcept
    {
        return m_list.rend();
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return m_list.crbegin();
    }

    const_reverse_iterator crend() const noexcept
    {
        return m_list.crend();
    }

    //
    //
    // Capacity
    //
    //
    bool empty() const noexcept
    {
        return m_list.empty();
    }

    size_type size() const noexcept
    {
        return m_list.size();
    }

    size_type max_size() const noexcept
    {
        return std::min(m_list.max_size(), m_map.max_size());
    }

    //
    //
    // Modifiers
    //
    //
    void clear() noexcept
    {
        {
            _writeLocker lock(m_mutex);
            m_map.clear();
            m_list.clear();
        }
    }

    std::pair<iterator, bool> insert(const_iterator pos,
                                     const value_type& value)
    {
        return emplace(pos, value);
    }

    std::pair<iterator, bool> insert(const_iterator pos, value_type&& value)
    {
        return emplace(pos, std::move(value));
    }

    void insert(const_iterator pos, initlist_type list)
    {
        insert(pos, list.begin(), list.end());
    }

    //생성자에서도 사용하기 때문에 Exception이 아닌 return 처리
    template<typename InputIt>
    void insert(const_iterator pos, InputIt first, InputIt last)
    {
        if (false == _check_valid_distance(first, last))
            return;
        for (auto i = first; i < last; ++i)
        {
            if (insert(pos, std::move(*i)).second == false)
                continue;
        }
    }

    std::pair<iterator, bool> push_back(const value_type& value)
    {
        return emplace_back(value);
    }

    std::pair<iterator, bool> push_back(value_type&& value)
    {
        return emplace_back(std::move(value));
    }

    std::pair<iterator, bool> push_front(value_type&& value)
    {
        return emplace_front(std::move(value));
    }

    std::pair<iterator, bool> push_front(const value_type& value)
    {
        return emplace_front(value);
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace_front(Args&&... args)
    {
        return emplace(m_list.begin(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace_back(Args&&... args)
    {
        return emplace(m_list.end(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace(const_iterator pos, Args&&... args)
    {
        value_type value(std::forward<Args>(args)...);
        Key key = value.first;

        {
            _writeLocker lock(m_mutex);

            iterator inserted = m_list.insert(pos, std::move(value));
            auto result = m_map.emplace(key, inserted);
            if (false == result.second)
                m_list.erase(inserted);

            return {result.first->second, result.second};
        }
    }

    // throw std::out_of_range
    iterator erase(const_iterator pos)
    {
        if (pos == m_list.end())
            throw std::out_of_range("out of range iterator");

        //iterator invalidate => segment fault
        auto target = m_map.find(pos->first);
        if (target == m_map.end())
            throw std::out_of_range("out of range iterator");

        iterator next = m_list.end();
        {
            _writeLocker lock(m_mutex);
            next = m_list.erase(pos);
            m_map.erase(target);
        }

        return next;
    }

    size_type erase(const Key& key)
    {
        auto target = m_map.find(key);
        if (target == m_map.end())
            return 0;

        erase(target->second);
        return 1;
    }

    template<typename linkedmap>
    void swap(linkedmap& rhs) noexcept
    {
        {
            _writeLocker lock(m_mutex);
            m_list.swap(rhs.m_list);
            m_map.swap(rhs.m_map);
        }
    }

    //
    //
    // LookUp
    //
    //
    T& at(const Key& key)
    {
        return m_map.at(key)->second;
    }

    const T& at(const Key& key) const
    {
        return m_map.at(key)->second;
    }

    T& operator[](const Key& key)
    {
        if (false == contains(key))
            emplace_back(key, T());

        return m_map[key]->second;
    }

    // throw except??
    size_type count(const Key& key) const
    {
        return m_map.count(key);
    }

    iterator find(const Key& key)
    {
        auto find = m_map.find(key);
        if (find == m_map.end())
            return m_list.end();

        return m_map.find(key)->second;
    }

    const_iterator find(const Key& key) const
    {
        auto find = m_map.find(key);
        if (find == m_map.cend())
            return m_list.cend();

        return m_map.find(key)->second;
    }

    // since c++20
    bool contains(const Key& key) const
    {
        return m_map.count(key) == 0 ? false : true;
    }

  private:
    template<typename InputIt>
    bool _check_valid_distance(InputIt first, InputIt last)
    {
        auto size = std::distance(first, last);
        if (size <= 0)
            return false;
        return true;
    }

  private:
    list_type m_list;
    map_type m_map;
    std::mutex m_mutex;
};  //class ordered_map
}  // namespace stppp

namespace std {
template<typename Key, typename T, typename Hash = std::hash<Key>>
void swap(stppp::ordered_map<Key, T, Hash>& lhs,
          stppp::ordered_map<Key, T, Hash>& rhs) noexcept
{
    lhs.swap(rhs);
}
}  // namespace std

#endif  // STPPP_ORDERED_MAP_H