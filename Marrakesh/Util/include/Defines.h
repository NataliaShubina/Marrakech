#pragma once
#include <stack>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <cassert>
#include <Windows.h>

#define WINDOW_TITLE "Marrakesh"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define GRID_SIZE 7
#define SCENE_PATH "data/scene.json"
#define RESOURCE_PATH "data/resources.json"

#define MAJOR_VERSION 3
#define MINOR_VERSION 3

#define PArray		std::vector
#define PStack		std::stack
#define PMap		std::map
#define PList		std::list
#define PSet		std::set
#define PQueue		std::queue
#define MapPair		std::pair

#define PUMap		std::unordered_map
#define PUSet		std::unordered_set

#define PLess		std::less
#define PEqual		std::equal_to

#define AutoPtr		std::auto_ptr
#define SharedPtr	std::shared_ptr
#define UniquePtr	std::unique_ptr
#define WeakPtr		std::weak_ptr

#define DEFINE_PTRS(T)							\
typedef std::shared_ptr<T>			T##Ptr;		\
typedef std::shared_ptr<const T>	T##CPtr;	\
typedef std::unique_ptr<T>			T##UPtr;	\
typedef std::unique_ptr<const T>	T##CUPtr;	\
typedef std::auto_ptr<T>			T##APtr;	\
typedef std::auto_ptr<const T>		T##CAPtr;	\
typedef std::weak_ptr<T>			T##WPtr;	\
typedef std::weak_ptr<const T>		T##CWPtr;

#define DEFINE_CLASS_PTRS(T)					\
class T;										\
DEFINE_PTRS(T)

#define DEFINE_STRUCT_PTRS(T)					\
struct T;										\
DEFINE_PTRS(T)

#define ForEach(type, container, it) for (type::iterator it = (container).begin(), end##it = (container).end(); it != end##it; ++it)
#define ForEachC(type, container, it) for (type::const_iterator it = (container).begin(), end##it = (container).end(); it != end##it; ++it)


#define ERROR_MESSAGE(message)			\
MessageBoxA( NULL,						\
message,								\
"Error!!!",								\
MB_ABORTRETRYIGNORE | MB_ICONERROR)		\


#if defined _DEBUG
	#define PASSERT(condition, message) if(!condition){ ERROR_MESSAGE(message);}
#else
	#define PASSERT(condition, message) ;
#endif