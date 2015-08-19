#define __must_check        __attribute__((warn_unused_result))
int __must_check foo(void)
{
	return -1;
}

int main()
{
	int ret;
    ret = foo();
	return 0;
}
