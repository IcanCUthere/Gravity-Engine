export module stdlib;
export import <vector>;
export import <unordered_map>;
export import <iostream>;
export import <functional>;
export import <shared_mutex>;

export template<typename T>
using Unique = std::unique_ptr<T>;
export template<typename T, typename ...Args>
constexpr Unique<T> CreateUnique(Args&& ...args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

export template<typename T>
using Shared = std::shared_ptr<T>;
export template<typename T, typename ...Args>
constexpr Shared<T> CreateShared(Args&& ...args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

export template<typename T>
using Ref = std::weak_ptr<T>;
export template<typename T>
constexpr Ref<T> CreateRef(const Shared<T>& shared)
{
	return Ref(shared);
}