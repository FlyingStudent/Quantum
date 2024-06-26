#ifdef QT_PLATFORM_WINDOWS
	#ifdef QT_BUILD_DLL
		#define QUANTUM_API __declspec(dllexport)
	#else
		#define QUANTUM_API __declspec(dllimport)	
	#endif
#else
	#error Quantum only support windows! 
#endif

#ifdef QT_ENABLE_ASSERTS
#define QT_ASSERT(x, ...) {if (!(x)) {QT_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); }}
#define QT_CORE_ASSERT(x, ...) { if(!(x)) {QT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define QT_ASSERT(x,...)
#define QT_CORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)
#define QT_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)