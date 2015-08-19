#if 1
#include <stdio.h>

#ifdef  MODULE
#define module_init( fn )  \
	int  init_module(void) __attribute__((alias(#fn)))
#else
#define module_init( fn )  __initcall(x);
#endif

int my_init(void)
{
	printf("init_module()\n");
	return 0;
}

module_init( my_init );

int main()
{
	init_module();
	return 0;
}
#endif
#if 0
#include <stdio.h>

void bar(void)
{
	printf("bar()\n");
}

void  foo(void) __attribute__((alias("bar")));

int main()
{
	foo();
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)
#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#define __MODULE_LICENSE( license, info )    \
	static const char __UNIQUE_ID(license)[] = "license" "=" info 


__MODULE_LICENSE(license, "GPL"); __MODULE_LICENSE(license, "BSD");

int main()
{
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define __FOO(a,b)   a##b
#define FOO( a,b )    __FOO(a,b) 
#define __MODULE_LICENSE( license, info )    \
	static const char FOO(license,__LINE__)[] = "license" "=" info 


__MODULE_LICENSE(license, "GPL"); __MODULE_LICENSE(license, "BSD");

int main()
{
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define BAR   hello	

int main()
{
	//printf("%s\n", "license" "=" "GPL" ); 
	printf("%s\n", "license=GPL" ); 
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define __FOO(x) #x	
#define FOO(x)	__FOO(x)
#define BAR   hello	

int main()
{
	printf("%s\n", FOO(BAR) ); 
	return 0;
}
#endif
#if 0
#include <stdio.h>

#define FOO(x)	#x
#define BAR   hello	

int main()
{
	printf("%s\n", FOO(BAR) ); 
	return 0;
}
#endif
#if 0
#include <stdio.h>

//#define __stringify_1(x...)	#x
//#define __stringify(x...)	__stringify_1(x)

#define __stringify(x...) #x	
int main()
{
	printf("%s\n", __stringify(license)); 
	return 0;
}
#endif
#if 0
#include <stdio.h>

# define __used			__attribute__((__used__))
int main()
{
	int __used __attribute__((unused))  glob;

	//printf("glob=%d\n", glob );
	return 0;
}
#endif

#if 0
static const char a[] 
__attribute__((section(".modinfo"))) 
= "hello";

int main()
{
	return 0;
}
#endif
#if 0
static const char a[] = "hello";

int main()
{
	return 0;
}
#endif
